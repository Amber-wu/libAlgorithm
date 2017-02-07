#include <iostream>
#include <string.h>
#include <stdio.h>

#include "common.h"
#include "libHeap.h"

using namespace std;

template<typename T>
libHeap<T>::libHeap()
{
	int ret = init(DEFAULT_DATA_SIZE);
	if (ret != OK)
	{
		PMD("failed to init\n");
		return;
	}
}

template<typename T>
libHeap<T>::libHeap(int S)
{
	int ret = init(S);
	if (ret != OK)
	{
		PMD("failed to init\n");
		return;
	}
}

template<typename T>
libHeap<T>::libHeap(int S, T* arr)
{
	int ret;
	if (NULL == arr) return;

	ret = init(S);
	if (ret != OK)
	{
		PMD("failed to init\n");
		return;
	}

	memcpy(heapTree, arr, sizeof(T) * S);
}

template<typename T>
int libHeap<T>::buildMinHeap()
{
	int ret;
	validSize = 0;
	for (int i = 0; i < maxSize; i++)
	{
		ret = insertMinHeap(heapTree[i]);

		if (ret != OK)
		{
			PMD("build heap ERR\n");
			return ret;
		}
	}

	return OK;
}

template<typename T>
int libHeap<T>::insertMinHeap(T v)
{
	return insertHeap(v, MIN_HEAP);
}

template<typename T>
int libHeap<T>::buildMaxHeap()
{
	int ret;
	validSize = 0;
	for (int i = 0; i < maxSize; i++)
	{
		ret = insertMaxHeap(heapTree[i]);

		if (ret != OK)
		{
			PMD("build heap ERR\n");
			return ret;
		}
	}

	return OK;
}

template<typename T>
int libHeap<T>::insertMaxHeap(T v)
{
	return insertHeap(v, MAX_HEAP);
}

template<typename T>
int libHeap<T>::convertMinHeapToMaxHeap()
{
	return buildMaxHeap();
}

// return the size of this heap
template<typename T>
int libHeap<T>::getMaxSize()
{
	return maxSize;
}

// display elements on tree
template<typename T>
int libHeap<T>::printHeapTree()
{
	for (int i = 0; i < maxSize; i++)
	{
		cout<<heapTree[i]<<", ";
	}
	cout<<endl;
	return OK;
}

template<typename T>
libHeap<T>::~libHeap()
{
	if (heapTree) delete[] heapTree;
}

template<typename T>
int libHeap<T>::init(int S)
{
	maxSize = S;
	heapTree = new T[maxSize];

	if (NULL == heapTree)
	{
		PMD("failed to new memory for heapTree\n");
		goto errP;
	}
	memset(heapTree, 0, sizeof(T) * maxSize);

	return OK;

errP:
	if (heapTree) delete[] heapTree;
	return ERR;
}

template<typename T>
int libHeap<T>::insertHeap(T v, heapType ht)
{
	T tv = v;
	int curIdx = validSize;
	int parIdx = (curIdx - 1 )>>1;

	if (curIdx >= maxSize) return ERR;

	heapTree[curIdx] = v;

	while (parIdx >= 0)
	{
		if ((MIN_HEAP == ht && heapTree[parIdx] > heapTree[curIdx]) ||
				(MAX_HEAP == ht && heapTree[parIdx] < heapTree[curIdx]))
		{
			tv = heapTree[parIdx];
			heapTree[parIdx] = heapTree[curIdx];
			heapTree[curIdx] = tv;

			curIdx = parIdx;
			parIdx = (curIdx - 1)>>1;
		}
		else
		{
			break;
		}
	}
	validSize++;
	return OK;
}

int testHeap()
{
	PMD("\n------ Heap test ------\n");
	int arr[20] = {19,7,8,3,5,2,1,4,9,6,15,12,10,13,14,20,11,18,17,16};
	libHeap<int> heap(20, arr);

	heap.printHeapTree();
	heap.buildMinHeap();
	heap.printHeapTree();

	heap.convertMinHeapToMaxHeap();
	heap.printHeapTree();

	cout<<endl<<endl;
	return OK;
}
