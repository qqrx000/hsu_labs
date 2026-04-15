#include "deikstra.h"

#define SIZE_T_MAX ((size_t)-1)

void deikstraAlgorithm(const int *matrix, size_t *distance, size_t *parent,
                       char *visited, size_t *pathCount, const size_t vertex,
                       const size_t start) {
  for (size_t i = 0; i < vertex; ++i) {
    visited[i] = 1;
    distance[i] = SIZE_T_MAX;
    parent[i] = SIZE_T_MAX;
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
      int edge_len = matrix[minIndex * vertex + i];
      if (edge_len <= 0)
        continue;

      size_t tmp;
      if (min > SIZE_T_MAX - (size_t)edge_len) {
        tmp = SIZE_T_MAX;
      } else {
        tmp = min + edge_len;
      }

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
