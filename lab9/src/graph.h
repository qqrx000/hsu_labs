#ifndef GRAPH_H
#define GRAPH_H
#include <stddef.h>

typedef struct graph graph;

graph *graphInit(void);

void graphDestroy(graph *g);

int graphRead(graph *g);

struct graphEdge;

int graphGetEdge(const graph *g, size_t index, size_t *from, size_t *to, size_t *len);
size_t graphGetVertex(const graph *g);
size_t graphGetEdgeCount(const graph *g);
size_t graphGetStart(const graph *g);
size_t graphGetFinish(const graph *g);

#endif
