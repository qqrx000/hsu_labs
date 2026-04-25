#include "io.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int read(int *vertex, int *edge, node ***adjList, size_t **inDegree) {

  if (scanf("%d", vertex) != 1 || *vertex > 2000) {
    printf("bad number of vertices");
    return 1;
  }

  if (scanf("%d", edge) != 1 || *edge > *vertex * (*vertex - 1) / 2) {
    printf("bad number of edges");
    return 1;
  }

  *inDegree = calloc(*vertex + 1, sizeof(size_t));
  if (!*inDegree) {
    printf("bad memory");
    return 1;
  }

  *adjList = calloc(*vertex + 1, sizeof(node *));
  if (!*adjList) {
    printf("bad memory");
    free(*inDegree);
    return 1;
  }

  int start, finish;

  for (int i = 0; i < *edge; i++) {
    if (scanf("%d %d", &start, &finish) != 2) {
      printf("bad number of lines");
      return 1;
    }

    if (start < 1 || finish < 1 || start > *vertex || finish > *vertex) {
      printf("bad vertex");
      return 1;
    }

    pushFront(&(*adjList)[start], finish);
    (*inDegree)[finish]++;
  }

  return 0;
}

void printResult(const size_t *result, const size_t vertex) {
  for (size_t i = 0; i < vertex; i++) {
    printf("%zu", result[i]);
    if (i + 1 < vertex)
      printf(" ");
  }
}
