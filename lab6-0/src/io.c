#include "io.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

int read(int *vertex, int **numbers) {
  if (scanf("%d", vertex) != 1) {
    printf("Empty input");
    return 1;
  }
  if (*vertex > 2000000 || *vertex < 0) {
    printf("Bad input");
    return 1;
  }
  *numbers = malloc(sizeof(int) * *vertex);
  if (!*numbers) {
    printf("malloc failed");
    return 1;
  }
  for (int i = 0; i < *vertex; ++i) {
    if (scanf("%d", *numbers + i) != 1) {
      printf("Bad input");
      free(*numbers);
      return 1;
    }
  }
  return 0;
}

void printResult(const int *log, const int idx, const int logEnable, const size_t height) {
  if (logEnable) {
    for (int i = 0; i < idx; i++) {
      switch (log[i]) {
      case SL:
        printf("SL");
        break;
      case SR:
        printf("SR");
        break;
      case BL:
        printf("BL");
        break;
      case BR:
        printf("BR");
        break;
      default:
        //printf("switch case error");
        break;
      }
      printf(" ");
    }
  }
  printf("%zu", height);
}
