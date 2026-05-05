#include "io.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int vertex;
  if (read(&vertex) == 1) {
    return EXIT_SUCCESS;
  }

  tree *mem = malloc((size_t)vertex * sizeof(tree));
  if (!mem) {
    printf("Bad input\n");
    return EXIT_SUCCESS;
  }

  int memIdx = 0;
  tree *root = NULL;
  const char logEnable = (char)(vertex < 100);
  for (int i = 0; i < vertex; ++i) {
    int number;
    if (scanf("%d", &number) != 1) {
      printf("Bad input\n");
      free(mem);
      return EXIT_SUCCESS;
    }
    root = insert(root, number, logEnable, mem, &memIdx);
  }
  printf("%d", getHeight(root));
  free(mem);
  return EXIT_SUCCESS;
}
