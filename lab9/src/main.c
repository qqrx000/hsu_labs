#include "deikstra.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int read(size_t *vertex, size_t *edge, size_t *start, size_t *finish,
         size_t **matrix);

int main(void) {
  size_t vertex, edge, start, finish;
  size_t *matrix = NULL;

  if (read(&vertex, &edge, &start, &finish, &matrix) == 1)
    return EXIT_SUCCESS;

  char *visited = malloc(vertex * sizeof(char));
  size_t *distance = malloc(vertex * sizeof(size_t));
  size_t *parent = malloc(vertex * sizeof(size_t));
  size_t *pathCount = calloc(vertex, sizeof(size_t));

  if (!parent || !visited || !distance || !pathCount) {
    printf("malloc failed");
    free(matrix);
    free(parent);
    free(visited);
    free(pathCount);
    free(distance);
    return EXIT_SUCCESS;
  }

  start--;
  finish--;

  deikstraAlgorithm(matrix, distance, parent, visited, pathCount, vertex,
                    start);
  printDistance(distance, start, vertex);
  printPath(finish, parent, distance, vertex, start, pathCount);

  free(matrix);
  free(distance);
  free(visited);
  free(pathCount);
  free(parent);
  return EXIT_SUCCESS;
}

int read(size_t *vertex, size_t *edge, size_t *start, size_t *finish,
         size_t **matrix) {
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

  *matrix = calloc(*vertex * *vertex, sizeof(size_t));
  if (!*matrix) {
    printf("malloc failed");
    return 1;
  }

  for (size_t i = 0; i < *edge; ++i) {
    size_t from, to;
    size_t len;

    if (scanf("%zu %zu %zu", &from, &to, &len) != 3) {
      printf("bad number of lines");
      free(*matrix);
      return 1;
    }

    if (from < 1 || from > *vertex || to < 1 || to > *vertex) {
      printf("bad vertex");
      free(*matrix);
      return 1;
    }

    if (len > INT_MAX) {
      printf("bad length");
      free(*matrix);
      return 1;
    }
    (*matrix)[(from - 1) * *vertex + (to - 1)] = len;
    (*matrix)[(to - 1) * *vertex + (from - 1)] = len;
  }
  return 0;
}
