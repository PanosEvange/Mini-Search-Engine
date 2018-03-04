/***************************************************************************************
Header file : docMap.h
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description :



****************************************************************************************/
#ifndef DOC_MAP_H
#define DOC_MAP_H

typedef struct docMap{
	int size;
	char **map;
} docMap;

typedef struct words{
	int numOfWords;
	char **wordsMap;
} words;

int docMap_Init( docMap *currentMap, int numOfDocs );
int docMap_Destroy( docMap *currentMap );
int docMap_InsertDoc( docMap currentMap, char *docToInsert, int index );
int docMap_PrintDoc( docMap currentMap, words wordsToHighlight, int index );
char docMap_IsWordIn( words wordsToSearch, char *wordToCheck );
char docMap_IsIndexIn( docMap mapToCheck, int indexToCheck );

#endif /* DOC_MAP_H */
