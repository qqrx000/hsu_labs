#ifndef IO_H
#define IO_H
#include <stddef.h>

int read(int *vertex, int **numbers);
void printResult(const int *log, int idx,  int logEnable, size_t height);
#endif
