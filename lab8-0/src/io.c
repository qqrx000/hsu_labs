#include "io.h"
#include "graph.h"
#include <limits.h>
#include <stdio.h>

#define MAX_VERTICES 5000

int read(short *vertex, int *edge, graph **g) {
  if (scanf("%hd", vertex) != 1) {
    printf("bad number of lines");
    return 1;
  }

  if (*vertex < 0 || *vertex > MAX_VERTICES) {
    printf("bad number of vertices");
    return 1;
  }

  if (scanf("%d", edge) != 1) {
    printf("bad number of lines");
    return 1;
  }

  if (*edge < 0 || *edge > *vertex * (*vertex - 1) / 2) {
    printf("bad number of edges");
    return 1;
  }
  *g = graphInit(*edge);
  if (!*g) {
    printf("bad mem");
    return 1;
  }

  for (int i = 0; i < *edge; ++i) {
    short start, finish;
    unsigned int len;
    if (scanf("%hd %hd %u", &start, &finish, &len) != 3) {
      printf("bad number of lines");
      freeGraph(*g);
      return 1;
    }
    if (len > INT_MAX) {
      printf("bad length");
      freeGraph(*g);
      return 1;
    }
    if (start < 1 || start > *vertex || finish < 1 || finish > *vertex) {
      printf("bad vertex");
      freeGraph(*g);
      return 1;
    }
    if (setEdge(*g, i, start, finish, len) == 1) {
      freeGraph(*g);
      return 1;
    }
  }
  return 0;
}
