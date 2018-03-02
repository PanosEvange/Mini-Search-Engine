/**************************************************************************
Source file	: main.c
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	: > Management of arguments
			  > Calling init and destroy functions of structures
			  > Calling store_docs functions
			  > Calling prompt function

***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../manageFuns/manageFuns.h"


int main(int argc, char const *argv[]) {

	char* inputFileName = NULL;
	int topResults;
	int error;

	error = argumentManagement( argc, argv, &inputFileName, &topResults );

	switch (error) {
		case -1:	/* Wrong arguments */
				printf("Wrong arguments. Please run again in this way (in any order): %s [-k K] -i docfile \n",argv[0]);
				return -1;
		case -2:	/* File not exists */
				printf("File not exists. Please run again giving a valid file name.\n" );
				return -2;
		case -3:	/* Invalid value of K argument */
				printf("Invalid value of K argument. Please run again giving a valid value ( K > 0 ).\n" );
				return -3;
		case -4:	/* Other error */
				printf("Something went wrong. Please run again in this way (in any order): %s [-k K] -i docfile \n",argv[0]);
				return -4;
	}

	/* Free */
	if( inputFileName != NULL ){
		free(inputFileName);
	}
	else{
		return -5;
	}

	return 0;
}
