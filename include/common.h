#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <string.h>

#define PMD(...)\
	printf("[%s, %s, %d]: ", __FILE__, __func__, __LINE__);\
	printf(__VA_ARGS__);

#define OK 0
#define ERR -1

#define DEFAULT_DATA_SIZE 1024

int utilGet2Log(int t);

#endif // COMMON_H
