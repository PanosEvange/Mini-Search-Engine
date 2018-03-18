/**************************************************************************
Source file	: DocMap.cc
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	: 		Words
			> Implementation of methods of class Word, which is used to
			represent the words of query we need to search. It works as
			an array of char* , that means pointers to char* , which
			help us to insert a word, check if a word is already in
			the array etc.

					Doc
			> Implementation of methods of class Doc, which is used to
			represent each document of of the input docfile. It works as
			an array of char, which help us to store the number of words in
			this document as well as to get the document itself ( that means
			a pointer to this document -char *- ).

					DocMap
			> Implementation of methods of class DocMap, which is used
			to store all documents of the input docfile. It works as an
			array of pointers to Doc objects ( Doc** ). It help us to
			insert a document, print a document ( underlining the words
			we found ), get the number of all documents, get the number
			of total words in all documents as well as get the number of
			words in a specific document.

***************************************************************************/

#include <cstring>
#include <sys/ioctl.h>
#include <iostream>

#include "DocMap.h"

using namespace std;

#include <cstdlib>
#define CHECK_OR_EXIT(value)     \
{                           \
	if (value == NULL) {      \
		cout << "Error at memory allocation! New() returned NULL! Program must exit!!" << endl;\
		exit(EXIT_FAILURE);           \
	}                         \
}

/* Initialize Words data structure */
Words::Words( int n )
:num_of_words(n)
{

	words_map = new char* [ n ];
	CHECK_OR_EXIT(words_map);

	for( int i = 0; i < num_of_words; i++ ){
		words_map[i] = NULL;
	}

}

/* Destroy Words data structure */
Words::~Words(){

	for( int i = 0; i < num_of_words; i++ ){
		if( words_map[i] != NULL ){
			delete[] words_map[i];
		}
	}

	delete[] words_map;

}

/* Insert word in words_map at index position */
int Words::InsertWord( char *word_to_insert, int index ){

	if( (index < 0) || (index >= num_of_words) ){
		return -1;
	}

	if( words_map[index] != NULL ){
		return -2;
	}

	words_map[index] = new char [ strlen(word_to_insert) + 1 ];
	CHECK_OR_EXIT(words_map[index]);

	strcpy(words_map[index],word_to_insert);

	return 1;

}

/* Return size of words_map */
int Words::GetSize(){
	return num_of_words;
}

/* Checking if word_to_check is in words_map */
bool Words::IsWordIn( char *word_to_check ){

	for( int i = 0; i < num_of_words; i++ ){
		if( words_map[i] != NULL ){
			if( strcmp(words_map[i],word_to_check) == 0 ){
				return true;
			}
		}
	}

	return false;
}

char* Words::GetWord( int index ){

	if( (index >= 0) && (index < num_of_words) ){
		if( words_map[index] != NULL ){
			return words_map[index];
		}
	}

	return NULL;

}

Doc::Doc( char *doc_to_insert )
:num_of_words(0)
{
	my_doc = new char[ strlen(doc_to_insert) + 1 ];
	CHECK_OR_EXIT(my_doc);
	strcpy(my_doc,doc_to_insert);
}

Doc::~Doc(){
	delete[] my_doc;
}

char* Doc::GetDoc(){
	return my_doc;
}

int Doc::GetWordsNum(){
	return num_of_words;
}

void Doc::SetWordsNum( int num ){
	num_of_words = num;
}

/* Initialize DocMap data structure */
DocMap::DocMap( int num_of_docs )
:size(num_of_docs),words_count(0)
{

	docs = new Doc* [ size ];
	CHECK_OR_EXIT(docs);

	for( int i = 0; i < size; i++ ){
		docs[i] = NULL;
	}

}

/* Destroy DocMap data structure */
DocMap::~DocMap(){

	for( int i = 0; i < size; i++ ){
		if( docs[i] != NULL ){
			delete docs[i];
		}
	}

	delete[] docs;

}

/* Insert given doc_to_insert document at index position */
int DocMap::InsertDoc( char *doc_to_insert, int index ){

	if( !IsIndexIn(index) ){
		return -1;
	}

	if( docs[index] == NULL ){

		docs[index] = new Doc( doc_to_insert );
		CHECK_OR_EXIT(docs[index]);

	}
	else{
		return -2;
	}

	return 1;
}

/* Print document with index id and highlight the words_to_highlight Words */
int DocMap::PrintDoc( Words &words_to_highlight, int index, char *special_info ){

	char *highlighting_string = NULL;

	if( !IsIndexIn(index) ){
		return -1;
	}

	if( HighlightText(docs[index]->GetDoc(), &highlighting_string, words_to_highlight) != 1 ){
		return -2;
	}

	if( PrintHighlightedText( docs[index]->GetDoc(), highlighting_string , special_info) != 1 ){
		return -4;
	}

	delete[] highlighting_string;

	return 1;
}

