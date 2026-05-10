#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph graph;

graph *graphInit(int vertexCount);
void graphFree(graph *g);

void setEdge(const graph *g, int u, int v, unsigned int w);

int getVertexCount(const graph *g);
unsigned int getEdge(const graph *g, int u, int v);
void freeGraph(graph *g);

#endif
