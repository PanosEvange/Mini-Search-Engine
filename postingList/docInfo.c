/**************************************************************************
Source file	: docInfo.c
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	: > docInfo_Set :
			  > docInfo_GetTermFreq :
			  > docInfo_IncrTermFreq :
			  >docInfo_GetDocId :

***************************************************************************/

#include "docInfo.h"

/* Set target docInfo fields with corresponding values of source docInfo */
void docInfo_Set( docInfo *target, docInfo source ){

	target->id = source.id;
	target->termFrequency = source.termFrequency;

}

/* Return termFrequency of given docInfo */
int docInfo_GetTermFreq( docInfo toTake ){

	return toTake.termFrequency;

}

/* Increment of termFrequency of given docInfo */
void docInfo_IncrTermFreq( docInfo *toIncrease ){

	(toIncrease->termFrequency)++;

}

int docInfo_GetDocId( docInfo toTake ){

	return toTake.id;

}
