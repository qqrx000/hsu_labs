#ifndef TOPSORT_H
#define TOPSORT_H

struct bitMatrix;
int topoSort(int n, const struct bitMatrix *adj, short *inDegree, short *result);

#endif
