#ifndef LAB9_DEIKSTRA_H
#define LAB9_DEIKSTRA_H
#include <stddef.h>

void deikstraAlgorithm(const int *matrix, size_t *distance, size_t *parent,
                       char *visited, size_t *pathCount, size_t vertex,
                       size_t start);

#endif
