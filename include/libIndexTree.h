#include <iostream>
#include <string.h>

#include "common.h"

using namespace std;

class IndexTree
{
public:
	IndexTree(int* array, int n);
	int updateIdx(int idx, int value);
	int printTree();
	~IndexTree();
private:
	int size;
	int *arr;
	int *treeArr;

	int lowBit(int x);
	int buildIndexTree(int *array, int n);
};

int testIndexTree();
