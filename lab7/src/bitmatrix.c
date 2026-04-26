#include "bitmatrix.h"
#include <stdio.h>
#include <stdlib.h>

#define BITS_PER_WORD 64

struct bitMatrix {
  unsigned int *data;
  int rows;
  int cols;
  int wordPerRow;
};

bitMatrix *createBitMatrix(const int n) {
  if (n < 0)
    return NULL;

  bitMatrix *bm = malloc(sizeof(bitMatrix));
  if (!bm) {
    printf("bad memory");
    return NULL;
  }

  bm->rows = n + 1;
  bm->cols = n + 1;
  bm->wordPerRow = (bm->cols + BITS_PER_WORD - 1) / BITS_PER_WORD;

  const size_t size = bm->rows * bm->wordPerRow * sizeof(int);
  bm->data = calloc(1, size);

  if (!bm->data && size > 0) {
    printf("bad memory");
    free(bm);
    return NULL;
  }
  return bm;
}

void freeBitMatrix(bitMatrix *bm) {
  if (bm) {
    free(bm->data);
    free(bm);
  }
}

void setEdge(bitMatrix *bm, const int from, const int to) {
  if (!bm || !bm->data)
    return;

  const int wordIdx = from * bm->wordPerRow + to / BITS_PER_WORD;
  const int bitIdx = to % BITS_PER_WORD;
  bm->data[wordIdx] |= 1ULL << bitIdx;
}

int hasEdge(const bitMatrix *bm, const int from, const int to) {
  if (!bm || !bm->data)
    return 0;

  const int wordIdx = from * bm->wordPerRow + to / BITS_PER_WORD;
  const int bitIdx = to % BITS_PER_WORD;
  return (int)bm->data[wordIdx] >> bitIdx & 1;
}

int getWordsPerRow(const bitMatrix *bm) { return bm ? bm->wordPerRow : 0; }

const unsigned int *getData(const bitMatrix *bm) {
  return bm ? bm->data : NULL;
}
