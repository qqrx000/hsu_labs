#include "deikstra.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  size_t vertex, edge, start, finish;
  int *matrix = NULL;

  if (read(&vertex, &edge, &start, &finish, &matrix) == 1)
    return EXIT_SUCCESS;
  char *visited = NULL;
  size_t *pathCount = NULL;
  size_t *distance = NULL;
  size_t *parent = NULL;
  visited = malloc(vertex * sizeof(char));
  if (!visited) {
    printf("malloc failed\n");
    goto End;
  }
  pathCount = calloc(vertex, sizeof(size_t));
  if (!pathCount) {
    printf("malloc failed\n");
    goto End;
  }
  distance = malloc(vertex * sizeof(size_t));
  if (!distance) {
    printf("malloc failed\n");
    goto End;
  }
  parent = malloc(vertex * sizeof(size_t));
  if (!parent) {
    printf("malloc failed\n");
    goto End;
  }

  start--;
  finish--;

  deikstraAlgorithm(matrix, distance, parent, visited, pathCount, vertex,
                    start);
  printDistance(distance, start, vertex);
  printPath(finish, parent, distance, vertex, start, pathCount);
End:
  free(matrix);
  free(distance);
  free(visited);
  free(pathCount);
  free(parent);
  return EXIT_SUCCESS;
}