/* Checking if index is in the range of valid indexes */
bool DocMap::IsIndexIn( int index_to_check ){
	return ( (index_to_check >= 0) && (index_to_check < size) );
}

/* Constructing highlighting_string given original string, words to highlight and special info string */
int DocMap::HighlightText( char *original, char **highlighting_string, Words &words_to_highlight ){

	char *word;
	int offset,offset_original;
	char *temp = NULL;

	if( (*highlighting_string) != NULL ){
		return -1;
	}

	(*highlighting_string) = new char[strlen(original) + 1];
	CHECK_OR_EXIT((*highlighting_string));

	/* We need a copy of document as we will use strtok. */
	temp = new char[strlen(original) + 1];
	CHECK_OR_EXIT(temp);
	strcpy(temp,original);

	word = strtok(temp," \t");

	offset = 0;
	offset_original = 0;

	while( word != NULL ){

		/* Copy spaces or tabs till we find the beginning of the word */
		while( (original[offset_original] == ' ') || (original[offset_original] == '\t') ){
			memset((*highlighting_string) + offset,original[offset_original],1);
			offset++;
			offset_original++;
		}

		if( words_to_highlight.IsWordIn(word) ){ /* Write ^^^^ */

			memset((*highlighting_string) + offset,'^',strlen(word));
			offset += strlen(word);
			offset_original += strlen(word);

		}
		else{ /* Write spaces */

			memset((*highlighting_string) + offset,' ',strlen(word));
			offset += strlen(word);
			offset_original += strlen(word);

		}

		word = strtok(NULL," \t");

	}

	/* Write spaces/tabs which may exist after the last word of the document */
	if( offset < ( (int) strlen(original) ) ){
		memset((*highlighting_string) + offset,' ',strlen(original) - offset );
	}

	(*highlighting_string)[strlen(original)] = '\0';

	delete[] temp;

	return 1;
}

/* Printing document text and special info at the beginning, with ^^^ above the words we need to mark.*/
int DocMap::PrintHighlightedText( char *text, char *highlighting_string, char *special_info ){

	struct winsize ws;
	int terminal_width;
	int counter_original,counter_highlight,counter_width;
	bool first_time = true;
	char *temp = NULL;
	char *word;

	if( ioctl(1,TIOCGWINSZ,&ws) == 0 ){ /* File descriptor of STDOUT is 1 */
		terminal_width = ws.ws_col;
	}
	else{
		return -1;
	}

	/* We need a copy of document as we will use strtok. */
	temp = new char[strlen(text) + 1];
	CHECK_OR_EXIT(temp);
	strcpy(temp,text);

	word = strtok(temp," \t");

	counter_width = 0;
	counter_original = 0;
	counter_highlight = 0;

	/* Print special_info */
	cout << special_info ;

	counter_width += strlen(special_info);

	while( word != NULL ){

		if( !first_time ){

			/* Print strlen(special_info) spaces so as to have alignment. */
			for( int i=0; i<( (int) strlen(special_info) ); i++ ){
				cout << " ";
			}

			counter_width += strlen(special_info);

		}

		/* Print words or spaces/tabs of original text */
		while( (counter_original < ( (int)  strlen(text) ) ) && (counter_width < terminal_width) && (word != NULL) ){

			/* Print spaces or tabs till we find the beginning of the word */
			while( ( (text[counter_original] == ' ') || (text[counter_original] == '\t') ) && (counter_width < terminal_width) ){
				cout << text[counter_original];
				counter_width++;
				counter_original++;
			}

			/* Print word if there is space for it, else break */
			if( ( ( (int) strlen(word) ) + counter_width) <= terminal_width ){
				cout << word;
				counter_original += strlen(word);
				counter_width += strlen(word);
				word = strtok(NULL," \t");
			}
			else{
				break;
			}

		}

		cout << endl;

		counter_width = 0;

		/* Print strlen(special_info) spaces so as to have alignment. */
		for( int i=0; i<( (int) strlen(special_info) ); i++ ){
			cout << " ";
		}

		counter_width += strlen(special_info);

		for( int i=counter_highlight; i<counter_original; i++ ){
			cout << highlighting_string[counter_highlight];
			counter_highlight ++;
			counter_width ++;
		}

		cout << endl;
		counter_width = 0;

		first_time = false;
	}

	delete[] temp;

	return 1;

}

/* Return size of DocMap data structure */
int DocMap::GetSize(){
	return size;
}

int DocMap::SetDocCount( int index, int num_of_words ){

	if( !IsIndexIn(index) ){
		return -1;
	}

	docs[index]->SetWordsNum(num_of_words);

	return 1;

}

int DocMap::GetDocCount( int index ){

	if( !IsIndexIn(index) ){
		return -1;
	}

	return docs[index]->GetWordsNum();

}

int DocMap::GetWordCount( ){
	return words_count;
}

void DocMap::SetWordCount( int num_of_words ){
	words_count = num_of_words;
}
