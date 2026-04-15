#ifndef DEIKSTRA_H
#define DEIKSTRA_H
#include <stddef.h>

void deikstraAlgorithm(const int *matrix, size_t *distance, size_t *parent,
                       char *visited, size_t *pathCount, size_t vertex,
                       size_t start);

#endif
