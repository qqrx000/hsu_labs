#ifndef KAN_H
#define KAN_H

#include <stddef.h>

struct node;
typedef struct queue queue;

int topoSort(size_t vertex, struct node **adjList, size_t *inDegree,
             size_t *result);

#endif
