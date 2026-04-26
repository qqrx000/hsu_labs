#include "bitmatrix.h"
#include "io.h"
#include "kan.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n, m;
  short *inDegree = NULL;
  bitMatrix *adj = NULL;
  short *result = NULL;

  if (!read(&n, &m, &inDegree, &adj)) {
    return EXIT_SUCCESS;
  }

  if (n == 0) {
    printf("\n");
    goto End;
  }

  result = (short *)malloc(n * sizeof(short));
  if (!result) {
    printf("bad memory");
    goto End;
  }

  if (topoSort(n, adj, inDegree, result)) {
    printResult(result, n);
  } else {
    printf("impossible to sort\n");
  }
End:
  free(inDegree);
  freeBitMatrix(adj);
  free(result);

  return EXIT_SUCCESS;
}
