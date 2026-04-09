#include <stdio.h>
#include <stdlib.h>

#define SIZE_T_MAX ULONG_MAX

int read(size_t *vertex, size_t *edge, size_t *start, size_t *finish,
         size_t **matrix);

char initChArr(char **arr, size_t vertex, size_t **matrix);

char initSztArr(size_t **arr, size_t vertex, size_t **matrix, char **visited);

int main(void) {
  size_t vertex, edge, start, finish;
  size_t *matrix = NULL;

  if (read(&vertex, &edge, &start, &finish, &matrix) == 1)
    return EXIT_SUCCESS;

  char *visited = NULL;
  size_t *distance = NULL;
  if (initChArr(&visited, vertex, &matrix) == 1)
    return EXIT_SUCCESS;
  if (initSztArr(&distance, vertex, &matrix, &visited) == 1)
    return EXIT_SUCCESS;
  for (size_t i = 0; i < vertex; ++i) {
    visited[i] = 1;
    distance[i] = SIZE_T_MAX;
  }
  distance[start] = 0;
  size_t minIndex = 0;
  while (minIndex < SIZE_T_MAX - 1) {
    minIndex = SIZE_T_MAX;
    size_t min = SIZE_T_MAX;
    for (size_t i = 0; i < vertex; ++i) {
      if (visited[i] == 1 && distance[i] < min) {
        min = distance[i];
        minIndex = i;
      }
    }
    if (minIndex != SIZE_T_MAX) {
      for (size_t i = 0; i < vertex; ++i) {
        if (matrix[minIndex * vertex + i] <= 0) continue;
        const size_t tmp = min + matrix[minIndex * vertex + i];
          if (tmp < distance[i]) distance[i] = tmp;
      }
      visited[minIndex] = 0;
    }
  }

  //

  free(matrix);
  return EXIT_SUCCESS;
}

int read(size_t *vertex, size_t *edge, size_t *start, size_t *finish,
         size_t **matrix) {
  if (scanf("%zu", vertex) != 1 || *vertex > 5000) {
    printf("bad number of vertices");
    return 1;
  }
  if (scanf("%zu %zu", start, finish) != 2 || *start < 1 || *finish < 1 ||
      *start > *vertex || *finish > *vertex) {
    printf("bad vertex");
    return 1;
  }
  if (scanf("%zu", edge) != 1 || *edge > *vertex * (*vertex - 1) / 2) {
    printf("bad number of edges");
    return 1;
  }

  *matrix = calloc(*vertex * *vertex, sizeof(size_t));
  if (!*matrix) {
    printf("malloc failed");
    return 1;
  }

  for (size_t i = 0; i < *edge; ++i) {
    size_t from, to;
    size_t len;

    if (scanf("%zu %zu %zu", &from, &to, &len) != 3) {
      printf("bad number of lines");
      free(*matrix);
      return 1;
    }

    if (from < 1 || from > *vertex || to < 1 || to > *vertex) {
      printf("bad vertex");
      free(*matrix);
      return 1;
    }

    if (len > INT_MAX) {
      printf("bad length");
      free(*matrix);
      return 1;
    }
    (*matrix)[(from - 1) * *vertex + (from - 1)] = 0;
    (*matrix)[(from - 1) * *vertex + (to - 1)] = len;
    (*matrix)[(to - 1) * *vertex + (from - 1)] = len;
  }
  return 0;
}

char initChArr(char **arr, const size_t vertex, size_t **matrix) {
  arr = malloc(vertex * sizeof(char));
  if (!arr) {
    printf("malloc failed");
    free(matrix);
    free(arr);
    return 1;
  }
  return 0;
}

char initSztArr(size_t **arr, const size_t vertex, size_t **matrix,
                char **visited) {
  arr = malloc(vertex * sizeof(size_t));
  if (!arr) {
    printf("malloc failed");
    free(matrix);
    free(visited);
    free(arr);
    return 1;
  }
  return 0;
}