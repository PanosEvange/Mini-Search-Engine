/**************************************************************************
Source file	: postingList.c
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	: > PL_Init :
			  > PL_Destroy :
			  > PL_InsertAtEnd :
			  > PL_GetDocFrequency :
			  > PL_GetTermFrequency :
			  > PL_IsEmpty :
			  > PL_IncrLastTermFreq :
			  > PL_Print :
			  >
			  >

***************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "postingList.h"

/* Initialization of given posting list */
int PL_Init( PL_Header **header ){

	if( (*header) != NULL ){
		return -1;
	}

	*header = malloc( sizeof(PL_Header) );

	if( (*header) == NULL ){
		return -2;
	}

	(*header)->first = NULL;
	(*header)->last = NULL;
	(*header)->docFrequency = 0;

	return 1;
}

/* Destruction of given posting list */
int PL_Destroy( PL_Header **header ){

	PL_Node *current;

	if( (*header) == NULL ){
		return -1;
	}

	while( ((*header)->first) != NULL ){

		current = (*header)->first;
		(*header)->first = current->next;
		free(current);

	}

	free(*header);

	*header = NULL;

	return 1;
}

/* Insert infoToInsert docInfo at the end of given posting list */
int PL_InsertAtEnd( PL_Header *header, docInfo infoToInsert ){

	if( header == NULL ){
		return -1;
	}

	if( PL_IsEmpty(header) ){

		header->first = malloc( sizeof(PL_Node) );
		if( header->first == NULL ){
			return -2;
		}

		docInfo_Set(&(header->first->myInfo),infoToInsert);

		header->last = header->first;
		header->first->next = NULL;
		header->docFrequency ++;

	}
	else{

		header->last->next = malloc( sizeof(PL_Node) );
		if( (header->last->next) == NULL ){
			return -2;
		}

		docInfo_Set(&(header->last->next->myInfo),infoToInsert);

		header->last = header->last->next;
		header->last->next = NULL;
		header->docFrequency ++;

	}

	return 1;

}

/* Return docFrequency of given posting list */
int PL_GetDocFrequency( PL_Header *header ){

	if( header == NULL ){
		return -1;
	}

	return header->docFrequency;

}

/* Find and return termFrequency of given docId  */
int PL_GetTermFrequency( PL_Header *header, int docId ){

	PL_Node *current;

	if( header == NULL ){
		return -2;
	}

	if( PL_IsEmpty(header) ){
		return -3;
	}

	/* Find given docId */
	current = header->first;
	while( current != NULL ){

		if( docId <= ( docInfo_GetDocId(current->myInfo) ) ){ /* It means that we found given docId or there is no such a docId */

			if( docId == ( docInfo_GetDocId(current->myInfo) ) ){
				return docInfo_GetTermFreq(current->myInfo);
			}
			else{	/* docIds are sorted, so there is no such a docId */
				return -1;	/* Not found */
			}

		}

		current = current->next;
	}

	return -1; /* Not found */
}

/* Return 0 if given posting list is empty, otherwise 1 */
char PL_IsEmpty( PL_Header *header ){

	return ( header->first == NULL );

}

/* Increment of termFrequency of last node of given posting list */
int PL_IncrLastTermFreq( PL_Header *header ){

	if( header == NULL ){
		return -1;
	}

	if( PL_IsEmpty(header) ){
		return -2;
	}

	docInfo_IncrTermFreq(&(header->last->myInfo));

	return 1;

}

/* For debugging purposes */
int PL_Print( PL_Header *header ){

	PL_Node* current;

	if( header == NULL ){
		return -1;
	}

	printf(" PL( %d ) ",header->docFrequency );

	current = header->first;
	while( current != NULL ){

		printf("-> [ %d , %d ]  ",docInfo_GetDocId(current->myInfo),docInfo_GetTermFreq(current->myInfo) );

		current = current->next;

	}

	printf("\n");

	return 1;

}
