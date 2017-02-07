#include <iostream>
#include <string.h>

#include "libIndexTree.h"

using namespace std;

IndexTree::IndexTree(int* array, int n)
{
	int ret = OK;
	size = 0;
	arr = treeArr = NULL;

	if (NULL == array || 0 == n) return;

	if (NULL == (arr = new int[n + 1]))
	{
		goto constructErr;
	}
	
	if (NULL == (treeArr = new int[n + 1]))
	{
		goto constructErr;
	}

	memset(arr, 0, n + 1);
	memset(treeArr, 0, n + 1);
	size = n;

	/* init index tree */
	ret = buildIndexTree(array, n);
	if (OK != ret)
	{
		cout<<"built tree failed, "<<ret<<endl;
	}

	return;
constructErr:
	if (arr) delete arr;
	if (treeArr) delete treeArr;

}

int IndexTree::updateIdx(int idx, int value)
{
	if (idx <= 0 || idx > size) return ERR;

	int delta = value - arr[idx];

	arr[idx] = value;

	while (idx <= size)
	{
		treeArr[idx] += delta;
		idx += lowBit(idx);
	}

	return OK;
}

int IndexTree::printTree()
{
	int i;
	cout<<"arr: ";
	for (i = 1; i <= size; i++)
		cout<<" "<<arr[i];
	cout<<endl;

	cout<<"treeArr: ";
	for (i = 1; i <= size; i++)
		cout<<" "<<treeArr[i];
	cout<<endl;

	return OK;
}

IndexTree::~IndexTree()
{
	if (arr) delete arr;
	if (treeArr) delete treeArr;
}

int IndexTree::lowBit(int x)
{
	return x & (-x);
}

int IndexTree::buildIndexTree(int *array, int n)
{
	if (0 >= n || NULL == array || NULL == arr || NULL == treeArr) return ERR;

	int i;
	int ret;
	for (i = 0; i < n; i++)
	{
		ret = updateIdx(i + 1, array[i]);

		if (OK != ret)
		{
			return ret;
		}
	}

	return OK;
}

int testIndexTree()
{
	PMD("\n------ Index Tree test ------\n");

	int tArr[5] = {2,5,3,9,7};
	class IndexTree t(tArr, 5);

	t.printTree();
	cout<<endl<<endl;
	return OK;
}
