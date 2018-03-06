/***************************************************************************************
Header file : docInfo.h
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description :



****************************************************************************************/
#ifndef DOC_INFO_H
#define DOC_INFO_H

typedef struct docInfo {
	int id;
	int termFrequency;
} docInfo;

void docInfo_Set( docInfo *target, docInfo source );
int docInfo_GetTermFreq( docInfo toTake );
void docInfo_IncrTermFreq( docInfo *toIncrease );
int docInfo_GetDocId( docInfo toTake );

#endif /* DOC_INFO_H */
