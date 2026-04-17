#include "io.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int vertex;
  int *numbers = NULL;
  if (read(&vertex, &numbers) == 1) {
    return EXIT_SUCCESS;
  }
  const int logEnable = vertex < 100;
  int *log = NULL;
  if (logEnable) {
    log = malloc(vertex * sizeof(*log));
    if (!log) {
      printf("malloc failed");
      free(numbers);
      return EXIT_SUCCESS;
    }
  }
  int idx = 0;
  tree *root = NULL;
  for (int i = 0; i < vertex; ++i) {
    root = insert(root, numbers[i], log, logEnable, &idx);
  }
  const size_t height = getHeight(root);
  printResult(log, idx, logEnable, height);
  freeTree(root);
  free(log);
  free(numbers);
  return EXIT_SUCCESS;
}
