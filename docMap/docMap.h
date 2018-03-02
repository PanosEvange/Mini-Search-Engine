/***************************************************************************************
Header file : docMap.h
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description :



****************************************************************************************/
#ifndef DOC_MAP_H
#define DOC_MAP_H

typedef char ** docMap;

int docMap_Init( docMap *currentMap, int numOfDocs );
int docMap_Destroy( docMap *currentMap, int numOfDocs );
int docMap_InsertDoc( docMap *currentMap, char *docToInsert, int index );
int docMap_PrintDoc( docMap *currentMap, char **wordsToHighlight, int index );

#endif /* DOC_MAP_H */
