/**************************************************************************
Source file	: ManageFuns.cc
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	: > ArgumentManagement : checks if arguments are ok and returning
				corresponding error if something is wrong
			  >
			  >
			  >

***************************************************************************/

#include <unistd.h>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

#include "ManageFuns.h"

/* Checking arguments and returning error if something is wrong */
int ArgumentManagement( int arg_num, char const **arguments, char **input_file_name, int *k ){

	bool arg1_ok = false;
	bool arg2_ok = false;
	int i=0;

	if( arg_num == 3 ){ /* We should get only -i docfile as argument */
		if( strcmp(arguments[1],"-i") == 0 ){

			/* Check if file exists */
			if( access( arguments[2], F_OK ) != 0 ) {     /* file doesn't exist */
				return -2;
			}

			if( *input_file_name == NULL ){
				*input_file_name = new char [strlen(arguments[2]) + 1];
				strcpy(*input_file_name,arguments[2]);
			}
			else{
				return -4;
			}

			/* Default value of k is 10 */
			*k = 10;

			return 0;
		}
		else{
			return -1;
		}
	}
	else if( arg_num == 5 ){ /* We should get  -i docfile -k K in any order */

		for( i = 1; i < arg_num; i++ ){

			if( strcmp(arguments[i],"-i") == 0 ){

				if( arg1_ok ){ /* Cannot give 2 times -i docfile */

					if( *input_file_name != NULL ){
						delete[] (*input_file_name);
						*input_file_name = NULL;
					}

					return -1;

				}

				i++;

				/* Check if file exists */
				if( access( arguments[i], F_OK ) != 0 ) {     /* file doesn't exist */
					return -2;
				}

				if( *input_file_name == NULL ){
					*input_file_name = new char [strlen(arguments[i]) + 1];
					strcpy(*input_file_name,arguments[i]);
				}
				else{
					return -4;
				}

				arg1_ok = true;

			}
			else if( strcmp(arguments[i],"-k") == 0 ){

				if( arg2_ok ){ /* Cannot give 2 times -k K */
					return -1;
				}

				i++;

				*k = atoi(arguments[i]);
				if( *k <= 0 ){
					return -3;
				}

				arg2_ok = true;

			}
			else{
				return -1;
			}
		}

		return 0;
	}
	else{
		return -1;
	}

}

/* Find number_of_rows of the file and check if ids are ok */
int GetFileInfo( FileInfo &current_file_info ){

	FILE* current_file;
	char to_check;
	int id=-1;

	current_file = fopen(current_file_info.file_name, "r");

	fscanf(current_file,"%d",&id);
	//cout << "to prwto id poy diabastike einai " << id << endl;
	if( id != 0 ){
		fclose(current_file);
		return -1;
	}

	to_check = fgetc(current_file);
	while( 1 ){
		//printf("diabastike -%d-(%c)\n",to_check,to_check );
		if( to_check == '\n' ){
			//cout << "mpike edw gia number_of_rows na einai " << current_file_info.number_of_rows << endl;
			current_file_info.number_of_rows ++;

			if ( fscanf(current_file,"%d",&id) != 1 ){

				to_check = fgetc(current_file);
				if( to_check == EOF ){
					break;
				}
				fclose(current_file);
				return -1;

			}

			//cout << "to deytero id poy diabastike einai " << id << endl;
			if( id != current_file_info.number_of_rows ){
				fclose(current_file);
				return -1;
			}

		}
		to_check = fgetc(current_file);
	}


	fclose(current_file);
	//cout << " Last id which we read " << id << endl;

	return 1;
}

/* Inserting Docs in DocMap and words in Trie */
int InsertDocs( DocMap &current_doc_map, Trie &current_trie, FileInfo &current_file_info ){

	char *init_doc = NULL;
	char *doc;
	size_t len = 0;
	ssize_t read = 1;
	int id = 0;
	int number_of_words;
	int total_words = 0;

	FILE* current_file;

	current_file = fopen(current_file_info.file_name, "r");

	read = getline(&init_doc, &len, current_file);
	while( read != -1 ){

		doc = GetFinalDoc(init_doc,read-1);

		/* Insert doc to DocMap at index id */
		current_doc_map.InsertDoc(doc,id);

		/* Insert words of this doc into Trie */
		number_of_words = InsertWords(doc,id,current_trie);

		/* Set number_of_words of doc with current id */
		current_doc_map.SetDocCount(id,number_of_words);

		total_words += number_of_words;

		/* Prepare for next loop */
		read = getline(&init_doc, &len, current_file);
		delete[] doc;
		id++;
	}

	current_doc_map.SetWordCount(total_words);
	fclose(current_file);
	free(init_doc);

	return 1;
}

