#include <iostream>

using namespace std;

#include "PostingList.h"

int main(int argc, char const *argv[]) {

	PostingList myPostList;

	myPostList.Insert(0);
	myPostList.Insert(0);
	myPostList.Insert(0);

	myPostList.Insert(1);
	myPostList.Insert(1);
	myPostList.Insert(1);
	myPostList.Insert(1);
	myPostList.Insert(1);

	myPostList.Insert(2);
	myPostList.Insert(2);
	myPostList.Insert(2);
	myPostList.Insert(2);
	myPostList.Insert(2);
	myPostList.Insert(2);
	myPostList.Insert(2);

	myPostList.Insert(3);
	myPostList.Insert(3);
	myPostList.Insert(3);
	myPostList.Insert(3);
	myPostList.Insert(3);
	myPostList.Insert(3);
	myPostList.Insert(3);
	myPostList.Insert(3);
	myPostList.Insert(3);

	myPostList.Insert(7);
	myPostList.Insert(7);
	myPostList.Insert(7);
	myPostList.Insert(7);
	myPostList.Insert(7);
	myPostList.Insert(7);
	myPostList.Insert(7);
	myPostList.Insert(7);
	myPostList.Insert(7);
	myPostList.Insert(7);
	myPostList.Insert(7);

	myPostList.Insert(9);
	myPostList.Insert(9);
	myPostList.Insert(9);
	myPostList.Insert(9);
	myPostList.Insert(9);
	myPostList.Insert(9);
	myPostList.Insert(9);
	myPostList.Insert(9);
	myPostList.Insert(9);
	myPostList.Insert(9);
	myPostList.Insert(9);
	myPostList.Insert(9);
	myPostList.Insert(9);

	cout << "termFrequency of docId 2 is " << myPostList.GetTermFreq(2) << endl;
	cout << "termFrequency of docId 5 is " << myPostList.GetTermFreq(5) << endl;
	cout << "termFrequency of docId 7 is " << myPostList.GetTermFreq(7) << endl;
	cout << "termFrequency of docId 8 is " << myPostList.GetTermFreq(8) << endl;

	cout << "docFrequency of PL is " << myPostList.GetDocFrequency() << endl;

	cout << "PL is : " ;
	myPostList.Print();

	return 0;
}
