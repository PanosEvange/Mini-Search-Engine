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

	char* input_file_name = NULL;
	int top_results;
	int error;

	error = ArgumentManagement( argc, argv, &input_file_name, &top_results );

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

	cout << "K is " << top_results << " and input_file_name is " << input_file_name << endl;

	/* Delete */
	if( input_file_name != NULL ){
		delete[] input_file_name;
	}
	else{
		return -5;
	}

	return 0;
}
