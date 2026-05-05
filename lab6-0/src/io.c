#include "io.h"
#include <stdio.h>

int read(int *vertex) {
  if (scanf("%d", vertex) != 1) {
    printf("Empty input\n");
    return 1;
  }
  if (*vertex > 2000000 || *vertex < 0) {
    printf("Bad input\n");
    return 1;
  }
  if (*vertex == 0) {
    printf("0\n");
    return 1;
  }
  return 0;
}
