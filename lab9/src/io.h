#ifndef IO_H
#define IO_H
#include <stddef.h>

int read(size_t *vertex, size_t *edge, size_t *start, size_t *finish,
         int **matrix);

void printDistance(const size_t *distance, size_t start, size_t vertex);

void printPath(size_t finish, const size_t *parent, const size_t *distance,
               size_t vertex, size_t start, const size_t *pathCount);

#endif
