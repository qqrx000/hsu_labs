#include "graph.h"
#include <stdlib.h>

struct edges {
  short start, finish;
  unsigned int len;
};

struct graph {
  edges *edgArr;
  int edgCount;
};

size_t getSizeOfEdges(void) { return sizeof(edges); }

graph *graphInit(const int edge) {
  graph *g = malloc(sizeof(graph));
  if (!g) {
    return NULL;
  }
  g->edgArr = malloc(edge * sizeof(edges));
  if (!g->edgArr) {
    free(g);
    return NULL;
  }
  g->edgCount = edge;
  return g;
}

int setEdge(graph *g, const int index, const short start, const short finish,
            const unsigned int len) {
  if (!g || index < 0 || index >= g->edgCount) {
    return 1;
  }
  g->edgArr[index].start = start;
  g->edgArr[index].finish = finish;
  g->edgArr[index].len = len;
  return 0;
}

int getEdge(const graph *g, const int index, short *start, short *finish,
            unsigned int *len) {
  if (!g || index < 0 || index >= g->edgCount) {
    return 1;
  }
  *start = g->edgArr[index].start;
  *finish = g->edgArr[index].finish;
  *len = g->edgArr[index].len;
  return 0;
}

int getEdgeCount(const graph *g) { return g ? g->edgCount : 0; }

static int compare(const void *a, const void *b) {
  const edges *e1 = a;
  const edges *e2 = b;
  if (e1->len < e2->len)
    return -1;
  if (e1->len > e2->len)
    return 1;
  return 0;
}

void sortEdges(graph *g) {
  qsort(g->edgArr, g->edgCount, sizeof(edges), compare);
}

void freeGraph(graph *g) {
  if (!g)
    return;
  free(g->edgArr);
  free(g);
}
