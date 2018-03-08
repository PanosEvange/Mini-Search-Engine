/***************************************************************************************
Header file : trie.h
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description :



****************************************************************************************/
#ifndef TRIE_H
#define TRIE_H

#include "../postingList/postingList.h"
#include "../postingList/docInfo.h"

typedef struct trie_Node{
	void *children; /* Points either to a trieNode or a finalTrieNode */
	void *next; /* Points either to a trieNode or a finalTrieNode */
	char childrenFinal; /* 1 if children is finalTrieNode, otherwise 0 */
	char nextFinal; /* 1 if next is finalTrieNode, otherwise 0 */
	char symbol;
} trie_Node;

typedef struct trie_FinalNode{
	void *children; /* Points either to a trieNode or a finalTrieNode */
	void *next; /* Points either to a trieNode or a finalTrieNode */
	char childrenFinal; /* 1 if children is finalTrieNode, otherwise 0 */
	char nextFinal; /* 1 if next is finalTrieNode, otherwise 0 */
	char symbol;
	PL_Header *myPostList;
} trie_FinalNode;

typedef struct trie_Header{
	void *firstNode; /* Points either to a trieNode or a finalTrieNode */
	char firstFinal; /* 1 if firstNode is finalTrieNode, otherwise 0 */
} trie_Header;

int trie_Init( trie_Header **header );
int trie_Destroy( trie_Header **header );
int trie_Insert( trie_Header *header, char *wordToInsert, int docId );
int trie_GetPostList( trie_Header *header, char *wordToFind );
int trie_PrintAllDf( trie_Header *header );
int trie_PrintSpecificDf( trie_Header *header, char *wordToPrint );
int trie_PrintTermFreq( trie_Header *header, char *wordToPrint, int docIdToPrint );
char trie_IsEmpty( trie_Header *header );

#endif /* TRIE_H */
