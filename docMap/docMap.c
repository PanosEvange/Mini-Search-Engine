/**************************************************************************
Source file	: docMap.c
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	: > docMap_Init :
			  > docMap_Destroy :
			  > docMap_InsertDoc :
			  > docMap_PrintDoc :
			  > docMap_IsWordIn :
			  >

***************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "docMap.h"

/* Initialize docMap data structure */
int docMap_Init( docMap *currentMap, int numOfDocs ){

	if( currentMap->map == NULL ){

		if( numOfDocs > 0 ){
			currentMap->size = numOfDocs;
		}
		else{
			return -3;
		}

		currentMap->map = malloc( (currentMap->size) * sizeof( char * ) );

		if( currentMap->map == NULL ){
			return -1;
		}

		for( int i = 0; i < (currentMap->size); i++ ){
			(currentMap->map)[i] = NULL;
		}

	}
	else{
		return -2;
	}

	return 1;
}

/* Destroy docMap data structure */
int docMap_Destroy( docMap *currentMap ){

	if( currentMap->map != NULL ){

		for( int i = 0; i < (currentMap->size); i++ ){

			if( (currentMap->map)[i] != NULL ){
				free((currentMap->map)[i]);
			}
			else{
				return -2;
			}

		}
		free(currentMap->map);

	}
	else{
		return -1;
	}

	return 1;
}

/* Insert given docToInsert document into currentMap docMap */
int docMap_InsertDoc( docMap currentMap, char *docToInsert, int index ){

	if( !docMap_IsIndexIn(currentMap,index) ){
		return -3;
	}

	if( currentMap.map[index] == NULL ){

		currentMap.map[index] = malloc( ( strlen(docToInsert) + 1 ) * sizeof(char) );

		if( currentMap.map[index] == NULL ){
			return -1;
		}

		strcpy(currentMap.map[index],docToInsert);

	}
	else{
		return -2;
	}

	return 1;
}

/* Print document with index id and highlight the wordsToHighlight words */
int docMap_PrintDoc( docMap currentMap, words wordsToHighlight, int index ){

	char *word;
	char *highlightingString = NULL;
	char *temp = NULL;

	int offset;

	if( !docMap_IsIndexIn(currentMap,index) ){
		return -3;
	}

	/* Print the document as it is */
	printf("%s\n",currentMap.map[index] );

	/* Make highlighting string */
	highlightingString = malloc( ( strlen(currentMap.map[index]) + 1 ) * sizeof(char) );
	temp = malloc( ( strlen(currentMap.map[index]) + 1 ) * sizeof(char) );
	strcpy(temp,currentMap.map[index]);

	word = strtok(temp," ");
	offset = 0;

	while( word != NULL ){
		
		if( docMap_IsWordIn(wordsToHighlight,word) ){ /* Write ^^^^ */

			memset(highlightingString + offset,'^',strlen(word));
			offset += strlen(word);
			memset(highlightingString + offset,' ',1);
			offset ++;

		}
		else{ /* Write spaces */

			memset(highlightingString + offset,' ',strlen(word));
			offset += strlen(word);
			memset(highlightingString + offset,' ',1);
			offset ++;

		}

		word = strtok(NULL," ");

	}

	highlightingString[strlen(currentMap.map[index])] = '\0';

	printf("%s\n",highlightingString );

	free(highlightingString);
	free(temp);

	return 1;
}

/* Checking if wordToCheck word is one of wordsToSearch words */
char docMap_IsWordIn( words wordsToSearch, char *wordToCheck ){

	for( int i = 0; i < wordsToSearch.numOfWords; i++ ){
		if( strcmp(wordsToSearch.wordsMap[i],wordToCheck) == 0 ){
			return 1;
		}
	}

	return 0;
}

/* Checking if index is in the range of valid indexes */
char docMap_IsIndexIn( docMap mapToCheck, int indexToCheck ){

	if( (indexToCheck >= 0) && (indexToCheck < mapToCheck.size) ){
		return 1;
	}
	else{
		return -1;
	}

}
