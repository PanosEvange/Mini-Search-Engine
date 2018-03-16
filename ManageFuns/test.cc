#include "ManageFuns.h"

#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char const *argv[]) {

	int rv;
	//char file_name[] = "bigDataset.txt";
	//char file_name[] = "test.txt";
	char file_name[] = "dataset.txt";

	FileInfo my_info;
	my_info.number_of_rows = 0;
	my_info.file_name = new char[strlen(file_name)+1];
	strcpy(my_info.file_name,file_name);

	rv = GetFileInfo(my_info);

	if( rv == -1 ){
		//cout << "Ids are invalid!" << endl;
		delete[] my_info.file_name;
		return -1;
	}
	else{
		//cout << "Number of rows of file " << my_info.file_name << " is " << my_info.number_of_rows << endl;
	}

	DocMap cur_map(my_info.number_of_rows);
	Trie cur_trie;

	InsertDocs( cur_map,cur_trie,my_info );

	// char word1[] = "users";
	// char word2[] = "Arts";
	// char word3[] = "form";
	// char word4[] = "enters";
	// char word5[] = "collection";
	// char word6[] = "challenges";
	// char word7[] = "Purchasing";
	// char word8[] = "dropped";
	// char word9[] = "who";
	// char word10[] = "their";
	// char word11[] = "Aussie";
	// char word12[] = "British";
	// char word13[] = "defection";
	// char word14[] = "mountainous";
	// char word15[] = "A";
	// char word16[] = "chip";
	// char word17[] = "Tony";
	// char word18[] = "make";
	// char word19[] = "France's";
	// char word20[] = "economy,\"";
	//
	// cur_trie.PrintSpecificDf(word1);
	// cur_trie.PrintSpecificDf(word2);
	// cur_trie.PrintSpecificDf(word3);
	// cur_trie.PrintSpecificDf(word4);
	// cur_trie.PrintSpecificDf(word5);
	// cur_trie.PrintSpecificDf(word6);
	// cur_trie.PrintSpecificDf(word7);
	// cur_trie.PrintSpecificDf(word8);
	// cur_trie.PrintSpecificDf(word9);
	// cur_trie.PrintSpecificDf(word10);
	// cur_trie.PrintSpecificDf(word11);
	// cur_trie.PrintSpecificDf(word12);
	// cur_trie.PrintSpecificDf(word13);
	// cur_trie.PrintSpecificDf(word14);
	// cur_trie.PrintSpecificDf(word15);
	// cur_trie.PrintSpecificDf(word16);
	// cur_trie.PrintSpecificDf(word17);
	// cur_trie.PrintSpecificDf(word18);
	// cur_trie.PrintSpecificDf(word19);
	// cur_trie.PrintSpecificDf(word20);

	cur_trie.PrintAllDf();

	delete[] my_info.file_name;
	return 0;
}