/* Insert words of given doc one by one into the Trie and return the number
	of words of given doc */
int InsertWords( char *doc_to_split, int id, Trie &current_trie ){

	int number_of_words = 0;
	char *word_to_insert;

	word_to_insert = strtok(doc_to_split," \t");

	while( word_to_insert != NULL ){
		number_of_words ++;
		current_trie.Insert(word_to_insert,id);
		word_to_insert = strtok(NULL," \t");
	}

	return number_of_words;
}

/* Return the substring of doc_to_format which begins
 	from first non-space character after id, and
	ends at last non-space character before \n */
char* GetFinalDoc( char *doc_to_format, int last_char_pos ){

	int begin,end;
	char *final_doc;
	int current = 0;

	/* Skip initial spaces/tabs before id */
	while( (doc_to_format[current] == ' ') || (doc_to_format[current] == '\t') ){
		current++;
	}

	/* Skip id */
	while( (doc_to_format[current] != ' ') && (doc_to_format[current] != '\t') ){
		current++;
	}

	/* Find the first non-space character after id */
	while( (doc_to_format[current] == ' ') || (doc_to_format[current] == '\t') ){
		current++;
	}

	begin = current;

	/* at last_char_pos is \n so we need last_char_pos - 1 */
	current = last_char_pos-1;

	/* Find the last non-space character */
	/* Begin from the second to last character ( before the \n ) and
		go back till find a non-space character */
	while( (doc_to_format[current] == ' ') || (doc_to_format[current] == '\t') ){
		current--;
	}

	end = current;

	final_doc = new char[ ( end - begin + 1 ) + 1 ];

	memcpy(final_doc,doc_to_format+begin,end - begin + 1);
	final_doc[end - begin + 1] = '\0';

	return final_doc;

}

int PromptMode( DocMap &current_doc_map, Trie &current_trie, int top_k ){

	char *input = NULL;
	char *option;
	size_t len = 0;
	char *word_to_check;
	char *word_to_search;
	int id_to_search;
	int number_of_words;
	Words *words_to_search;

	while( 1 ){

		cout << "Give your option:" << endl;

		getline(&input, &len, stdin);

		option = new char[ strlen(input) + 1 ];
		strcpy(option,input);

		word_to_check = strtok(option," \t \n");
		if( word_to_check == NULL ){
			continue;
		}

		if( (strcmp(word_to_check,"/search") == 0) || (strcmp(word_to_check,"\\search") == 0) ){

			number_of_words = FindWordsNumber( input );

			if( number_of_words == 0 ){
				cout << "Invalid option! No words were given for searching! Please try again!" << endl;
			}
			else{

				/* Make Words for searching */
				words_to_search = new Words(number_of_words);
				for( int i = 0; i < number_of_words; i++ ){
					word_to_check = strtok(NULL," \t \n");
					words_to_search->InsertWord(word_to_check,i);
				}

				/* Search words and find scores */
				if ( Search(current_doc_map,current_trie,*words_to_search,top_k) != 1 ){
					//something went wrong
				}

				delete words_to_search;
			}

		}
		else if( (strcmp(word_to_check,"/df") == 0) || (strcmp(word_to_check,"\\df") == 0) ){

			word_to_check = strtok(NULL," \t \n");
			if( word_to_check != NULL ){

				word_to_search = new char[ strlen(word_to_check) + 1 ];
				strcpy(word_to_search,word_to_check);

				word_to_check = strtok(NULL," \t \n");
				if( word_to_check != NULL ){
					cout << "Invalid option! There cannot be other words after the option /df word . Please try again!" << endl;
				}
				else{
					current_trie.PrintSpecificDf(word_to_search);
				}

				delete[] word_to_search;

			}
			else{
				current_trie.PrintAllDf();
			}

		}
		else if( (strcmp(word_to_check,"/tf") == 0) || (strcmp(word_to_check,"\\tf") == 0) ){
			word_to_check = strtok(NULL," \t \n");
			if( word_to_check != NULL ){

				id_to_search = atoi(word_to_check);
				word_to_check = strtok(NULL," \t \n");

				if( word_to_check != NULL ){

					word_to_search = new char[ strlen(word_to_check) + 1 ];
					strcpy(word_to_search,word_to_check);

					word_to_check = strtok(NULL," \t \n");
					if( word_to_check != NULL ){
						cout << "Invalid option! There cannot be other words after the option /tf id word . Please try again!" << endl;
					}
					else{
						current_trie.PrintTermFreq(word_to_search,id_to_search);
					}

					delete[] word_to_search;

				}
				else{
					cout << "Invalid syntax of option /tf . No word was given. You should give /tf id word . Please try again!" << endl;
				}

			}
			else{
				cout << "Invalid syntax of option /tf . You should give /tf id word . Please try again!" << endl;
			}
		}
		else if( (strcmp(word_to_check,"/exit") == 0) || (strcmp(word_to_check,"\\exit") == 0) ){

			word_to_check = strtok(NULL," \t \n");
			if( word_to_check != NULL ){
				cout << "Invalid option! There cannot be words after the option /exit . Please try again!" << endl;
			}
			else{
				delete[] option;
				free(input);
				return 1;
			}

		}
		else {
			cout << "Invalid option! Try again!" << endl;
		}


		delete[] option;
		cout << endl;
	}

}

