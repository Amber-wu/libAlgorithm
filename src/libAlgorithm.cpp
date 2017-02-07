#include <iostream>
#include <string.h>
#include <stdio.h>

#include "common.h"
#include "libHeap.h"
#include "libIndexTree.h"
#include "libRmq.h"

using namespace std;

int main()
{
	testHeap();
	testIndexTree();
	testRmq();
}

int utilGet2Log(int t)
{
	if (t < 0) return ERR;

	int ret = 0;
	for (ret = 0; 1<<ret <= t; ret++)
	{
	}

	return ret - 1;
}
