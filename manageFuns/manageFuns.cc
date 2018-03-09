/**************************************************************************
Source file	: manageFuns.cc
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	: > argumentManagement : checks if arguments are ok and returning
				corresponding error if something is wrong
			  >
			  >
			  >

***************************************************************************/

#include <unistd.h>
#include <cstring>
#include <iostream>
#include <cstdlib>

using namespace std;

#include "manageFuns.h"

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