/* Find how many words there are in string with format "/search word1 word2 ..... wordn \n" */
/* We have check before this call, that search_string_to_check has at least 1 word */
int FindWordsNumber( char *search_string_to_check ){

	int count = 0;
	int current = 0;

	/* Skip initial spaces/tabs before /search */
	while( (search_string_to_check[current] == ' ') || (search_string_to_check[current] == '\t') ){
		current++;
	}

	/* Skip /search */
	while( (search_string_to_check[current] != ' ') && (search_string_to_check[current] != '\t') && (search_string_to_check[current] != '\n') ){
		current++;
	}

	while( count < 10 ){

		/* Skip spaces/tabs before word */
		while( (search_string_to_check[current] == ' ') || (search_string_to_check[current] == '\t') ){
			current++;
		}

		/* Because there may be \n after some spaces/tab */
		if( search_string_to_check[current] == '\n' ){
			break;
		}

		count ++;

		/* Skip current word */
		while( (search_string_to_check[current] != ' ') && (search_string_to_check[current] != '\t') && (search_string_to_check[current] != '\n') ){
			current++;
		}

		/* Because there may be \n after a word */
		if( search_string_to_check[current] == '\n' ){
			break;
		}

	}

	return count;
}

int Search( DocMap &current_doc_map, Trie &current_trie, Words &words_to_search, int top_k ){

	PostingList *cur_PL;
	PL_Node *cur_node = NULL;
	ScoreInfo *init_scores_array;
	ScoreId *relevant_id_scores_array;
	int counter;
	int count_relevant_ids = 0;
	double idf;
	int df;
	int tf;
	double score;
	double avgdl = ((double) current_doc_map.GetWordCount()) / current_doc_map.GetSize();

	//cout << "avgdl is " << avgdl << endl;

	/* Create an array of size current_doc_map.GetDocCount() so as to have
		O(1) insertion of a score and O(1) update of a score */
	init_scores_array = new ScoreInfo[ current_doc_map.GetSize() ];

	for( int i = 0; i < current_doc_map.GetSize(); i++ ){
		init_scores_array[i].is_relevant = false;
		init_scores_array[i].score = 0;
	}

	/* For each word, get posting list and calculate this partial
		score for each id in this posting list */
	for( int i = 0; i < words_to_search.GetSize(); i++ ){

		cur_PL = current_trie.GetPostList(words_to_search.GetWord(i));

		if( cur_PL == NULL ){ /* There is no Posting list for this word */
			continue;
		}

		df = cur_PL->GetDocFrequency();

		idf = ( current_doc_map.GetSize() - df + 0.5 ) / (df + 0.5);
		idf = log10(idf);

		//cout << "idf for word " << words_to_search.GetWord(i) << " is " << idf << endl;

		cur_node = cur_PL->GetFirst();

		/* Calculate partial score for each id in this PostingList */
		while( cur_node != NULL ){

			tf = cur_node->GetTermFreq();
			score = ( tf * ( 1.2 + 1 ) ) / ( tf + 1.2 * ( 1 - 0.75 + 0.75 * ( current_doc_map.GetDocCount(cur_node->GetId()) / avgdl ) ) );
			score = idf * score;
			//cout << "To score gia to doc me id " << cur_node->GetId() << " einai " << score << endl;

			if( !init_scores_array[cur_node->GetId()].is_relevant ){
				init_scores_array[cur_node->GetId()].is_relevant = true;
				count_relevant_ids ++;
			}

			init_scores_array[cur_node->GetId()].score += score;

			cur_node = cur_node->GetNext();

		}

	}

	if( count_relevant_ids == 0 ){
		cout << "No document with at least one word of this query was found!" << endl;
		delete[] init_scores_array;
		return -1;
	}

	/* Make a smaller array to store only relevant ids scores */
	relevant_id_scores_array = new ScoreId [ count_relevant_ids ];
	counter = 0;
	for( int i = 0; i < current_doc_map.GetSize(); i++ ){
		if( init_scores_array[i].is_relevant ){
			relevant_id_scores_array[counter].score = init_scores_array[i].score;
			relevant_id_scores_array[counter].id = i;
			counter ++;
		}
	}
	delete[] init_scores_array;

	/* Create heap for relevant_id_scores_array array */
	Heap scores_heap(relevant_id_scores_array,count_relevant_ids);

	/* Print top-k scores */
	if( PrintTopK(current_doc_map,scores_heap,words_to_search,top_k) != 1 ){
		//something went wrong
	}

	delete[] relevant_id_scores_array;
	return 1;

}

