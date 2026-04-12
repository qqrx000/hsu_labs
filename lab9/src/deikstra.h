#ifndef LAB9_DEIKSTRA_H
#define LAB9_DEIKSTRA_H
#include <stddef.h>

void deikstraAlgorithm(const size_t *matrix, size_t *distance, size_t *parent,
                       char *visited, size_t *pathCount, size_t vertex,
                       size_t start);

void printDistance(const size_t *distance, size_t start, size_t vertex);

void printPath(size_t finish, const size_t *parent, const size_t *distance,
               size_t vertex, size_t start, const size_t *pathCount);

#endif
