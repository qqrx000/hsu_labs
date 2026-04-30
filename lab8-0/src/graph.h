#ifndef GRAPH_H
#define GRAPH_H
#include <stddef.h>
typedef struct edges edges;
typedef struct graph graph;

graph *graphInit(int edge);

size_t getSizeOfEdges(void);

int setEdge(graph *g, int index, short start, short finish, unsigned int len);

int getEdge(const graph *g, int index, short *start, short *finish,
            unsigned int *len);

int getEdgeCount(const graph *g);

void sortEdges(graph *g);

void freeGraph(graph *g);

#endif
