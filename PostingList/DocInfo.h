/***************************************************************************************
Header file : DocInfo.h
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description :



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
