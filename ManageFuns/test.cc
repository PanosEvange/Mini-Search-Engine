#include "ManageFuns.h"

#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char const *argv[]) {

	int rv;
	char file_name[] = "test.txt";
	FileInfo my_info;
	my_info.number_of_rows = 0;
	my_info.file_name = new char[strlen(file_name)+1];
	strcpy(my_info.file_name,file_name);

	rv = GetFileInfo(my_info);

	if( rv == -1 ){
		cout << "Ids are invalid!" << endl;
		delete[] my_info.file_name;
		return -1;
	}
	else{
		cout << "Number of rows of file " << my_info.file_name << " is " << my_info.number_of_rows << endl;
	}

	DocMap cur_map(my_info.number_of_rows);
	Trie cur_trie;

	InsertDocs( cur_map,cur_trie,my_info );

	cur_trie.PrintAllDf();
	
	delete[] my_info.file_name;
	return 0;
}
