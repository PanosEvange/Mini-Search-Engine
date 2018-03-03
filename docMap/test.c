#include <stdio.h>
#include "docMap.h"

int main(int argc, char const *argv[]) {

	char doc1[17] = "Hello world of C";
	char doc2[14] = "Haha have fun";
	char doc3[22] = "Wow yolo and have fun";

	int numberOfDocuments = 3;
	char **words = NULL;
	docMap myMap = NULL;

	docMap_Init(&myMap,numberOfDocuments);
	docMap_InsertDoc(myMap,doc1,0);
	docMap_InsertDoc(myMap,doc2,1);
	docMap_InsertDoc(myMap,doc3,2);
	docMap_PrintDoc(myMap,words,0);
	docMap_PrintDoc(myMap,words,1);
	docMap_PrintDoc(myMap,words,2);
	docMap_Destroy(&myMap,numberOfDocuments);

	return 0;
}
