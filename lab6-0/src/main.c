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
  int idx = 0;
  tree *root = NULL;
  int number = 0;
  for (int i = 0; i < vertex; ++i) {
    if (scanf("%d", &number) != 1) {
      printf("Bad input");
      freeTree(root);
      return EXIT_SUCCESS;
    }
    root = insert(root, number, logEnable, &idx);
  }
  const int height = getHeight(root);
  printf("%d", height);
  freeTree(root);
  return EXIT_SUCCESS;
}
