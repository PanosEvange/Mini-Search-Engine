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
	TrieNode *child;
	TrieNode *previous_of_child;
	TrieNode *temp;

	int i,rv;

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

		if( strlen(word_to_insert) == 1 ){

			/* We have only one final node which should be inserted ( or increase its PostingList )
			   if exists ) at the "first level" of children nodes */
			rv = FindFirstFinalChild(word_to_insert[0],previous_of_child);
			switch (rv) {
				case 0:	/* Check if first node is already final node, else make it final node */
						break;
				case 1: /* A new final node should be inserted as first node */
						break;
				case 2:
						/* A new final node should be inserted as next of previous_of_child */
						break;
				case 3:
						/* Check if next of previous_of_child is already final node, else make it final node */
						break;
			}

		}
		else{

			/* Find the position/child of first letter */
			child = FindFirstChild(word_to_insert[0]);
			if( child == NULL ){
				/* Insert new node as first node */

				/* Then insert NonFinalTrieNodes as children of first node
					for all letters except last letter */

				/* Insert finalNode for last letter */

			}
			else{
				/* We found child which may have symbol == word_to_insert[0] or
				 	symbol < word_to_insert[0] but child->next symbol > word_to_insert[0] , if
					child->next node exists */
				/* So there are 2 options */
				if( word_to_insert[0] > child->GetSymbol() ){
					/* Insert new node as child->next */

					/* Then insert NonFinalTrieNodes as children of this new node
						for all letters except last letter */

					/* Insert finalNode for last letter */

				}
				else if( word_to_insert[0] == child->GetSymbol() ){

					/* Move to this child */
					current = child;

					/* Then call FindChild for all other letters except last letter */
					for( i = 1; i < strlen(word_to_insert-1); i++ ){

						child = FindChild(word_to_insert[i],current);
						if( child == NULL ){
							/* Insert new node as first child */

							//current = new node / first child
							break;
						}
						else{
							/* We found child which may have symbol == word_to_insert[0] or
							 	symbol < word_to_insert[0] but child->next symbol > word_to_insert[0] , if
								child->next node exists */
							/* So there are 2 options */
							if( word_to_insert[0] > child->GetSymbol() ){
								/* Insert new node as child->next */

								//current = new node/ child->next
								break;
							}
							else if( word_to_insert[0] == child->GetSymbol() ){
								current = child;
								/* Go on to next i */
							}
						}
					}

					if( i < strlen(word_to_insert-1) ){
						/* We should insert NonFinalTrieNodes as childen of current node
						 	for remaining letters and final node for last letter */

						/* We dont have to call FindFinalChild */
					}
					else{
						/* We should only insert final node for last letter */
						/* So we need to call FindFinalChild */
					}


				}

			}

		}

	}

}

/* Find child of current node which has symbol == letter or (symbol < letter and letter < nextSymbol)  */
TrieNode* Trie::FindChild( char letter, TrieNode *current  ){

	char next_symbol;

	if( current->GetChild() == NULL ){ /* Insert new node as first child */
		return NULL;
	}
	else if( letter == current->GetChild()->GetSymbol() ){ /* Move to this child */
		return current->GetChild();
	}
	else if( letter < current->GetChild()->GetSymbol() ){ /* Insert new node as first child */
		return NULL;
	}
	else{ //letter > current->GetChild()->GetSymbol()

		/* Move to first child */
		current = current->GetChild();
		/* Check next children */
		while(1){

			if( current->GetNext() == NULL ){ /* There is no next child to check */
				return current;
			}
			else{

				next_symbol = current->GetNext()->GetSymbol();
				if( letter < next_symbol ){ /* New node should be inserted as current->next, as letter > current_symbol but letter < next_symbol */
					return current;
				}
				else if( letter == next_symbol ){ /* Move to this child */
					return current->GetNext();
				}
				else{
					current = current->GetNext();
				}

			}

		}

	}

}

