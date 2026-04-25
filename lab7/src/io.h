#ifndef IO_H
#define IO_H

#include <stddef.h>

struct node;

int read(int *vertex, int *edge, struct node ***adjList, size_t **inDegree);

void printResult(const size_t *result, size_t vertex);

#endif
