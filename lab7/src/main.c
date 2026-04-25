#include "io.h"
#include "kan.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int vertex, edge;
  size_t *inDegree = NULL;
  node **adjList = NULL;

  if (read(&vertex, &edge, &adjList, &inDegree)) {
    free(inDegree);
    free(adjList);
    return  EXIT_SUCCESS;
  }

  size_t *result = malloc(vertex * sizeof(size_t));
  if (!result) {
    printf("bad memory");
    free(inDegree);
    free(adjList);
    return EXIT_SUCCESS;
  }

  if (topoSort(vertex, adjList, inDegree, result)) {
    printf("impossible to sort");
  } else {
    printResult(result, vertex);
  }

  for (int i = 1; i <= vertex; i++) {
    freeNodes(adjList[i]);
  }
  free(adjList);
  free(inDegree);
  free(result);

  return EXIT_SUCCESS;
}
