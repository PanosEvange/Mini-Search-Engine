#include "Heap.h"

#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	int size = 10;
	ScoreId* array = new ScoreId[size];
	ScoreId max;

	array[0].score = 4;
	array[0].id = 43;

	array[1].score = 1;
	array[1].id = 16;

	array[2].score = 3;
	array[2].id = 22;

	array[3].score = 10;
	array[3].id = 33;

	array[4].score = 16;
	array[4].id = 44;

	array[5].score = 9;
	array[5].id = 55;

	array[6].score = 10;
	array[6].id = 66;

	array[7].score = 14;
	array[7].id = 55;

	array[8].score = 8;
	array[8].id = 66;

	array[9].score = 7;
	array[9].id = 66;


	Heap my_heap(array,size);

	cout << "sorted array is:" << endl;
	for( int i = 0; i < size; i++ ){
		my_heap.GetMax(max);
		cout << " id : " << max.id << " | score : " << max.score << endl;
	}

	return 0;
}
