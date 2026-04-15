#include "deikstra.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  size_t vertex, edge, start, finish;
  int *matrix = NULL;

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
