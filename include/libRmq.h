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

	int init(int S);
};

int testRmq();

#endif // LIB_RMQ_H
