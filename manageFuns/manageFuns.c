/**************************************************************************
Source file	: manageFuns.c
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	: > argumentManagement : checks if arguments are ok and returning
				corresponding error if something is wrong
			  >
			  >
			  >

***************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "manageFuns.h"

/* Checking arguments and returning error if something is wrong */
int argumentManagement( int argNum, char const **arguments, char **inputFileName, int *k ){

	char arg1_ok = 0;
	char arg2_ok = 0;
	int i=0;

	if( argNum == 3 ){ /* We should get only -i docfile as argument */
		if( strcmp(arguments[1],"-i") == 0 ){

			/* Check if file exists */
			if( access( arguments[2], F_OK ) != 0 ) {     /* file doesn't exist */
				return -2;
			}

			if( *inputFileName == NULL ){
				*inputFileName = malloc( (strlen(arguments[2]) + 1) * sizeof(char) );
				strcpy(*inputFileName,arguments[2]);
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
	else if( argNum == 5 ){ /* We should get  -i docfile -k K in any order */

		for( i = 1; i < argNum; i++ ){

			if( strcmp(arguments[i],"-i") == 0 ){

				if( arg1_ok == 1 ){ /* Cannot give 2 times -i docfile */

					if( *inputFileName != NULL ){
						free(*inputFileName);
						*inputFileName = NULL;
					}

					return -1;

				}

				i++;

				/* Check if file exists */
				if( access( arguments[i], F_OK ) != 0 ) {     /* file doesn't exist */
					return -2;
				}

				if( *inputFileName == NULL ){
					*inputFileName = malloc( (strlen(arguments[i]) + 1) * sizeof(char) );
					strcpy(*inputFileName,arguments[i]);
				}
				else{
					return -4;
				}

				arg1_ok = 1;

			}
			else if( strcmp(arguments[i],"-k") == 0 ){

				if( arg2_ok == 1 ){ /* Cannot give 2 times -k K */
					return -1;
				}

				i++;

				*k = atoi(arguments[i]);
				if( *k <= 0 ){
					return -3;
				}

				arg2_ok = 1;

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
