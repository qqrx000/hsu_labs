#include "io.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int vertex;
  if (read(&vertex) == 1) {
    return EXIT_SUCCESS;
  }

  tree *mem = malloc(vertex * sizeof(tree));
  if (!mem) {
    printf("malloc failed");
    return EXIT_SUCCESS;
  }

  int memIdx = 0;

  tree *root = NULL;
  int number = 0;
  const char logEnable = (char)(vertex < 100);
  for (int i = 0; i < vertex; ++i) {
    if (scanf("%d", &number) != 1) {
      printf("Bad input");
      return EXIT_SUCCESS;
    }
    root = insert(root, number, logEnable, mem, &memIdx);
  }
  const char height = getHeight(root);
  printf("%d", height);
  free(mem);
  return EXIT_SUCCESS;
}
