#ifndef LIB_RMQ_H
#define LIB_RMQ_H

template<typename T>
class libRmq
{
public:
	libRmq();
	libRmq(int S);
	libRmq(int S, T* data);
	~libRmq();

	// sparse table
	int sparseTableProcess();
	int sparseTableUpdate(int idx, T value);
	int sparseTableQuery(int startIdx, int endIdx);

	// segment tree
	int segmentTreeProcess();
	int segmentTreeUpdate(int idx, T value);
	int segmentTreeQuery(int startIdx, int endIdx);
private:
	int maxSize;
	T* dataArr;
	int **M;

	int treeMaxIdx;
	int *treeM;

	int init(int S);
	int initSegTree(int nodeIdx, int left, int right);
	int querySegTree(int nodeIdx, int left, int right, int queryL, int queryR);
};

int testRmq();

#endif // LIB_RMQ_H
