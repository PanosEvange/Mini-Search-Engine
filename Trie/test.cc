#include <iostream>
#include <cstring>

#include "Trie.h"

int main(int argc, char const *argv[]) {

	Trie myTrie;

	char *word = new char[9];
	char word2[] = "a";
	char word3[] = "b";
	char word4[] = "d";
	char word5[] = "h";
	char word6[] = "p";

	strcpy(word,"ola_kala");

	//myTrie.Insert(word,12);
	myTrie.Insert(word5,1);
	myTrie.Insert(word2,1);
	myTrie.Insert(word4,1);
	myTrie.Insert(word6,1);
	myTrie.Insert(word3,1);

	myTrie.Insert(word6,2);
	//myTrie.Insert(word3,2);
	myTrie.Insert(word2,2);
	myTrie.Insert(word4,2);
	myTrie.Insert(word5,2);

	myTrie.PrintAllDf();

	delete[] word;
	return 0;
}
