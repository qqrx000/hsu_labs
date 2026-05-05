#ifndef BITMATRIX_H
#define BITMATRIX_H

typedef struct bitMatrix bitMatrix;

bitMatrix *createBitMatrix(int n);
void freeBitMatrix(bitMatrix *bm);
void setEdge(bitMatrix *bm, int from, int to);
int hasEdge(const bitMatrix *bm, int from, int to);
int getWordsPerRow(const bitMatrix *bm);
const unsigned int *getData(const bitMatrix *bm);

#endif
