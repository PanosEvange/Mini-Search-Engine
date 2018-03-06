/***************************************************************************************
Header file : postingList.h
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description :



****************************************************************************************/
#ifndef POST_LIST_H
#define POST_LIST_H
#include "docInfo.h"


typedef struct PL_Node {
	struct PL_Node *next;
	docInfo myInfo;
} PL_Node;

typedef struct PL_Header {
	PL_Node *last;
	PL_Node *first;
	int docFrequency;
} PL_Header;

int PL_Init( PL_Header **header );
int PL_Destroy( PL_Header **header );
int PL_InsertAtEnd( PL_Header *header, docInfo infoToInsert );
int PL_GetDocFrequency( PL_Header *header );
int PL_GetTermFrequency( PL_Header *header, int docId );
char PL_IsEmpty( PL_Header *header );
int PL_IncrLastTermFreq( PL_Header *header );
int PL_Print( PL_Header *header );

#endif /* POST_LIST_H */