/* Find previous node of final child of current node which has symbol == letter or (symbol < letter and letter < nextSymbol)  */
int Trie::FindFinalChild( char letter, TrieNode *current, TrieNode* &previous_of_child  ){

	char next_symbol;

	if( current->GetChild() == NULL ){
		previous_of_child = current; /* previous_of_child would be the current node */
		return 0; /* New final node should be inserted as first child */
	}
	else if( letter == current->GetChild()->GetSymbol() ){
		previous_of_child = current; /* previous_of_child would be the current node */
		return 1; /* We should check if this node is already finalNode else we should make it as finalNode */
	}
	else if( letter < current->GetChild()->GetSymbol() ){
		previous_of_child = current; /* previous_of_child would be the current node */
		return 0; /* New final node should be inserted as first child */
	}
	else{ //letter > current->GetChild()->GetSymbol()

		/* Check next children */
		current = current->GetChild();
		while(1){

			if( current->GetNext() == NULL ){ /* There is no next child to check */
				previous_of_child = current; /* previous_of_child would be this current node */
				return 2; /* New final node should be inserted as next of this current node */
			}
			else{

				next_symbol = current->GetNext()->GetSymbol();
				if( letter < next_symbol ){
					previous_of_child = current; /* previous_of_child would be this current node */
					return 2; /* New final node should be inserted as next of this current node */
				}
				else if( letter == next_symbol ){
					previous_of_child = current; /* previous_of_child would be this current node */
					return 3; /* We should check if current->Next node is already finalNode else we should make it as finalNode  */
				}
				else{ //letter > next_symbol
					current = current->GetNext();
				}

			}

		}

	}

}

/* Find previous node of first final child, beggining to check from first node, which has symbol == letter or (symbol < letter and letter < nextSymbol)  */
int Trie::FindFirstFinalChild( char letter, TrieNode* &previous_of_child  ){

	char next_symbol;
	TrieNode* current;

	if( letter == first->GetSymbol() ){
		previous_of_child = NULL; /* there is no previous_of_child  */
		return 0; /* We should check if first node is already finalNode else we should make it as finalNode */
	}
	else if( letter < first->GetSymbol() ){
		previous_of_child = NULL; /* there is no previous_of_child  */
		return 1; /* New final node should be inserted as first node */
	}
	else{ //letter > first->GetSymbol()

		/* Move to first node */
		current = first;
		/* Check next */
		while(1){

			if( current->GetNext() == NULL ){ /* There is no next node to check */
				previous_of_child = current; /* previous_of_child would be this current node */
				return 2; /* New final node should be inserted as next of this current node */
			}
			else{

				next_symbol = current->GetNext()->GetSymbol();
				if( letter < next_symbol ){
					previous_of_child = current; /* previous_of_child would be this current node */
					return 2; /* New final node should be inserted as next of this current node */
				}
				else if( letter == next_symbol ){
					previous_of_child = current; /* previous_of_child would be this current node */
					return 3; /* We should check if current->Next node is already finalNode else we should make it as finalNode  */
				}
				else{ //letter > next_symbol
					current = current->GetNext();
				}

			}

		}

	}

}

/* Find first child, beggining from first node which has symbol == letter or (symbol < letter and letter < nextSymbol)  */
TrieNode* Trie::FindFirstChild( char letter ){

	char next_symbol;
	TrieNode* current;

	if( letter == first->GetSymbol() ){ /* Move to this child */
		return first;
	}
	else if( letter < first->GetSymbol() ){ /* Insert new node as first child/node */
		return NULL;
	}
	else{ //letter > first->GetSymbol()

		/* Move to first node */
		current = first;
		/* Check next */
		while(1){

			if( current->GetNext() == NULL ){ /* There is no next to check */
				return current;
			}
			else{

				next_symbol = current->GetNext()->GetSymbol();
				if( letter < next_symbol ){ /* New node should be inserted as current->next, as letter > current_symbol but letter < next_symbol */
					return current;
				}
				else if( letter == next_symbol ){ /* Move to this child */
					return current->GetNext();
				}
				else{
					current = current->GetNext();
				}

			}

		}

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
