/**************************************************************************
Source file	: Trie.cc
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	:

***************************************************************************/

#include <iostream>
#include <cstring>

using namespace std;

#include "Trie.h"


TrieNode::TrieNode( char symbol_to_set )
:child(NULL),next(NULL),symbol(symbol_to_set)
{

}

TrieNode::~TrieNode(){

	if( child != NULL ){
		delete child;
	}

	if( next != NULL ){
		delete next;
	}

	cout << "TrieNode with symbol " << symbol << " will be destroyed!" << endl;

}

TrieNode* TrieNode::GetChild(){
	return child;
}

TrieNode* TrieNode::GetNext(){
	return next;
}

void TrieNode::SetChild( TrieNode *my_child ){
	child = my_child;
}

void TrieNode::SetNext( TrieNode *my_next ){
	next = my_next;
}

PostingList* TrieNode::GetPostList(){
	return NULL;
}

char TrieNode::GetSymbol(){
	return symbol;
}

int TrieNode::GetDocFrequency(){
	return -1;
}

void TrieNode::PrintPL(){

}

int TrieNode::GetTermFreq( int doc_id ){
	return -1;
}

void TrieNode::InsertDocId( int doc_id_to_insert ){

}

NonFinalTrieNode::NonFinalTrieNode( char symbol_to_set )
:TrieNode(symbol_to_set)
{

}

NonFinalTrieNode::~NonFinalTrieNode(){

}

FinalTrieNode::FinalTrieNode( char symbol_to_set )
:TrieNode(symbol_to_set)
{
	my_post_list = new PostingList();
}

FinalTrieNode::~FinalTrieNode(){
	delete my_post_list;
}

PostingList* FinalTrieNode::GetPostList(){
	return my_post_list;
}

int FinalTrieNode::GetDocFrequency(){
	return my_post_list->GetDocFrequency();
}

void FinalTrieNode::PrintPL(){
	cout << "|" << endl << "--> ";
	my_post_list->Print();
}

int FinalTrieNode::GetTermFreq( int doc_id ){
	return my_post_list->GetTermFreq(doc_id);
}

void FinalTrieNode::InsertDocId( int doc_id_to_insert ){
	my_post_list->Insert(doc_id_to_insert);
}

Trie::Trie()
:first(NULL),total_words(0)
{

}

Trie::~Trie(){

	if( first != NULL ){
		delete first;
	}

}

void Trie::Insert( char *word_to_insert, int doc_id_to_insert ){

	TrieNode *current;

	if( IsEmpty() ){
		InsertFirstWord(word_to_insert,doc_id_to_insert);
		/* VVVVVVVVVVV FOR DEBUGGING VVVVVVVVVV */
		current = first;
		while( current->GetChild() != NULL ){
			cout << current->GetSymbol() << " - ";
			current = current->GetChild();
		}
		//we reached final node
		cout << current->GetSymbol() << endl;
		current->PrintPL();
		/* ^^^^^^^^^^ FOR DEBUGGING ^^^^^^^^^^^^ */
	}
	else{

	}

}

void Trie::InsertFirstWord( char *word_to_insert, int doc_id_to_insert ){

	TrieNode *current;
	TrieNode *temp;

	if( strlen(word_to_insert) == 1 ){ /* First will point to a final node */

		first = new FinalTrieNode( word_to_insert[0] );
		first->InsertDocId(doc_id_to_insert);

	}
	else{

		first = new NonFinalTrieNode( word_to_insert[0] );
		current = first;

		/* Make NonFinalTrieNodes for all letters except last letter */
		for( int i = 1; i < ( (int) (strlen(word_to_insert) - 1) ); i++  ){
			temp = new NonFinalTrieNode( word_to_insert[i] );
			current->SetChild(temp);
			current = temp;
		}

		temp = new FinalTrieNode( word_to_insert[strlen(word_to_insert)-1] );
		temp->InsertDocId(doc_id_to_insert);
		current->SetChild(temp);

	}

}

bool Trie::IsEmpty(){
	return ( first == NULL );
}

PostingList* Trie::GetPostList( char *word_to_find ){
	return NULL;
}

void Trie::PrintAllDf(){

}

void Trie::PrintSpecificDf( char *word_to_print ){

}

void Trie::PrintTermFreq( char *word_to_print, int doc_id_to_print ){

}
