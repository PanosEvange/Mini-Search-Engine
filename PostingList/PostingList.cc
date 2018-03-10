/**************************************************************************
Source file	: PostingList.cc
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	:

***************************************************************************/

#include <iostream>

using namespace std;

#include "PostingList.h"

PL_Node::PL_Node( const DocInfo &to_insert )
:next(NULL),my_info(to_insert)
{

}

PL_Node::~PL_Node(){

}

PL_Node* PL_Node::GetNext(){
	return next;
}

int PL_Node::GetId(){
	return my_info.GetId();
}

int PL_Node::GetTermFreq(){
	return my_info.GetTermFreq();
}

void PL_Node::SetNext( PL_Node *my_next ){
	next = my_next;
}

void PL_Node::IncreaseTermFreq(){
	my_info.IncreaseTermFreq();
}

/* Initialization of given posting list */
PostingList::PostingList()
:first(NULL),last(NULL),doc_frequency(0)
{

}

/* Destruction of given posting list */
PostingList::~PostingList(){

	PL_Node *current;

	while( first != NULL ){
		current = first;
		first = current->GetNext();
		delete current;
	}

}

/* Insert infoToInsert docInfo at the end of given posting list */
int PostingList::InsertAtEnd( const DocInfo &to_insert ){

	PL_Node *temp;

	if( IsEmpty() ){

		first = new PL_Node(to_insert);
		last = first;
		doc_frequency ++;

	}
	else{

		temp = new PL_Node(to_insert);
		last->SetNext(temp);
		last = temp;
		doc_frequency ++;

	}

	return 1;
}

/* Return docFrequency of given posting list */
int PostingList::GetDocFrequency(){
	return doc_frequency;
}

bool PostingList::IsEmpty(){
	return ( first == NULL );
}

/* Increment of termFrequency of last node of given posting list */
int PostingList::IncrLastTermFreq(){

	if( IsEmpty() ){
		return -1;
	}

	last->IncreaseTermFreq();
	return 1;
}

/* For debugging purposes */
void PostingList::Print(){

	PL_Node *current;
	current = first;

	cout << "PL(" << doc_frequency << ") " ;

	while( current != NULL ){
		cout << "-> ( " << current->GetId() << " , " << current->GetTermFreq() << " ) ";
		current = current->GetNext();
	}

	cout << endl;

}

/* Find and return termFrequency of given docId  */
int PostingList::GetTermFreq( int doc_id ){

	PL_Node *current;
	current = first;

	while( current != NULL ){

		if( doc_id <= current->GetId() ){ /* It means that we found given docId or there is no such a docId */

			if( doc_id == current->GetId() ){
				return current->GetTermFreq();
			}
			else{	/* doc_ids are sorted, so there is no such a docId */
				return -1;	/* Not found */
			}

		}

		current = current->GetNext();
	}

	return -1;
}
