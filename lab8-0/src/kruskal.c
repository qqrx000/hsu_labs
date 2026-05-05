#include "graph.h"
#include <stdio.h>

#define MAX_VERTICES 5000

// DSU
static int parent[MAX_VERTICES + 1];

static void makeSet(const int n) {
  for (int i = 1; i <= n; ++i) {
    parent[i] = i;
  }
}

static int findSet(const int finish) {
  if (finish == parent[finish])
    return finish;
  return parent[finish] = findSet(parent[finish]);
}

static void uniteSets(int a, int b) {
  a = findSet(a);
  b = findSet(b);
  if (a != b) {
    parent[b] = a;
  }
}

void kruskal(graph *g, const int vertexCount) {
  sortEdges(g);

  makeSet(vertexCount);

  const int edgeCount = getEdgeCount(g);

  short resultU[MAX_VERTICES];
  short resultV[MAX_VERTICES];
  int count = 0;

  for (int i = 0; i < edgeCount; ++i) {
    short start, finish;
    unsigned int w;

    if (getEdge(g, i, &start, &finish, &w) == 1) {
      printf("error in args");
      return;
    }

    if (findSet(start) != findSet(finish)) {
      uniteSets(start, finish);

      resultU[count] = start;
      resultV[count] = finish;
      count++;
    }
  }

  if (count != vertexCount - 1) {
    printf("no spanning tree");
    return;
  }

  for (int i = 0; i < count; ++i) {
    printf("%hd %hd\n", resultU[i], resultV[i]);
  }
}
