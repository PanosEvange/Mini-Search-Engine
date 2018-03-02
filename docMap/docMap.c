/**************************************************************************
Source file	: docMap.c
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	: > docMap_Init :
			  > docMap_Destroy :
			  > docMap_InsertDoc :
			  > docMap_PrintDoc :
			  >
			  >

***************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "docMap.h"

/* Initialize docMap data structure */
int docMap_Init( docMap *currentMap, int numOfDocs ){

	if( *currentMap == NULL ){

		*currentMap = malloc( numOfDocs * sizeof( char * ) );

		if( *currentMap == NULL ){
			return -1;
		}

		for( int i = 0; i < numOfDocs; i++ ){
			(*currentMap)[i] = NULL;
		}

	}
	else{
		return -2;
	}

	return 1;
}

/* Destroy docMap data structure */
int docMap_Destroy( docMap *currentMap, int numOfDocs ){

	if( *currentMap != NULL ){

		for( int i = 0; i < numOfDocs; i++ ){

			if( (*currentMap)[i] != NULL ){
				free((*currentMap)[i]);
			}
			else{
				return -2;
			}

		}
		free(*currentMap);

	}
	else{
		return -1;
	}

	return 1;
}

/* Insert given docToInsert document into currentMap docMap */
int docMap_InsertDoc( docMap *currentMap, char *docToInsert, int index ){

	if( (*currentMap)[index] == NULL ){

		(*currentMap)[index] = malloc( ( strlen(docToInsert) + 1 ) * sizeof(char) );

		if( (*currentMap)[index] == NULL ){
			return -1;
		}

		strcpy((*currentMap)[index],docToInsert);

	}
	else{
		return -2;
	}

	return 1;
}

/* Print document with index id and highlight the wordsToHighlight words */
int docMap_PrintDoc( docMap *currentMap, char **wordsToHighlight, int index ){

	printf("document with id %d is -%s-\n",index,(*currentMap)[index] );

	return 1;
}
