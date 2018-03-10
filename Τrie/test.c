#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

int main(int argc, char const *argv[]) {

	trie_Header *myTrie = NULL;

	trie_Init(&myTrie);

	char *word = malloc( 9 * sizeof(char) );
	//char word2[] = "a";
	strcpy(word,"ola_kala");

	trie_Insert(myTrie,word,12);
	//trie_Insert(myTrie,word2,14);

	return 0;
}
