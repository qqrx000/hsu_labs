#include "graph.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_T_MAX ULONG_MAX

int main(void) {
  graph *graph = graphInit();
  if (!graph) {
    printf("Error creating graph\n");
    return EXIT_SUCCESS;
  }
  if (graphRead(graph) == 1) {
    graphDestroy(graph);
    return EXIT_SUCCESS;
  }
  const size_t start = graphGetStart(graph);
  const size_t finish = graphGetFinish(graph);
  const size_t vertexCount = graphGetVertex(graph);

  for (size_t i = start; i < vertexCount; ++i) {

  }
  graphDestroy(graph);
  return EXIT_SUCCESS;
}
