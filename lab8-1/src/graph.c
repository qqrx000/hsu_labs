#include "graph.h"
#include <stdlib.h>

#define INF 0

struct graph {
  unsigned int **a;
  int n;
};

graph *graphInit(const int vertexCount) {
  graph *g = malloc(sizeof(graph));
  if (!g)
    return NULL;
  g->n = vertexCount;
  g->a = malloc((vertexCount + 1) * sizeof(unsigned int *));
  if (!g->a) {
    freeGraph(g);
    return NULL;
  }

  for (int i = 1; i <= vertexCount; ++i) {
    g->a[i] = calloc(vertexCount + 1, sizeof(unsigned int));
    if (!g->a[i]) {
      freeGraph(g);
      return NULL;
    }
  }
  return g;
}

void setEdge(const graph *g, const int u, const int v, const unsigned int w) {
  g->a[u][v] = w;
  g->a[v][u] = w;
}

unsigned int getEdge(const graph *g, const int u, const int v) {
  return g->a[u][v];
}

int getVertexCount(const graph *g) { return g->n; }

void freeGraph(graph *g) {
  if (!g)
    return;
  if (g->a) {
    for (int i = 1; i <= g->n; ++i) {
      free(g->a[i]);
    }
    free(g->a);
  }
  free(g);
}
