#include <iostream>
#include <cstring>

#include "Trie.h"

int main(int argc, char const *argv[]) {

	Trie myTrie;

	char *word = new char[9];
	char word2[] = "a";
	strcpy(word,"ola_kala");

	//myTrie.Insert(word,12);
	myTrie.Insert(word2,14);

	delete[] word;
	return 0;
}
