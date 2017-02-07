#ifndef LIB_HEAP_H
#define LIB_HEAP_H

#include "common.h"

enum heapType {MIN_HEAP, MAX_HEAP};

template<typename T>
class libHeap
{
public:
	libHeap();

	libHeap(int S);

	libHeap(int S, T* arr);

	int buildMinHeap();

	int insertMinHeap(T v);

	int buildMaxHeap();

	int insertMaxHeap(T v);

	int convertMinHeapToMaxHeap();

	// return the size of this heap
	int getMaxSize();

	// display elements on tree
	int printHeapTree();

	~libHeap();

private:
	int maxSize;
	int validSize;
	
	T* heapTree;

	int init(int S);

	int insertHeap(T v, heapType ht);
};

int testHeap();

#endif // LIB_HEAP_H
