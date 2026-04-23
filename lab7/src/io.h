#ifndef IO_H
#define IO_H
#include <stddef.h>

struct node;
int read(size_t *vertex, size_t *edge, struct node ***adjList, size_t **inDegree);

#endif