int PrintTopK( DocMap &current_doc_map, Heap &current_heap, Words &words_to_search, int top_k ){

	ScoreId max;
	int top_k_digits;
	int max_id_digits;
	int top_score_digits;
	int cur_k_digits;
	int cur_id_digits;
	int cur_score_digits;
	char *special_info;
	int special_length;
	int offset = 0;

	/* We are sure that there will be at least one document which contains
		at least one of the word of the query */
	current_heap.GetMax(max);

	/* Find the number of digits of some max numbers */
	top_k_digits = DigitCount(top_k);
	max_id_digits = DigitCount(current_doc_map.GetSize());
	top_score_digits = DigitCount((int)max.score);

	/* Make space for special_info string */
	/* We need top_k_digits + '.' + '(' + max_id_digits + ')' + '[' + '-'+ top_score_digits + 5 (for '.' + decimal digits) + ']' + ' ' + '\0' + some_spaces */
	special_length = top_k_digits + 1 + 1 + max_id_digits + 1 + 1 + 1 + top_score_digits + 5 + 1 + 1 + 1 + 2;
	special_info = new char[special_length];
	special_info[special_length-1] = '\0';

	for( int i = 1; i <= top_k; i ++ ){

		offset = 0;
		cur_k_digits = DigitCount(i);
		cur_id_digits = DigitCount(max.id);
		cur_score_digits = DigitCount(max.score);

		/* Write Serial number */
		for( int j = 0; j < ( top_k_digits - cur_k_digits ); j++ ){
			special_info[offset] = ' ';
			offset ++;
		}
		sprintf(special_info+offset,"%d. (",i);
		offset = offset + cur_k_digits + 3;

		/* Write Id number */
		for( int j = 0; j < ( max_id_digits - cur_id_digits ); j++ ){
			special_info[offset] = ' ';
			offset ++;
		}
		sprintf(special_info+offset,"%d) [",max.id);
		offset = offset + cur_id_digits + 3;

		/* Write Score */
		for( int j = 0; j < ( top_score_digits - cur_score_digits ); j++ ){
			special_info[offset] = ' ';
			offset ++;
		}
		if( max.score > 0 ){
			special_info[offset] = ' ';
			offset ++;
		} /* Else we need this space for '-' */
		sprintf(special_info+offset,"%.4f] ",max.score);
		if( max.score < 0 ){
			offset ++;
		}
		offset = offset + cur_score_digits + 2;

		//cout << "To special_info string einai -" << special_info << "-" << endl;

		/* Print current doc */
		current_doc_map.PrintDoc(words_to_search,max.id,special_info);

		if( current_heap.GetMax(max) != 1 ){
			cout << "There is no other document which contains at least one of the given words for searching!" << endl;
			break;
		}

	}

	delete[] special_info;
	return 1;
}

int DigitCount( int num_to_check ){

	int count = 0;

	while( num_to_check != 0 ){
		num_to_check /= 10;
		count ++;
	}

	if( count == 0 ){ /* num_to_check is 0, so it has 1 digit */
		count = 1;
	}

	return count;

}
