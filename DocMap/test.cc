#include "DocMap.h"

int main(int argc, char const *argv[]) {

	char doc1[17] = "Hello world of C";
	char doc2[14] = "Haha have fun";
	char doc3[22] = "Wow yolo and have fun";
	char specialInfo[] = "1.( 1)[0.0341] ";
	int numberOfDocuments = 3;
	char word1[] = "yolo";
	char word2[] = "have";
	char word3[] = "fun";

	Words myWords(3);

	myWords.InsertWord(word1,0);
	myWords.InsertWord(word2,1);
	myWords.InsertWord(word3,2);

	DocMap myMap(numberOfDocuments);

	myMap.InsertDoc(doc1,0);
	myMap.InsertDoc(doc2,1);
	myMap.InsertDoc(doc3,2);

	myMap.PrintDoc(myWords,2,specialInfo);

	return 0;
}
