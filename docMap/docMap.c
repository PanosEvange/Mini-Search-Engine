/**************************************************************************
Source file	: docMap.c
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	: > docMap_Init :
			  > docMap_Destroy :
			  > docMap_InsertDoc :
			  > docMap_PrintDoc :
			  > docMap_IsWordIn :
			  > docMap_IsIndexIn :
			  > docMap_HighlightText :
***************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>

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
int docMap_PrintDoc( docMap currentMap, words wordsToHighlight, int index, char *specialInfo ){

	char *highlightingString = NULL;

	struct winsize ws;
	int terminalWidth;

	if( ioctl(1,TIOCGWINSZ,&ws) == 0 ){ /* File descriptor of STDOUT is 1 */
		terminalWidth = ws.ws_col;
	}
	else{
		return -4;
	}

	//printf("to terminalWidth einai %d \n",terminalWidth );

	if( !docMap_IsIndexIn(currentMap,index) ){
		return -3;
	}

	if( docMap_HighlightText(currentMap.map[index], specialInfo, &highlightingString, wordsToHighlight) != 1 ){
		return -5;
	}

	/* Print the document as it is */
	printf("%s%s\n",specialInfo,currentMap.map[index] );

	printf("%s\n",highlightingString );

	free(highlightingString);

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

/* Constructing highlightingString given original string, words to highlight and special info string */
int docMap_HighlightText( char *original, char *specialInfo, char **highlightingString, words wordsToHighlight ){

	char *word;
	int offset,offsetOriginal;
	char *temp = NULL;

	if( (*highlightingString) == NULL ){
		(*highlightingString) = malloc( ( strlen(original) + strlen(specialInfo) + 1 ) * sizeof(char) );
		if( (*highlightingString) == NULL ){
			return -2;
		}
	}
	else{
		return -1;
	}

	/* We need a copy of document as we will use strtok. */
	temp = malloc( ( strlen(original) + 1 ) * sizeof(char) );
	if( temp == NULL ){
		return -3;
	}

	strcpy(temp,original);

	word = strtok(temp," \t");

	/* Write spaces at the beginning of highlightingString as we have specialInfo */
	memset((*highlightingString),' ',strlen(specialInfo));
	offset = strlen(specialInfo);
	offsetOriginal = 0;

	while( word != NULL ){

		/* Copy spaces or tabs till we find the beginning of the word */
		while( (original[offsetOriginal] == ' ') || (original[offsetOriginal] == '\t') ){
			memset((*highlightingString) + offset,original[offsetOriginal],1);
			offset++;
			offsetOriginal++;
		}

		if( docMap_IsWordIn(wordsToHighlight,word) ){ /* Write ^^^^ */

			memset((*highlightingString) + offset,'^',strlen(word));
			offset += strlen(word);
			offsetOriginal += strlen(word);

		}
		else{ /* Write spaces */

			memset((*highlightingString) + offset,' ',strlen(word));
			offset += strlen(word);
			offsetOriginal += strlen(word);

		}

		word = strtok(NULL," \t");

	}

	/* Write spaces/tabs which may exists after the last word of the document */
	if( offset < ( strlen(original) + strlen(specialInfo) ) ){
		memset((*highlightingString) + offset,' ',( strlen(original) + strlen(specialInfo) ) - offset );
	}

	(*highlightingString)[strlen(original) + strlen(specialInfo)] = '\0';

	free(temp);
	return 1;
}
