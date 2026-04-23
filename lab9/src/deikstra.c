#include "deikstra.h"
#include <limits.h>

void deikstraAlgorithm(const int *matrix, size_t *distance, size_t *parent,
                       char *visited, size_t *pathCount, const size_t vertex,
                       const size_t start) {
  for (size_t i = 0; i < vertex; ++i) {
    visited[i] = 1;
    distance[i] = ULONG_MAX;
    parent[i] = ULONG_MAX;
    pathCount[i] = 0;
  }
  distance[start] = 0;
  pathCount[start] = 1;

  while (1) {
    size_t minIndex = ULONG_MAX;
    size_t min = ULONG_MAX;
    for (size_t i = 0; i < vertex; ++i) {
      if (visited[i] == 1 && distance[i] < min) {
        min = distance[i];
        minIndex = i;
      }
    }
    if (minIndex == ULONG_MAX)
      break;

    for (size_t i = 0; i < vertex; ++i) {
      int edge_len = matrix[minIndex * vertex + i];
      if (edge_len <= 0)
        continue;

      size_t tmp;
      if (min > ULONG_MAX - (size_t)edge_len) {
        tmp = ULONG_MAX;
      } else {
        tmp = min + edge_len;
      }

      if (tmp < distance[i]) {
        distance[i] = tmp;
        parent[i] = minIndex;
        pathCount[i] = pathCount[minIndex];
      } else if (tmp == distance[i] && tmp != ULONG_MAX) {
        pathCount[i] += pathCount[minIndex];
      }
    }
    visited[minIndex] = 0;
  }
}
