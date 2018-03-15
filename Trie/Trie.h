/***************************************************************************************
Header file : Trie.h
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description :



****************************************************************************************/
#ifndef TRIE_H
#define TRIE_H

#include "../PostingList/PostingList.h"
#include "../PostingList/DocInfo.h"

class TrieNode{

private:
		TrieNode *child;
		TrieNode *next;
		char symbol;

public:
		TrieNode( char symbol_to_set );
		virtual ~TrieNode();
		TrieNode* GetChild();
		TrieNode* GetNext();
		void SetChild( TrieNode *my_child );
		void SetNext( TrieNode *my_next );
		virtual PostingList* GetPostList(); /* Default GetPostList */
		char GetSymbol();
		virtual int GetDocFrequency();
		virtual void PrintPL();
		virtual int GetTermFreq( int doc_id );
		virtual void InsertDocId( int doc_id_to_insert );
		virtual int Print( char* word_so_far = NULL );
};

class NonFinalTrieNode : public TrieNode {

public:
		NonFinalTrieNode( char symbol_to_set );
		~NonFinalTrieNode();
		int Print( char* word_so_far = NULL );
};

class FinalTrieNode : public TrieNode {

private:
		PostingList *my_post_list;

public:
		FinalTrieNode( char symbol_to_set );
		~FinalTrieNode();
		PostingList* GetPostList();
		int GetDocFrequency();
		void PrintPL();
		int GetTermFreq( int doc_id );
		void InsertDocId( int doc_id_to_insert );
		int Print( char* word_so_far = NULL );
};

class Trie{

private:
		TrieNode *first;
		int total_words;
		void InsertFirstWord( char *word_to_insert, int doc_id_to_insert );
		TrieNode* InsertNonFinalNodes( char *word_to_insert, int start, TrieNode* current );
		TrieNode* FindChild( char letter, TrieNode *current  );
		int FindFinalChild( char letter, TrieNode *current, TrieNode* &previous_of_child  );
		int FindFirstFinalChild( char letter, TrieNode* &previous_of_child  );
		TrieNode* FindFirstChild( char letter );
public:
		Trie();
		~Trie();
		void Insert( char *word_to_insert, int doc_id_to_insert );
		bool IsEmpty();
		PostingList* GetPostList( char *word_to_find );
		void PrintAllDf();
		void PrintSpecificDf( char *word_to_print );
		void PrintTermFreq( char *word_to_print, int doc_id_to_print );

};

#endif /* TRIE_H */
