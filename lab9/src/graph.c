#include "graph.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t from;
    size_t to;
    size_t len;
} graphEdge;

struct graph {
    size_t vertex;
    size_t edge;
    size_t start;
    size_t finish;
    graphEdge *edges;
};

graph *graphInit(void) {
    graph *g = malloc(sizeof(graph));
    if (g == NULL) {
        return NULL;
    }
    g->vertex = 0;
    g->edge = 0;
    g->edges = NULL;
    return g;
}

void graphDestroy(graph *g) {
    if (g) {
        if (g->edges) {
            free(g->edges);
        }
        free(g);
    }
}

int graphRead(graph *g) {
    if (!g) return 1;
    if (scanf("%zu", &g->vertex) != 1 || g->vertex > 5000) {
        printf("bad number of vertices");
        return 1;
    }
    if (scanf("%zu %zu", &g->start, &g->finish) != 2 || g->start < 1 || g->finish < 1 || g->start > g->vertex || g->
        finish > g->vertex) {
        printf("bad vertex");
        return 1;
    }

    if (scanf("%zu", &g->edge) != 1 || g->edge > g->vertex * (g->vertex - 1) / 2) {
        printf("bad number of edges");
        return 1;
    }
    if (g->edge > 0) {
        g->edges = (graphEdge *) malloc(sizeof(graphEdge) * g->edge);
        if (g->edges == NULL) {
            printf("malloc failed");
            return 1;
        }
    }

    for (size_t i = 0; i < g->edge; ++i) {
        if (scanf("%zu %zu %zu", &g->edges[i].from, &g->edges[i].to, &g->edges[i].len) != 3) {
            printf("bad number of lines");
            return 1;
        }
        if (g->edges[i].from > g->vertex || g->edges[i].to > g->vertex) {
            printf("bad vertex");
            return 1;
        }
        if (g->edges[i].len > INT_MAX) {
            printf("bad length");
            return 1;
        }
    }
    return 0;
}

size_t graphGetVertex(const graph *g) {
    return g ? g->vertex : 0;
}

size_t graphGetEdgeCount(const graph *g) {
    return g ? g->edge : 0;
}

size_t graphGetStart(const graph *g) {
    return g ? g->start : 0;
}

size_t graphGetFinish(const graph *g) {
    return g ? g->finish : 0;
}

int graphGetEdge(const graph *g, const size_t index, size_t *from, size_t *to, size_t *len) {
    if (!g || !g->edges || index >= g->edge) return -1;
    if (from) *from = g->edges[index].from;
    if (to) *to = g->edges[index].to;
    if (len) *len = g->edges[index].len;
    return 0;
}