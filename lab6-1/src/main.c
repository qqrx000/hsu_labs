#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

int read(int *vertex);

int main(void) {
    int vertex;
    if (read(&vertex) == 1) {
        return EXIT_SUCCESS;
    }

    rbtree *root = newTree(vertex);
    if (!root) {
        printf("Bad input\n");
        return EXIT_SUCCESS;
    }

    for (int i = 0; i < vertex; ++i) {
        int number;
        if (scanf("%d", &number) != 1) {
            printf("Bad input\n");
            freeTree(root);
            return EXIT_SUCCESS;
        }
        insert(root, number);
    }
    printf("%d", getBlackHeight(root));
    freeTree(root);
    return EXIT_SUCCESS;
}

int read(int *vertex) {
    if (scanf("%d", vertex) != 1) {
        printf("Empty input\n");
        return 1;
    }
    if (*vertex > 2000000 || *vertex < 0) {
        printf("Bad input\n");
        return 1;
    }
    if (*vertex == 0) {
        printf("0\n");
        return 1;
    }
    return 0;
}
