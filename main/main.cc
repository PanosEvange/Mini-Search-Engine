/**************************************************************************
Source file	: main.cc
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	: > Management of arguments
			  > Calling init and destroy functions of structures
			  > Calling store_docs functions
			  > Calling prompt function

***************************************************************************/

#include <cstring>
#include <iostream>
using namespace std;

#include "../ManageFuns/ManageFuns.h"

int main(int argc, char const *argv[]) {

	int top_results;
	int error;
	FileInfo my_file_info;
	my_file_info.number_of_rows = 0;
	my_file_info.file_name = NULL;

	error = ArgumentManagement( argc, argv, &my_file_info.file_name, &top_results );
	switch (error) {
		case -1:	/* Wrong arguments */
				cout << "Wrong arguments. Please run again in this way (in any order): " << argv[0] << " [-k K] -i docfile " << endl;
				return -1;
		case -2:	/* File not exists */
				cout << "File not exists. Please run again giving a valid file name." << endl;
				return -2;
		case -3:	/* Invalid value of K argument */
				cout << "Invalid value of K argument. Please run again giving a valid value ( K > 0 )." << endl;
				return -3;
		case -4:	/* Other error */
				cout << "Something went wrong. Please run again in this way (in any order): " << argv[0] << " [-k K] -i docfile " << endl;
				return -4;
	}

	error = GetFileInfo(my_file_info);
	if( error == -1 ){
		cout << "Invalid id format in given docfile!" << endl;
		delete[] my_file_info.file_name;
		return -5;
	}

	/* Create Data structures */
	DocMap my_doc_map(my_file_info.number_of_rows);
	Trie my_trie;

	/* Insert docs into DocMap and words into Trie */
	error = InsertDocs(my_doc_map,my_trie,my_file_info);
	if( error != 1 ){
		cout << "Error occured when inserting docs int DocMap and words into Trie!" << endl;
		delete[] my_file_info.file_name;
		return -6;
	}

	/* Execute user options */
	error = PromptMode( my_doc_map, my_trie );
	if( error != 1 ){
		cout << "Error occured in prompt mode!" << endl;
		delete[] my_file_info.file_name;
		return -7;
	}

	/* Delete */
	delete[] my_file_info.file_name;

	return 0;
}
