#include <iostream>

using namespace std;

#include "PostingList.h"
#include "DocInfo.h"

int main(int argc, char const *argv[]) {

	PostingList myPostList;
	DocInfo tempDocInfo(0,1);

	myPostList.InsertAtEnd(tempDocInfo);
	myPostList.IncrLastTermFreq();

	tempDocInfo.SetId(1);
	tempDocInfo.SetTermFreq(10);
	myPostList.InsertAtEnd(tempDocInfo);
	myPostList.IncrLastTermFreq();

	tempDocInfo.SetId(2);
	tempDocInfo.SetTermFreq(100);
	myPostList.InsertAtEnd(tempDocInfo);
	myPostList.IncrLastTermFreq();

	tempDocInfo.SetId(3);
	tempDocInfo.SetTermFreq(1000);
	myPostList.InsertAtEnd(tempDocInfo);
	myPostList.IncrLastTermFreq();

	tempDocInfo.SetId(7);
	tempDocInfo.SetTermFreq(10000);
	myPostList.InsertAtEnd(tempDocInfo);
	myPostList.IncrLastTermFreq();

	tempDocInfo.SetId(9);
	tempDocInfo.SetTermFreq(100000);
	myPostList.InsertAtEnd(tempDocInfo);
	myPostList.IncrLastTermFreq();


	cout << "termFrequency of docId 2 is " << myPostList.GetTermFreq(2) << endl;
	cout << "termFrequency of docId 5 is " << myPostList.GetTermFreq(5) << endl;
	cout << "termFrequency of docId 7 is " << myPostList.GetTermFreq(7) << endl;
	cout << "termFrequency of docId 8 is " << myPostList.GetTermFreq(8) << endl;

	cout << "docFrequency of PL is " << myPostList.GetDocFrequency() << endl;

	cout << "PL is : " ;
	myPostList.Print();

	return 0;
}
