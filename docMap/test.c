#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "docMap.h"

int main(int argc, char const *argv[]) {

	char doc1[17] = "Hello world of C";
	char doc2[14] = "Haha have fun";
	char doc3[29] = "  \tWow \tyolo and have fun  \t";
	char specialInfo[] = "1.( 1)[0.0341] ";
	int numberOfDocuments = 3;

	words myWords;

	myWords.numOfWords = 3;
	myWords.wordsMap = malloc( 3 * sizeof(char *) );

	myWords.wordsMap[0] = malloc ( 5 * sizeof(char) );
	myWords.wordsMap[1] = malloc ( 5 * sizeof(char) );
	myWords.wordsMap[2] = malloc ( 4 * sizeof(char) );

	strcpy(myWords.wordsMap[0],"yolo");
	strcpy(myWords.wordsMap[1],"have");
	strcpy(myWords.wordsMap[2],"fun");

	docMap myMap;
	myMap.map = NULL;

	docMap_Init(&myMap,numberOfDocuments);

	docMap_InsertDoc(myMap,doc1,0);
	docMap_InsertDoc(myMap,doc2,1);
	docMap_InsertDoc(myMap,doc3,2);

	docMap_PrintDoc(myMap,myWords,2,specialInfo);

	docMap_Destroy(&myMap);

	for( int i = 0; i < myWords.numOfWords; i++ ){
		free( myWords.wordsMap[i] );
	}

	free( myWords.wordsMap );

	return 0;
}
