/**************************************************************************
Source file	: trie.c
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	: >
			  >
			  >
			  >

***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

int trie_Init( trie_Header **header ){

	if( (*header) != NULL ){
		return -1;
	}

	(*header) = malloc( sizeof(trie_Header) );

	if( (*header) == NULL ){
		return -2;
	}

	(*header)->firstNode = NULL;
	((*header)->firstFinal) = -1;

	return 1;

}

int trie_Destroy( trie_Header **header ){

	if( (*header) == NULL ){
		return -1;
	}

	return 1;
}

int trie_Insert( trie_Header *header, char *wordToInsert, int docId ){

	trie_FinalNode **currentFinal;
	trie_Node **currentNonFinal;
	
	docInfo infoToInsert;
	infoToInsert.id = docId;
	infoToInsert.termFrequency = 1;

	if( header == NULL ){
		return -1;
	}

	if( trie_IsEmpty(header) ){

		if( strlen(wordToInsert) == 1 ){ /* firstNode will be trie_FinalNode */

			header->firstFinal = 1;

			currentFinal = (trie_FinalNode **) &(header->firstNode);
			(*currentFinal) = malloc(sizeof(trie_FinalNode));
			(*currentFinal)->symbol = wordToInsert[0];
			(*currentFinal)->myPostList = NULL;
			(*currentFinal)->next = NULL;
			(*currentFinal)->children = NULL;
			(*currentFinal)->nextFinal = -1;
			(*currentFinal)->childrenFinal = -1;

			if( PL_Init( &( (*currentFinal)->myPostList ) )  != 1 ){
				return -2;
			}

			if( PL_InsertAtEnd( (*currentFinal)->myPostList,infoToInsert )  != 1 ){
				return -3;
			}

			printf("h PL einai: \n" );
			PL_Print((*currentFinal)->myPostList);

		}
		else{ /* firstNode will be a non final trie_Node */

			header->firstFinal = 0;

			currentNonFinal = (trie_Node **) &(header->firstNode);
			(*currentNonFinal) = malloc(sizeof(trie_Node));
			(*currentNonFinal)->symbol = wordToInsert[0];
			(*currentNonFinal)->next = NULL;
			(*currentNonFinal)->nextFinal = -1;

			/* Make non-final nodes, which will be the internal letters of the word */
			for( int i = 1; i < strlen(wordToInsert)-1; i++ ){
				(*currentNonFinal)->childrenFinal = 0;
				currentNonFinal = (trie_Node **) &((*currentNonFinal)->children);
				(*currentNonFinal) = malloc(sizeof(trie_Node));
				(*currentNonFinal)->symbol = wordToInsert[i];
				(*currentNonFinal)->next = NULL;
				(*currentNonFinal)->nextFinal = -1;
			}

			/* Now we are at the last letter so childer will be a final node */
			(*currentNonFinal)->childrenFinal = 1;
			currentFinal = (trie_FinalNode **) &((*currentNonFinal)->children);

			(*currentFinal) = malloc(sizeof(trie_FinalNode));
			(*currentFinal)->symbol = wordToInsert[strlen(wordToInsert)-1];
			(*currentFinal)->myPostList = NULL;
			(*currentFinal)->next = NULL;
			(*currentFinal)->children = NULL;
			(*currentFinal)->nextFinal = -1;
			(*currentFinal)->childrenFinal = -1;

			if( PL_Init( &( (*currentFinal)->myPostList ) )  != 1 ){
				return -2;
			}

			if( PL_InsertAtEnd( (*currentFinal)->myPostList,infoToInsert )  != 1 ){
				return -3;
			}

			/* VVVVVVVVVVV FOR DEBUGGING VVVVVVVVVV */
			printf("h PL einai: \n" );
			PL_Print((*currentFinal)->myPostList);

			currentNonFinal = (trie_Node **) &(header->firstNode);
			while( (*currentNonFinal)->childrenFinal == 0 ){
				printf(" -> %c ",(*currentNonFinal)->symbol );
				currentNonFinal = (trie_Node **) &((*currentNonFinal)->children);
			}
			printf(" -> %c ",(*currentNonFinal)->symbol );
			currentFinal = (trie_FinalNode **) &((*currentNonFinal)->children);
			printf(" -> %c ",(*currentFinal)->symbol );
			printf("\n");
			/* ^^^^^^^^^^ FOR DEBUGGING ^^^^^^^^^^^^ */

		}

	}
	else{

	}


	return 1;
}

int trie_GetPostList( trie_Header *header, char *wordToFind ){

	if( header == NULL ){
		return -1;
	}

	return 1;
}

int trie_PrintAllDf( trie_Header *header ){

	if( header == NULL ){
		return -1;
	}

	return 1;
}

int trie_PrintSpecificDf( trie_Header *header, char *wordToPrint ){

	if( header == NULL ){
		return -1;
	}

	return 1;
}

int trie_PrintTermFreq( trie_Header *header, char *wordToPrint, int docIdToPrint ){

	if( header == NULL ){
		return -1;
	}

	return 1;
}

char trie_IsEmpty( trie_Header *header ){

	return ( (header->firstNode) == NULL );

}
