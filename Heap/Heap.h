/***************************************************************************************
Header file : Heap.h
Programmer	: PANAGIOTIS EVANGELIOU  AM:1115201500039
Description : Declaration of class Heap, which represents a binary heap
			  which helps us to find the ids of top-K scores of the query.
****************************************************************************************/
#ifndef HEAP_H
#define HEAP_H

#include "../ManageFuns/ManageFuns.h"

typedef struct ScoreId{
	double score;
	int id;
} ScoreId;

class Heap{

private:
		ScoreId *array;
		int size;

public:
		Heap( ScoreId *array_to_sort, int size_of_array );
		~Heap();
		void Heapify( int index );
		int GetMax( ScoreId &to_return );
		void Print();

};

#endif /* HEAP_H */
