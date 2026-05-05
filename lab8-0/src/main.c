#include "graph.h"
#include "io.h"
#include "kruskal.h"
#include <stdlib.h>

int main(void) {
    short vertex;
    int edge;
    graph *g = NULL;
    if (read(&vertex, &edge, &g) == 1) {
        return EXIT_SUCCESS;
    }
    kruskal(g, vertex);
    freeGraph(g);
    return EXIT_SUCCESS;
}
