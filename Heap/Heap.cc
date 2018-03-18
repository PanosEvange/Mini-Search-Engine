/**************************************************************************
Source file	: Heap.cc
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	: Implementation of methods of class Heap, which is used to
			  represent a binary heap, implemented as an array, which
			  helps us to create ( Heapify ) a given array, and then
			  taking the max ScoreId struct, whenever we call the methods
			  GetMax.
***************************************************************************/

using namespace std;

#include <iostream>
#include <cmath>

#include "Heap.h"

Heap::Heap( ScoreId *array_to_sort, int size_of_array )
:array(array_to_sort),size(size_of_array)
{

	for( int i = size/2; i >= 1; i-- ){
		Heapify(i);
	}

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

int Heap::GetMax( ScoreId &to_return ){

	if( size > 0 ){

		to_return.score = array[0].score;
		to_return.id = array[0].id;

		array[0].id = array[size-1].id;
		array[0].score = array[size-1].score;

		array[size-1].id = to_return.id;
		array[size-1].score = to_return.score;

		size = size - 1;
		Heapify(1);

		return 1;
	}
	else{
		return -1;
	}


}

/* For debugging purposes */
void Heap::Print(){

	cout << "Elements of the heap are:" << endl;

	for( int i = 0; i < size; i++ ){
		cout << "doc id : " << array[i].id << " | score : " << array[i].score << endl;
	}

}
