#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int weight;
    int value;
} Item;

int main(void) {
    int n, capacity;
    if (scanf("%d %d", &n, &capacity) != 2) {
        printf("bad input\n");
        return EXIT_SUCCESS;
    }

    Item *items = malloc(n * sizeof(Item));

    for (int i = 0; i < n; ++i) {
        if (scanf("%d %d", &items[i].weight, &items[i].value) != 2) {
            printf("bad input\n");
            free(items);
            return EXIT_SUCCESS;
        }

    }

    int **maxValue = malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; ++i) {
        maxValue[i] = calloc(capacity + 1, sizeof(int));
    }

    for (int i = 1; i <= n; ++i) {
        const int w = items[i - 1].weight;
        const int v = items[i - 1].value;

        for (int j = 0; j <= capacity; j++) {
            maxValue[i][j] = maxValue[i - 1][j];

            if (j >= w) {
                const int candidate = maxValue[i - 1][j - w] + v;
                if (candidate > maxValue[i][j]) {
                    maxValue[i][j] = candidate;
                }
            }
        }
    }

    const int best_value = maxValue[n][capacity];
    printf("%d\n", best_value);

    int *chosen = calloc(n, sizeof(int));

    int j = capacity;
    for (int i = n; i > 0; i--) {
        if (maxValue[i][j] != maxValue[i - 1][j]) {
            chosen[i - 1] = 1;
            j -= items[i - 1].weight;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (chosen[i]) {
            printf("%d %d\n", items[i].weight, items[i].value);
        }
    }

    for (int i = 0; i <= n; ++i) {
        free(maxValue[i]);
    }
    free(maxValue);
    free(items);
    free(chosen);

    return 0;
}
