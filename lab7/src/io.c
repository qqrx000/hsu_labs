#include "io.h"
#include "bitmatrix.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 2000

int read(int *n, int *m, short **inDegree, bitMatrix **adj) {
  if (scanf("%d", n) != 1) {
    printf("bad number of lines");
    return 0;
  }

  if (*n < 0 || *n > MAX_VERTICES) {
    printf("bad number of vertices");
    return 0;
  }

  if (scanf("%d", m) != 1) {
    printf("bad number of lines");
    return 0;
  }

  if (*m < 0 || *m > *n * (*n - 1) / 2) {
    printf("bad number of edges");
    return 0;
  }

  if (*n == 0) {
    return 1;
  }

  *inDegree = (short *)calloc(*n + 1, sizeof(short));
  if (!*inDegree) {
    printf("bad memory");
    return 0;
  }

  *adj = createBitMatrix(*n);
  if (!*adj) {
    free(*inDegree);
    return 0;
  }

  for (int i = 0; i < *m; ++i) {
    int u, v;
    if (scanf("%d %d", &u, &v) != 2) {
      printf("bad number of lines");
      return 0;
    }

    if (u < 1 || u > *n || v < 1 || v > *n) {
      printf("bad vertex");
      free(*inDegree);
      freeBitMatrix(*adj);
      return 0;
    }
    setEdge(*adj, u, v);
    (*inDegree)[v]++;
  }

  return 1;
}

void printResult(const short *result, const int n) {
  if (!result || n <= 0)
    return;
  for (int i = 0; i < n; i++) {
    printf("%d", result[i]);
    if (i + 1 < n) {
      printf(" ");
    }
  }
  printf("\n");
}
