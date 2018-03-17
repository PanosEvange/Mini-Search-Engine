/**************************************************************************
Source file	: Heap.cc
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	:

***************************************************************************/

using namespace std;

#include <iostream>
#include <cmath>

#include "Heap.h"

Heap::Heap( ScoreId *array_to_sort, int size_of_array )
:array(array_to_sort),size(size_of_array)
{
	int n = floor( ((double)size) / 2 );

	cout << "array before heapify : " << endl;
	Print();
	cout << endl;

	for( int i = n; i >= 1; i-- ){
		Heapify(i);
	}


	cout << "array after heapify : " << endl;
	Print();
	cout << endl;
}

Heap::~Heap(){

}

void Heap::Heapify( int index ){

	int temp_id;
	double temp_score;
	int max;
	int l = 2 * index;
	int r = 2 * index + 1;

	if( ( l <= size ) && ( array[l-1].score > array[index-1].score ) ){
		max = l;
	}
	else{
		max = index;
	}

	if( ( r <= size ) && ( array[r-1].score > array[max-1].score ) ){
		max = r;
	}

	if( index != max ){

		/* Swap( array[index],array[max] ) */
		temp_id = array[index-1].id;
		temp_score = array[index-1].score;

		array[index-1].id = array[max-1].id;
		array[index-1].score = array[max-1].score;

		array[max-1].id = temp_id;
		array[max-1].score = temp_score;

		Heapify(max);
	}

}

void Heap::Print(){

	cout << "Elements of the heap are:" << endl;

	for( int i = 0; i < size; i++ ){
		cout << "doc id : " << array[i].id << " | score : " << array[i].score << endl;
	}

}
