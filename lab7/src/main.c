#include "io.h"
#include "list.h"
#include <stdlib.h>

int main(void) {
    size_t vertex, edge;
    size_t *inDegree = NULL;
    node **adjList = NULL;
    if (read(&vertex, &edge, &adjList, &inDegree)) {
        free(inDegree);
        free(adjList);
        return EXIT_SUCCESS;
    }
    //somewhat algorithm
    free(adjList);
    free(inDegree);
    return EXIT_SUCCESS;
}
