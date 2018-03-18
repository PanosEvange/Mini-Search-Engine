/***************************************************************************************
Header file : DocInfo.h
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description : Declaration of class DocInfo which is used to represent the
			  information of each node in the posting list, which is the id of
			  the a document and the term_frequency of the word in this
			  document.
****************************************************************************************/
#ifndef DOC_INFO_H
#define DOC_INFO_H

class DocInfo{

private:
		int id;
		int term_frequency;
public:
		DocInfo( int id_to_set, int term_frequency_to_set );
		DocInfo( const DocInfo &to_copy );
		~DocInfo();
		void IncreaseTermFreq();
		int GetId();
		int GetTermFreq();
		void SetId( int id_to_set );
		void SetTermFreq( int term_frequency_to_set );
};

#endif /* DOC_INFO_H */
