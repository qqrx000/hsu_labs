#include "io.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int vertex;
  if (read(&vertex) == 1) {
    return EXIT_SUCCESS;
  }

  const int logEnable = vertex < 100;
  int *log = NULL;
  if (logEnable) {
    log = malloc(vertex * sizeof(*log));
    if (!log) {
      printf("malloc failed");
      return EXIT_SUCCESS;
    }
  }
  int idx = 0;
  tree *root = NULL;
  int number = 0;
  for (int i = 0; i < vertex; ++i) {
    if (scanf("%d", &number) != 1) {
      printf("Bad input");
      freeTree(root);
      free(log);
      return EXIT_SUCCESS;
    }
    root = insert(root, number, log, logEnable, &idx);
  }
  const int height = getHeight(root);
  printResult(log, idx, logEnable, height);
  freeTree(root);
  free(log);
  return EXIT_SUCCESS;
}
