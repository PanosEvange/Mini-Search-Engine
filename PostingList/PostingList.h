/***************************************************************************************
Header file : PostingList.h
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description :



****************************************************************************************/
#ifndef POST_LIST_H
#define POST_LIST_H
#include "DocInfo.h"

class PL_Node{

private:
		PL_Node *next;
		DocInfo my_info;
public:
		PL_Node( const DocInfo &to_insert );
		~PL_Node();
		PL_Node* GetNext();
		int GetId();
		int GetTermFreq();
		void SetNext( PL_Node *my_next );
		void IncreaseTermFreq();

};

class PostingList{

private:
		PL_Node *first;
		PL_Node *last;
		int doc_frequency;
public:
		PostingList();
		~PostingList();
		void Insert( int doc_id_to_insert );
		int GetDocFrequency();
		bool IsEmpty();
		void Print();
		int GetTermFreq( int doc_id );
		PL_Node* GetFirst();

};

#endif /* POST_LIST_H */
