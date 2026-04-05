#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int weight;
  int value;
} Item;

int readInput(int *count, int *capacity, Item **items);
int** allocTable(int count, int capacity);
void fillTable(const Item *items, int count, int capacity, int **maxValue);
void result(const Item *items, int count, int capacity, int **maxValue);
void freeMemory(Item *items, int **maxValue, int count, int *chosen);

int main(void) {
  int count, capacity;
  Item *items = NULL;

  if (readInput(&count, &capacity, &items) == 1) {
    return EXIT_SUCCESS;
  }

  int **maxValue = allocTable(count, capacity);
  if (!maxValue) {
    free(items);
    printf("bad input");
    return EXIT_FAILURE;
  }

  fillTable(items, count, capacity, maxValue);

  const int best_value = maxValue[count][capacity];
  printf("%d\n", best_value);

  result(items, count, capacity, maxValue);

  freeMemory(items, maxValue, count, NULL);

  return 0;
}

int readInput(int *count, int *capacity, Item **items) {
  if (scanf("%d %d", count, capacity) != 2) {
    printf("bad input");
    return 1;
  }

  *items = malloc(*count * sizeof(Item));
  if (!*items) {
    printf("bad input");
    return 1;
  }

  for (int i = 0; i < *count; ++i) {
    if (scanf("%d %d", &(*items)[i].weight, &(*items)[i].value) != 2) {
      printf("bad input");
      free(*items);
      return 1;
    }
  }
  return 0;
}

int** allocTable(const int count, const int capacity) {
  int **maxValue = malloc((count + 1) * sizeof(int *));
  if (!maxValue) {
    return NULL;
  }

  for (int i = 0; i <= count; ++i) {
    maxValue[i] = calloc(capacity + 1, sizeof(int));
    if (!maxValue[i]) {
      for (int k = 0; k < i; ++k)
        free(maxValue[k]);
      free(maxValue);
      return NULL;
    }
  }
  return maxValue;
}

void fillTable(const Item *items, const int count, const int capacity, int **maxValue) {
  for (int i = 1; i <= count; ++i) {
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
}

void result(const Item *items, const int count, const int capacity, int **maxValue) {
  int *chosen = calloc(count, sizeof(int));
  if (!chosen) {
    printf("bad input");
    return;
  }

  int j = capacity;
  for (int i = count; i > 0; i--) {
    if (maxValue[i][j] != maxValue[i - 1][j]) {
      chosen[i - 1] = 1;
      j -= items[i - 1].weight;
    }
  }

  for (int i = 0; i < count; ++i) {
    if (chosen[i]) {
      printf("%d %d\n", items[i].weight, items[i].value);
    }
  }

  free(chosen);
}

void freeMemory(Item *items, int **maxValue, const int count, int *chosen) {
  if (chosen) free(chosen);
  for (int i = 0; i <= count; ++i) {
    free(maxValue[i]);
  }
  free(maxValue);
  free(items);
}
