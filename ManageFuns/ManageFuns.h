/***************************************************************************************
Header file : ManageFuns.h
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description :



****************************************************************************************/
#ifndef MANAGE_H
#define MANAGE_H

#include "../Trie/Trie.h"
#include "../DocMap/DocMap.h"

typedef struct FileInfo{
	int number_of_rows;
	char *file_name;
} FileInfo;

int ArgumentManagement( int arg_num, char const **arguments, char **input_file_name, int *k );
int GetFileInfo( FileInfo &current_file_info );
int InsertDocs( DocMap &current_doc_map, Trie &current_trie, FileInfo &current_file_info );
//int InsertDocs( FileInfo &current_file_info );
int InsertWords( char *doc_to_split, int id, Trie &current_trie );
char* GetFinalDoc( char *doc_to_format, int last_char_pos );
#endif /* MANAGE_H */
