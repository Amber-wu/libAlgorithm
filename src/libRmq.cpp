#include <iostream>
#include <cmath>

#include "common.h"
#include "libRmq.h"

using namespace std;

template<typename T>
libRmq<T>::libRmq()
{
	if (OK != init(DEFAULT_DATA_SIZE)) return;

	memset(dataArr, 0, sizeof(T) * DEFAULT_DATA_SIZE);
}

template<typename T>
libRmq<T>::libRmq(int S)
{
	if (OK != init(S)) return;

	memset(dataArr, 0, sizeof(T) * S);
}

template<typename T>
libRmq<T>::libRmq(int S, T* data)
{
	if (NULL == data) return;

	if (OK != init(S)) return;

	memcpy(dataArr, data, sizeof(T) * S);
}

template<typename T>
libRmq<T>::~libRmq()
{
	if (NULL != dataArr)
	{
		delete[] dataArr;
		dataArr = NULL;
	}

	// free M
	if (NULL != M)
	{
		for (int i = 0; i < maxSize; i++)
		{
			delete[] M[i];
		}
		delete[] M;
	}

	if (NULL != treeM)
	{
		delete[] treeM;
	}
}

// sparse table
template<typename T>
int libRmq<T>::sparseTableProcess()
{
	int i, j;

	for (j = 0; 1<<j <= maxSize; j++)
	{
		for (i = 0; i + (1<<j) - 1 < maxSize; i++)
		{
			if (0 == j)
			{
				M[i][j] = i;
			}
			else
			{
				if (dataArr[ M[i][j-1] ] < dataArr[ M[i + (1<<(j-1))][j-1]])
				{
					M[i][j] = M[i][j-1];
				}
				else
				{
					M[i][j] = M[i + (1<<(j-1))][j-1];
				}
			}
		}
	}

	return OK;
}

template<typename T>
int libRmq<T>::sparseTableUpdate(int idx, T value)
{
	// TODO
	dataArr[idx] = value;
	sparseTableProcess();
	return OK;
}

template<typename T>
int libRmq<T>::sparseTableQuery(int startIdx, int endIdx)
{
	if (startIdx > endIdx || endIdx >= maxSize)
		return ERR;

	int k = utilGet2Log(endIdx - startIdx + 1);

	if (dataArr[M[startIdx][k]] < dataArr[M[endIdx - (1<<k) + 1][k]])
	{
		return M[startIdx][k];
	}
	else
	{
		return M[endIdx - (1<<k) + 1][k];
	}
}

// segment tree
template<typename T>
int libRmq<T>::segmentTreeProcess()
{
	return initSegTree(0, 0, maxSize - 1);
}

template<typename T>
int libRmq<T>::segmentTreeUpdate(int idx, T value)
{
	return OK;
}

template<typename T>
int libRmq<T>::segmentTreeQuery(int startIdx, int endIdx)
{
	return querySegTree(0, 0, maxSize - 1, startIdx, endIdx);
}

template<typename T>
int libRmq<T>::init(int S)
{
	this->maxSize = S;
	dataArr = new T[sizeof(T) * S];

	if (NULL == dataArr)
	{
		PMD("failed to malloc memory for data\n");
		return ERR;
	}

	int k = utilGet2Log(S);

	M = new int*[S];
	for (int i = 0; i < S; i++)
	{
		// MUST new at least 1byte more to hold the terminate character
		// otherwise it would crash while delete these memorys
		//
		// in case M[i] = new int[k], running it through valgrind would
		// araise the error message "0 bytes after a block of size xxx"
		M[i] = new int[k + 1];
	}

	if ((1 << k) < S) k++;

	this->treeMaxIdx = (1<<k);

	treeM = new int[this->treeMaxIdx + 1];
	if (NULL == treeM)
	{
		PMD("failed to malloc memory\n");
		return ERR;
	}

	return OK;
}

// nodeIdx start from 0
template<typename T>
int libRmq<T>::initSegTree(int nodeIdx, int left, int right)
{
	if (left < 0 || right > treeMaxIdx || left > right)
	{
		return ERR;
	}

	if (left == right)
	{
		treeM[nodeIdx] = left;
	}
	else
	{
		int leftCld = nodeIdx * 2 + 1;
		initSegTree(leftCld, left, ((left + right)>>1));
		initSegTree(leftCld + 1, ((left + right)>>1) + 1, right);

		if (dataArr[treeM[leftCld]] < dataArr[treeM[leftCld + 1]])
		{
			treeM[nodeIdx] = treeM[leftCld];
		}
		else
		{
			treeM[nodeIdx] = treeM[leftCld + 1];
		}
	}

	return OK;
}

template<typename T>
int libRmq<T>::querySegTree(int nodeIdx, int left, int right, int queryL, int queryR)
{
	int mid, leftCld;
	int lMinIdx, rMinIdx;

	mid = (left + right)>>1;
	leftCld = nodeIdx * 2 + 1;

	if (queryL > right || queryR < left || queryL > queryR) return -1;

	if (queryL <= left && right <= queryR)
		return treeM[nodeIdx];

	lMinIdx = querySegTree(leftCld, left, ((left+right)>>1), queryL, queryR);
	rMinIdx = querySegTree(leftCld + 1, ((left+right)>>1) + 1, right, queryL, queryR);

	if (-1 == lMinIdx) return rMinIdx;
	else if (-1 == rMinIdx) return lMinIdx;
	else if (dataArr[lMinIdx] < dataArr[rMinIdx]) return lMinIdx;
	else return rMinIdx;
}

int testRmq()
{
	PMD("\n------ RMQ test ------\n");
	int A[10] = {2,4,3,1,6,7,8,9,1,7};
	int queryArr[10][2] = {
		{0, 9},
		{1, 3},
		{1, 1},
		{9, 9},
		{0, 7},
		{1, 8},
		{5, 7},
	};

	libRmq<int> rmq(10, A);

	rmq.sparseTableProcess();

	cout<<"A[] = {";
	for (int i = 0; i < 10; i++)
	{
		if (i != 0) cout<<", ";
		cout<<A[i];
	}
	cout<<"}\n";

	cout<<"sparse table\n";
	for (int i = 0; i < 7; i++)
	{
		printf("min[%d, %d]= A[%d]\n", queryArr[i][0], queryArr[i][1], rmq.sparseTableQuery(queryArr[i][0], queryArr[i][1]));
	}

	cout<<endl<<endl;


	cout<<"segment tree\n";
	rmq.segmentTreeProcess();
	for (int i = 0; i < 7; i++)
	{
		printf("min[%d, %d]= A[%d]\n", queryArr[i][0], queryArr[i][1], rmq.segmentTreeQuery(queryArr[i][0], queryArr[i][1]));
	}
	cout<<endl;

	return OK;
}
