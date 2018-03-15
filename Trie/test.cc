#include <iostream>
#include <cstring>

#include "Trie.h"

using namespace std;

int main(int argc, char const *argv[]) {

	Trie myTrie;

	char word0[] = "aloha";
	char word1[] = "The";
	char word2[] = "quick";
	char word3[] = "brown";
	char word4[] = "fox";
	char word5[] = "leaped";
	char word6[] = "over";
	char word7[] = "the";
	char word8[] = "lazy";
	char word9[] = "dog";
	char word10[] = "Quick";
	char word11[] = "foxes";
	char word12[] = "dogs";
	char word13[] = "for";
	char word14[] = "fun";


	myTrie.Insert(word1,0);
	myTrie.Insert(word2,0);
	myTrie.Insert(word3,0);
	myTrie.Insert(word4,0);
	myTrie.Insert(word5,0);
	myTrie.Insert(word6,0);
	myTrie.Insert(word7,0);
	myTrie.Insert(word8,0);
	myTrie.Insert(word8,0);
	myTrie.Insert(word9,0);

	myTrie.Insert(word10,1);
	myTrie.Insert(word3,1);
	myTrie.Insert(word11,1);
	myTrie.Insert(word5,1);
	myTrie.Insert(word6,1);
	myTrie.Insert(word8,1);
	myTrie.Insert(word12,1);
	myTrie.Insert(word13,1);
	myTrie.Insert(word14,1);

	myTrie.PrintAllDf();
	cout << "------------------------------------------------" << endl;

	myTrie.PrintSpecificDf(word5);
	cout << "------------------------------------------------" << endl;
	myTrie.PrintSpecificDf(word0);
	cout << "------------------------------------------------" << endl;
	myTrie.PrintTermFreq(word8,0);
	cout << "------------------------------------------------" << endl;
	myTrie.PrintTermFreq(word0,0);
	cout << "------------------------------------------------" << endl;
	myTrie.PrintTermFreq(word8,3);
	cout << "------------------------------------------------" << endl;

	return 0;
}
