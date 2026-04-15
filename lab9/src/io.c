#include "io.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_T_MAX ((size_t)-1)

int read(size_t *vertex, size_t *edge, size_t *start, size_t *finish,
         int **matrix) {
  if (scanf("%zu", vertex) != 1 || *vertex > 5000 || *vertex < 1) {
    printf("bad number of vertices");
    return 1;
  }
  if (scanf("%zu %zu", start, finish) != 2 || *start < 1 || *finish < 1 ||
      *start > *vertex || *finish > *vertex) {
    printf("bad vertex");
    return 1;
  }
  if (scanf("%zu", edge) != 1 || *edge > *vertex * (*vertex - 1) / 2) {
    printf("bad number of edges");
    return 1;
  }

  *matrix = calloc(*vertex * *vertex, sizeof(int));
  if (!*matrix) {
    printf("malloc failed");
    return 1;
  }

  for (size_t i = 0; i < *vertex * *vertex; ++i) {
    (*matrix)[i] = 0;
  }

  for (size_t i = 0; i < *edge; ++i) {
    size_t from, to;
    long long len;

    if (scanf("%zu %zu %lld", &from, &to, &len) != 3) {
      printf("bad number of lines");
      free(*matrix);
      return 1;
    }

    if (from < 1 || from > *vertex || to < 1 || to > *vertex) {
      printf("bad vertex");
      free(*matrix);
      return 1;
    }

    if (len < 0 || len > INT_MAX) {
      printf("bad length");
      free(*matrix);
      return 1;
    }

    (*matrix)[(from - 1) * *vertex + (to - 1)] = (int)len;
    (*matrix)[(to - 1) * *vertex + (from - 1)] = (int)len;
  }
  return 0;
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
