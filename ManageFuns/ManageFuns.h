/***************************************************************************************
Header file : ManageFuns.h
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description :



****************************************************************************************/
#ifndef MANAGE_H
#define MANAGE_H

#include "../Trie/Trie.h"
#include "../DocMap/DocMap.h"
#include "../Heap/Heap.h"

typedef struct FileInfo{
	int number_of_rows;
	char *file_name;
} FileInfo;

typedef struct ScoreInfo{
	double score;
	bool is_relevant;
} ScoreInfo;

int ArgumentManagement( int arg_num, char const **arguments, char **input_file_name, int *k );
int GetFileInfo( FileInfo &current_file_info );
int InsertDocs( DocMap &current_doc_map, Trie &current_trie, FileInfo &current_file_info );
int InsertWords( char *doc_to_split, int id, Trie &current_trie );
int GetFinalDoc( char *doc_to_format, int last_char_pos, char* &final_doc );
int PromptMode( DocMap &current_doc_map, Trie &current_trie, int top_k );
int FindWordsNumber( char *search_string_to_check );
int Search( DocMap &current_doc_map, Trie &current_trie, Words &words_to_search, int top_k );
int PrintTopK( DocMap &current_doc_map, class Heap &current_heap, Words &words_to_search, int top_k );
int DigitCount( int num_to_check );

#endif /* MANAGE_H */
