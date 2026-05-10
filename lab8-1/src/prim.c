#include "graph.h"
#include <limits.h>
#include <stdio.h>

#define INF UINT_MAX

#define MAX_VERTEX 5000

void prim(const graph *g) {
  const int vertex = getVertexCount(g);
  if (vertex < 1) {
    printf("no spanning tree");
    return;
  }

  unsigned int minEdge[MAX_VERTEX + 1];
  int parent[MAX_VERTEX + 1];
  char used[MAX_VERTEX + 1];

  for (int i = 1; i <= vertex; ++i) {
    minEdge[i] = INF;
    parent[i] = -1;
    used[i] = 0;
  }
  minEdge[1] = 0;
  for (int i = 1; i <= vertex; ++i) {
    int v = -1;
    for (int j = 1; j <= vertex; ++j) {
      if (!used[j] && (v == -1 || minEdge[j] < minEdge[v])) {
        v = j;
      }
    }
    if (v == -1 || minEdge[v] == INF) {
      printf("no spanning tree");
      return;
    }
    used[v] = 1;
    for (int to = 1; to <= vertex; ++to) {
      const unsigned int w = getEdge(g, v, to);
      if (!used[to] && w > 0 && w < minEdge[to]) {
        minEdge[to] = w;
        parent[to] = v;
      }
    }
  }
  for (int i = 2; i <= vertex; ++i) {
    printf("%d %d\n", parent[i], i);
  }
}
