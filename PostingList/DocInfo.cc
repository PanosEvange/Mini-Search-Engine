/**************************************************************************
Source file	: DocInfo.cc
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	: Implementation of methods of class DocInfo, which is used to
			  represent the information of each node in posting list. They
			  help us to Increase the term_frequency of the word in the
			  document with this id, as well as to get the id or the
			  term_frequency of current node.
***************************************************************************/

#include "DocInfo.h"

DocInfo::DocInfo( int id_to_set, int term_frequency_to_set )
:id(id_to_set),term_frequency(term_frequency_to_set)
{

}

DocInfo::DocInfo( const DocInfo &to_copy ){
	id = to_copy.id;
	term_frequency = to_copy.term_frequency;
}

DocInfo::~DocInfo(){

}

void DocInfo::IncreaseTermFreq(){
	term_frequency ++;
}

int DocInfo::GetId(){
	return id;
}

int DocInfo::GetTermFreq(){
	return term_frequency;
}

void DocInfo::SetId( int id_to_set ){
	id = id_to_set;
}

void DocInfo::SetTermFreq( int term_frequency_to_set ){
	term_frequency = term_frequency_to_set;
}
