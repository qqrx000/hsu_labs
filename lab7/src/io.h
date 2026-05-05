#ifndef IO_H
#define IO_H

struct bitMatrix;

int read(int *n, int *m, short **inDegree, struct bitMatrix **adj);

void printResult(const short *result, int n);

#endif
