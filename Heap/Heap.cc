/**************************************************************************
Source file	: Heap.cc
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description	:

***************************************************************************/

using namespace std;

#include <iostream>

#include "Heap.h"

Heap::Heap( ScoreId *array_to_sort, int size_of_array )
:array(array_to_sort),size(size_of_array)
{

}

Heap::~Heap(){

}

void Heap::Print(){
	
	cout << "Elements of the heap are:" << endl;

	for( int i = 0; i < size; i++ ){
		cout << "doc id : " << array[i].id << " | score : " << array[i].score << endl;
	}

}
