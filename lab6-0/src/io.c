#include "io.h"
#include <stdio.h>

int read(int *vertex) {
  if (scanf("%d", vertex) != 1) {
    printf("Empty input");
    return 1;
  }
  if (*vertex > 2000000 || *vertex < 0) {
    printf("Bad input");
    return 1;
  }
  return 0;
}
