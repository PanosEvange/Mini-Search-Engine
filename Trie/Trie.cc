/**************************************************************************
Source file	: Trie.cc
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	:

***************************************************************************/

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

#include "Trie.h"


TrieNode::TrieNode( char symbol_to_set )
:child(NULL),next(NULL),symbol(symbol_to_set)
{

}

TrieNode::~TrieNode(){

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

int TrieNode::Print( char* word_so_far ){
	return -1;
}

void TrieNode::DeleteChildNext(){

	if( GetChild() != NULL ){
		GetChild()->DeleteChildNext();
	}

	if( GetNext() != NULL ){
		GetNext()->DeleteChildNext();
	}

	if( GetChild() != NULL ){
		delete GetChild();
	}

	if( GetNext() != NULL ){
		delete GetNext();
	}

}

NonFinalTrieNode::NonFinalTrieNode( char symbol_to_set )
:TrieNode(symbol_to_set)
{

}

NonFinalTrieNode::~NonFinalTrieNode(){

}

int NonFinalTrieNode::Print( char* word_so_far ){

	char *new_word;
	int old_length;

	if( word_so_far == NULL ){ /* I am the first child/letter */
		/* So my symbol will be the first symbol for this word_so_far */
		new_word = new char[2];
		new_word[0] = GetSymbol();
		new_word[1] = '\0';
	}
	else{
		old_length = strlen(word_so_far);
		new_word = new char[old_length+2];
		strcpy(new_word,word_so_far);
		new_word[old_length] = GetSymbol();
		new_word[old_length+1] = '\0';
	}

	if( GetChild() != NULL ){
		GetChild()->Print(new_word);
	}

	if( GetNext() != NULL ){
		GetNext()->Print(word_so_far);
	}

	delete[] new_word;
	return 1;

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

int FinalTrieNode::Print( char* word_so_far ){

	char *new_word;
	int old_length;

	if( word_so_far == NULL ){ /* I am the first child/letter */
		/* So my symbol will be the first symbol for this word_so_far */
		new_word = new char[2];
		new_word[0] = GetSymbol();
		new_word[1] = '\0';
	}
	else{
		old_length = strlen(word_so_far);
		new_word = new char[old_length+2];
		strcpy(new_word,word_so_far);
		new_word[old_length] = GetSymbol();
		new_word[old_length+1] = '\0';
	}

	/* I am a final Node so print new_word and df */
	cout << new_word << " " << my_post_list->GetDocFrequency() << endl;

	if( GetChild() != NULL ){
		GetChild()->Print(new_word);
	}

	if( GetNext() != NULL ){
		GetNext()->Print(word_so_far);
	}

	delete[] new_word;
	return 1;

}

Trie::Trie()
:first(NULL),total_words(0)
{

}

Trie::~Trie(){

	if( first != NULL ){
		first->DeleteChildNext();
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
	}
	else{

		if( strlen(word_to_insert) == 1 ){
			/* We have only one final node which should be inserted ( or increase its PostingList )
			   if exists ) at the "first level" of children nodes */
			rv = FindFirstFinalChild(word_to_insert[0],previous_of_child);
			switch (rv) {
				case 0:	/* Check if first node is already final node, else make it final node */
						if( first->GetPostList() == NULL ){ /* It is not a final node */
							/* Convert it to final node */
							temp = new FinalTrieNode( first->GetSymbol() );
							temp->SetNext( first->GetNext() );
							temp->SetChild( first->GetChild() );
							temp->InsertDocId(doc_id_to_insert);
							delete first;
							first = temp;
						}
						else{
							/* It is already a final node so just insert this doc_id_to_insert */
							first->InsertDocId(doc_id_to_insert);
						}
						break;
				case 1: /* A new final node should be inserted as first node */
						temp = new FinalTrieNode( word_to_insert[0] );
						temp->InsertDocId(doc_id_to_insert);
						temp->SetNext(first);
						first = temp;
						break;
				case 2: /* A new final node should be inserted as next of previous_of_child */
						temp = new FinalTrieNode( word_to_insert[0] );
						temp->InsertDocId(doc_id_to_insert);
						temp->SetNext(previous_of_child->GetNext());
						previous_of_child->SetNext(temp);
						break;
				case 3: /* Check if next of previous_of_child is already final node, else make it final node */
						if( previous_of_child->GetNext()->GetPostList() == NULL ){ /* It is not a final node */
							/* Convert it to final node */
							temp = new FinalTrieNode( previous_of_child->GetNext()->GetSymbol() );
							temp->SetNext( previous_of_child->GetNext()->GetNext() );
							temp->SetChild( previous_of_child->GetNext()->GetChild() );
							temp->InsertDocId(doc_id_to_insert);
							delete previous_of_child->GetNext();
							previous_of_child->SetNext(temp);
						}
						else{
							/* It is already a final node so just insert this doc_id_to_insert */
							previous_of_child->GetNext()->InsertDocId(doc_id_to_insert);
						}
						break;
			}

		}
		else{

			/* Find the position/child of first letter */
			child = FindFirstChild(word_to_insert[0]);
			if( child == NULL ){
				/* Insert new node as first node */
				temp = new NonFinalTrieNode( word_to_insert[0] );
				temp->SetNext(first);
				first = temp;
				/* Then insert NonFinalTrieNodes as children of first node
					for all letters except last letter */
				current = InsertNonFinalNodes( word_to_insert, 1, first );
				/* Insert finalNode for last letter */
				temp = new FinalTrieNode( word_to_insert[strlen(word_to_insert)-1] );
				temp->InsertDocId(doc_id_to_insert);
				current->SetChild(temp);
			}
			else{
				/* We found child which may have symbol == word_to_insert[0] or
				 	symbol < word_to_insert[0] but child->next symbol > word_to_insert[0] , if
					child->next node exists */
				/* So there are 2 options */
				if( word_to_insert[0] > child->GetSymbol() ){
					/* Insert new node as child->next */
					temp = new NonFinalTrieNode( word_to_insert[0] );
					temp->SetNext(child->GetNext());
					child->SetNext(temp);
					/* Then insert NonFinalTrieNodes as children of this new node
						for all letters except last letter */
					current = InsertNonFinalNodes( word_to_insert, 1, child->GetNext() );
					/* Insert finalNode for last letter */
					temp = new FinalTrieNode( word_to_insert[strlen(word_to_insert)-1] );
					temp->InsertDocId(doc_id_to_insert);
					current->SetChild(temp);
				}
				else if( word_to_insert[0] == child->GetSymbol() ){
					/* Move to this child */
					current = child;

					/* Then call FindChild for all other letters except last letter */
					for( i = 1; i < ( (int) strlen(word_to_insert) - 1 ); i++ ){
						child = FindChild(word_to_insert[i],current);
						if( child == NULL ){
							/* Insert new node as first child */
							temp = new NonFinalTrieNode( word_to_insert[i] );
							if( current->GetChild() != NULL ){
								temp->SetNext(current->GetChild());
							}
							current->SetChild(temp);
							current = current->GetChild();
							break;
						}
						else{
							/* We found child which may have symbol == word_to_insert[0] or
								symbol < word_to_insert[0] but child->next symbol > word_to_insert[0] , if
								child->next node exists */
							/* So there are 2 options */
							if( word_to_insert[i] > child->GetSymbol() ){
								/* Insert new node as child->next */
								temp = new NonFinalTrieNode( word_to_insert[i] );
								temp->SetNext(child->GetNext());
								child->SetNext(temp);
								current = child->GetNext();
								break;
							}
							else if( word_to_insert[i] == child->GetSymbol() ){
								current = child;
								/* Go on to next i */
							}
						}
					}

					if( i < ((int) (strlen(word_to_insert)-1)) ){
						/* We should insert NonFinalTrieNodes as childen of current node
							for remaining letters and final node for last letter */
						current = InsertNonFinalNodes( word_to_insert, i+1, current );
						/* We dont have to call FindFinalChild */
						temp = new FinalTrieNode( word_to_insert[strlen(word_to_insert)-1] );
						temp->InsertDocId(doc_id_to_insert);
						current->SetChild(temp);
					}
					else{
						/* We should only insert final node for last letter */
						/* So we need to call FindFinalChild */
						rv = FindFinalChild(word_to_insert[strlen(word_to_insert)-1],current,previous_of_child);
						switch (rv) {
							case 0:	/* New finalNode should be inserted as first child of previous_of_child */
									temp = new FinalTrieNode( word_to_insert[strlen(word_to_insert)-1] );
									temp->InsertDocId(doc_id_to_insert);
									if( previous_of_child->GetChild() != NULL ){
										temp->SetNext(previous_of_child->GetChild());
									}
									previous_of_child->SetChild(temp);
									break;
							case 1: /* Check if previous_of_child->GetChild is final,else make it final */
									if( previous_of_child->GetChild()->GetPostList() == NULL ){ /* It is not a final node */
										/* Convert it to final node */
										temp = new FinalTrieNode( previous_of_child->GetChild()->GetSymbol() );
										temp->SetNext( previous_of_child->GetChild()->GetNext() );
										temp->SetChild( previous_of_child->GetChild()->GetChild() );
										temp->InsertDocId(doc_id_to_insert);
										delete previous_of_child->GetChild();
										previous_of_child->SetChild(temp);
									}
									else{
										/* It is already a final node so just insert this doc_id_to_insert */
										previous_of_child->GetChild()->InsertDocId(doc_id_to_insert);
									}
									break;
							case 2: /* A new final node should be inserted as next of previous_of_child */
									temp = new FinalTrieNode( word_to_insert[strlen(word_to_insert)-1] );
									temp->InsertDocId(doc_id_to_insert);
									temp->SetNext(previous_of_child->GetNext());
									previous_of_child->SetNext(temp);
									break;
							case 3: /* Check if next of previous_of_child is already final node, else make it final node */
									if( previous_of_child->GetNext()->GetPostList() == NULL ){ /* It is not a final node */
										/* Convert it to final node */
										temp = new FinalTrieNode( previous_of_child->GetNext()->GetSymbol() );
										temp->SetNext( previous_of_child->GetNext()->GetNext() );
										temp->SetChild( previous_of_child->GetNext()->GetChild() );
										temp->InsertDocId(doc_id_to_insert);
										delete previous_of_child->GetNext();
										previous_of_child->SetNext(temp);
									}
									else{
										/* It is already a final node so just insert this doc_id_to_insert */
										previous_of_child->GetNext()->InsertDocId(doc_id_to_insert);
									}
									break;
						}
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

/* Insert NonFinalTrieNodes for each letter ( beggining from word_to_insert[start] to word_to_insert[strlen-2] ), starting from current->child */
TrieNode* Trie::InsertNonFinalNodes( char *word_to_insert, int start, TrieNode* current ){

	TrieNode *temp;

	for( int i = start; i < ( (int) (strlen(word_to_insert) - 1) ); i++  ){
		temp = new NonFinalTrieNode( word_to_insert[i] );
		current->SetChild(temp);
		current = temp;
	}

	return current;

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
	first->Print();
}

void Trie::PrintSpecificDf( char *word_to_print ){

}

void Trie::PrintTermFreq( char *word_to_print, int doc_id_to_print ){

}
