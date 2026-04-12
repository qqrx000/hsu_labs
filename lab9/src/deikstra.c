#include "deikstra.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_T_MAX 4294967295

void deikstraAlgorithm(const size_t *matrix, size_t *distance, size_t *parent,
                       char *visited, size_t *pathCount, const size_t vertex,
                       const size_t start) {
  for (size_t i = 0; i < vertex; ++i) {
    visited[i] = 1;
    distance[i] = SIZE_T_MAX;
    parent[i] = -1;
    pathCount[i] = 0;
  }
  distance[start] = 0;
  pathCount[start] = 1;
  while (1) {
    size_t minIndex = SIZE_T_MAX;
    size_t min = SIZE_T_MAX;
    for (size_t i = 0; i < vertex; ++i) {
      if (visited[i] == 1 && distance[i] < min) {
        min = distance[i];
        minIndex = i;
      }
    }
    if (minIndex == SIZE_T_MAX)
      break;
    for (size_t i = 0; i < vertex; ++i) {
      if (matrix[minIndex * vertex + i] <= 0)
        continue;
      size_t tmp = min + matrix[minIndex * vertex + i];
      if (tmp < min || tmp < matrix[minIndex * vertex + i])
        tmp = SIZE_T_MAX;

      if (tmp < distance[i]) {
        distance[i] = tmp;
        parent[i] = minIndex;
        pathCount[i] = pathCount[minIndex];
      } else if (tmp == distance[i] && tmp != SIZE_T_MAX) {
        pathCount[i] += pathCount[minIndex];
      }
    }
    visited[minIndex] = 0;
  }
}

void printDistance(const size_t *distance, const size_t start,
                   const size_t vertex) {
  for (size_t i = 0; i < vertex; ++i) {
    if (i == start)
      printf("0");
    else if (distance[i] == SIZE_T_MAX)
      printf("oo");
    else if (distance[i] > INT_MAX)
      printf("INT_MAX+");
    else
      printf("%zu", distance[i]);
    if (i < vertex - 1)
      printf(" ");
  }
  printf("\n");
}

void printPath(const size_t finish, const size_t *parent,
               const size_t *distance, const size_t vertex, const size_t start,
               const size_t *pathCount) {
  if (distance[finish] == SIZE_T_MAX) {
    printf("no path\n");
    return;
  }
  if (distance[finish] > INT_MAX && pathCount[finish] > 1) {
    printf("overflow\n");
    return;
  }
  size_t *path = malloc(vertex * sizeof(size_t));
  if (!path) {
    printf("malloc failed");
    return;
  }
  size_t path_len = 0;
  size_t current = finish;

  while (current != SIZE_T_MAX && current != start) {
    path[path_len++] = current;
    current = parent[current];
  }
  path[path_len++] = start;

  for (size_t i = 0; i < path_len; ++i) {
    printf("%zu", path[i] + 1);
    if (i < path_len - 1)
      printf(" ");
  }
  printf("\n");
  free(path);
}
