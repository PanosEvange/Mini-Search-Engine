/**************************************************************************
Source file	: ManageFuns.cc
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	: > ArgumentManagement : Checking if given arguments are the
				correct arguments, else returing error.

			  > GetFileInfo : We read the input file for the first time so as
				to finding the number of ids of the document file ( skipping
				the blank lines ), check if ids are in the correct sequence
				and return error if something goes wrong.

			  > InsertDocs : We read the input file for the second time, line
				by line so as to inser docs in given DocMap and words in given
				Trie.If a line is blank we skip it but at the situation where
				there is no word after a given id, we return error and the
				program exits.

			  > InsertWords : We insert words of given document/string, into
				the given Trie one by one.

			  > GetFinalDoc : Returning the substring of given string,that is
				the content of a document, which begins from the first non-space
				character and ends at the last non-space character before '\n'.

			  > PromptMode : We get into a loop, waiting for user options, till
				user gives "\exit" as option. Options are:
				# /search q1 q2 ... q10 or \search q1 q2 ... q10
				# /df or \df
				# /df word or \df word
				# /tf id word or \tf id word
				# /exit
				Any other option is invalid.Blank options/lines are skipped and
				whitespaces can be given before or after any element of above
				options.

			  > FindWordNumber : Finds how many words there are in given string,
				which has the format "/search word1 word2 ... wordn \n"

			  > Search : We get the posting list for each word at the given query,
				we calculate the partial score of each id in each node of the
				posting list and update the whole score of each id.For doing that
				we create an array of length size of the docMap, that means size
				of the count of all ids, so as to have O(1) access on storing the
				score of each relevant to the query id and O(1) access on
				updating the score of each relevant to the query id.Then we create
				a smaller ,which will have only the scores and ids of relevant to
				the query ids, and then we delete the initial "big" array. Finally
				we give the last array to the Heap constructor so as to build
				a heap and then we can call PrintTopK function.

			  > PrintTopK : First of all we do the appropriate preparation of
				the special info string, so as to allocate the appropriate space
				and using an appropriate number of spaces so as to have the correct
				alignment.Then we construct the special info string, taking in
				consideration the number of digits of each serial number, of
				each score number and of each id number. Finally we call the
				PrintDoc method of given DocMap so as to print the current
				document with the special info we constructed.

			  > DigitCount : Returning the number of digits of given integer
				number. If number is 0, returns 1 as number of digits.
***************************************************************************/

#include <unistd.h>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

#include "ManageFuns.h"

#include <cstdlib>
#define CHECK_OR_EXIT(value)     \
{                           \
	if (value == NULL) {      \
		cout << "Error at memory allocation! New() returned NULL! Program must exit!!" << endl;\
		exit(EXIT_FAILURE);           \
	}                         \
}

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
				CHECK_OR_EXIT(input_file_name);
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
					CHECK_OR_EXIT(input_file_name);
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

	if( id != 0 ){
		fclose(current_file);
		return -1;
	}

	to_check = fgetc(current_file);
	while( 1 ){

		if( to_check == '\n' ){ /* Next element should be the id of the next document */

			current_file_info.number_of_rows ++;

			if ( fscanf(current_file,"%d",&id) != 1 ){

				to_check = fgetc(current_file);
				if( to_check == EOF ){
					break;
				}
				fclose(current_file);
				return -1;

			}

			if( id != current_file_info.number_of_rows ){
				fclose(current_file);
				return -1;
			}

		}
		to_check = fgetc(current_file);
	}


	fclose(current_file);

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
	int rv;

	FILE* current_file;

	current_file = fopen(current_file_info.file_name, "r");

	read = getline(&init_doc, &len, current_file);
	while( read != -1 ){

		rv = GetFinalDoc(init_doc,read-1,doc);

		if( rv == -1 ){ /* Skip this line as it is blank */
			read = getline(&init_doc, &len, current_file);
			continue;
		}

		if( rv == -2 ){ /* No word after id! Program must exit! */
			fclose(current_file);
			free(init_doc);
			cout << "No words were given after id " << id << " ! Program must exit!" << endl;
			return -1;
		}
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
int GetFinalDoc( char *doc_to_format, int last_char_pos, char* &final_doc ){

	int begin,end;
	int current = 0;

	/* Skip initial spaces/tabs before id */
	while( (doc_to_format[current] == ' ') || (doc_to_format[current] == '\t') ){
		current++;
	}

	if( doc_to_format[current] == '\n' ){ /* This line is blank so skip it */
		final_doc = NULL;
		return -1;
	}

	/* Skip id */
	while( (doc_to_format[current] != ' ') && (doc_to_format[current] != '\t') && (doc_to_format[current] != '\n') ){
		current++;
	}

	if( doc_to_format[current] == '\n' ){ /* No word after id */
		final_doc = NULL;
		return -2;
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
	CHECK_OR_EXIT(final_doc);

	memcpy(final_doc,doc_to_format+begin,end - begin + 1);
	final_doc[end - begin + 1] = '\0';

	return 1;

}

/* We get into a loop, waiting for user options, till user gives "\exit" as option */
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
		CHECK_OR_EXIT(option);
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
				CHECK_OR_EXIT(words_to_search);
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
				CHECK_OR_EXIT(word_to_search);
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
					CHECK_OR_EXIT(word_to_search);
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

/* Calculate scores for each relevant to query ids, make a heap for sorting them
   and then print top-k results.*/
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

	/* Create an array of size current_doc_map.GetDocCount() so as to have
		O(1) insertion of a score and O(1) update of a score */
	init_scores_array = new ScoreInfo[ current_doc_map.GetSize() ];
	CHECK_OR_EXIT(init_scores_array);

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

		cur_node = cur_PL->GetFirst();

		/* Calculate partial score for each id in this PostingList */
		while( cur_node != NULL ){

			tf = cur_node->GetTermFreq();
			score = ( tf * ( 1.2 + 1 ) ) / ( tf + 1.2 * ( 1 - 0.75 + 0.75 * ( current_doc_map.GetDocCount(cur_node->GetId()) / avgdl ) ) );
			score = idf * score;

			if( !init_scores_array[cur_node->GetId()].is_relevant ){
				init_scores_array[cur_node->GetId()].is_relevant = true;
				count_relevant_ids ++;
			}

			/* Update the whole score */
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
	CHECK_OR_EXIT(relevant_id_scores_array);
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

/* Constructing special info string for each document and then calling PrintDoc method of
   given DocMap */
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
	CHECK_OR_EXIT(special_info);
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

/* Returning the number of digits of given integer number. If number is 0,
   returns 1 as number of digits. */
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
