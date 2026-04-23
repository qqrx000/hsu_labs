#include "io.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int read(size_t *vertex, size_t *edge, node ***adjList, size_t **inDegree) {
  if (scanf("%zu", vertex) != 1 || *vertex > 2000) {
    printf("bad number of vertices");
    return 1;
  }
  if (scanf("%zu", edge) != 1 || *edge > *vertex * (*vertex - 1) / 2) {
    printf("bad number of edges");
    return 1;
  }

  *inDegree = calloc(*vertex + 1, sizeof(size_t));
  if (!*inDegree) {
    printf("bad memory");
    return 1;
  }
  *adjList = malloc((*vertex+1) * sizeof(node*));
  if (!*adjList) {
    printf("bad memory");
    free(*inDegree);
    return 1;
  }
  size_t start, finish;
  for (size_t i = 0; i < *edge; ++i) { //maybe have to check lines after *edge value
    if (scanf("%zu %zu", &start, &finish) != 2) {
      printf("bad number of lines");
      free(*inDegree);
      free(*adjList);
      return 1;
    }
    if (start < 1 || finish < 1 || start > *vertex ||
        finish > *vertex) {
      printf("bad vertex");
      free(*inDegree);
      free(*adjList);
      return 1;
    }
    pushFront(&(*adjList)[start], finish);
    (*inDegree)[finish]++;
  }
  return 0;
}
