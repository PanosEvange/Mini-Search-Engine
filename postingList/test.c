#include <stdio.h>

#include "postingList.h"
#include "docInfo.h"

int main(int argc, char const *argv[]) {

	PL_Header *myPostList = NULL ;
	docInfo tempDocInfo;

	PL_Init(&myPostList);

	tempDocInfo.id = 0;
	tempDocInfo.termFrequency = 1;
	PL_InsertAtEnd(myPostList,tempDocInfo);
	PL_IncrLastTermFreq(myPostList);

	tempDocInfo.id = 1;
	tempDocInfo.termFrequency = 10;
	PL_InsertAtEnd(myPostList,tempDocInfo);
	PL_IncrLastTermFreq(myPostList);

	tempDocInfo.id = 2;
	tempDocInfo.termFrequency = 100;
	PL_InsertAtEnd(myPostList,tempDocInfo);
	PL_IncrLastTermFreq(myPostList);

	tempDocInfo.id = 3;
	tempDocInfo.termFrequency = 1000;
	PL_InsertAtEnd(myPostList,tempDocInfo);
	PL_IncrLastTermFreq(myPostList);

	tempDocInfo.id = 7;
	tempDocInfo.termFrequency = 10000;
	PL_InsertAtEnd(myPostList,tempDocInfo);
	PL_IncrLastTermFreq(myPostList);

	tempDocInfo.id = 9;
	tempDocInfo.termFrequency = 100000;
	PL_InsertAtEnd(myPostList,tempDocInfo);
	PL_IncrLastTermFreq(myPostList);

	printf("termFrequency of docId 2 is %d \n",PL_GetTermFrequency(myPostList,2) );
	printf("termFrequency of docId 5 is %d \n",PL_GetTermFrequency(myPostList,5) );
	printf("termFrequency of docId 8 is %d \n",PL_GetTermFrequency(myPostList,8) );

	printf("docFrequency of PL is %d \n",PL_GetDocFrequency(myPostList) );

	printf("PL is : " );
	PL_Print(myPostList);

	PL_Destroy(&myPostList);
	return 0;
}
