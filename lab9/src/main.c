#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_T_MAX 4294967295

int read(size_t *vertex, size_t *edge, size_t *start, size_t *finish,
         size_t **matrix);

char initParentArr(size_t **arr, size_t vertex, size_t **matrix);

char initChArr(char **arr, size_t vertex, size_t **matrix, size_t **parent);

char initSztArr(size_t **arr, size_t vertex, size_t **matrix, char **visited,
                size_t **parent);

void deikstraAlgorithm(const size_t *matrix, size_t *distance, size_t *parent,
                       char *visited, size_t vertex, size_t start);

void printDistance(const size_t *distance, size_t start, size_t vertex);

void printPath(size_t finish, const size_t *parent, const size_t *distance,
               size_t vertex, size_t start);

int main(void) {
  size_t vertex, edge, start, finish;
  size_t *matrix = NULL;

  if (read(&vertex, &edge, &start, &finish, &matrix) == 1)
    return EXIT_SUCCESS;

  char *visited = NULL;
  size_t *distance = NULL;
  size_t *parent = NULL;
  if (initParentArr(&parent, vertex, &matrix) == 1)
    return EXIT_SUCCESS;
  if (initChArr(&visited, vertex, &matrix, &parent) == 1)
    return EXIT_SUCCESS;
  if (initSztArr(&distance, vertex, &matrix, &visited, &parent) == 1)
    return EXIT_SUCCESS;
  start--;
  finish--;
  deikstraAlgorithm(matrix, distance, parent, visited, vertex, start);

  printDistance(distance, vertex, finish);

  printPath(finish, parent, distance, vertex, start);
  free(matrix);
  free(distance);
  free(parent);
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
    (*matrix)[(from - 1) * *vertex + (to - 1)] = len;
    (*matrix)[(to - 1) * *vertex + (from - 1)] = len;
  }
  return 0;
}

char initParentArr(size_t **arr, const size_t vertex, size_t **matrix) {
  *arr = malloc(vertex * sizeof(size_t));
  if (!*arr) {
    printf("malloc failed");
    free(matrix);
    free(arr);
    return 1;
  }
  return 0;
}

char initChArr(char **arr, const size_t vertex, size_t **matrix,
               size_t **parent) {
  *arr = malloc(vertex * sizeof(char));
  if (!*arr) {
    printf("malloc failed");
    free(matrix);
    free(arr);
    free(parent);
    return 1;
  }
  return 0;
}

char initSztArr(size_t **arr, const size_t vertex, size_t **matrix,
                char **visited, size_t **parent) {
  *arr = malloc(vertex * sizeof(size_t));
  if (!*arr) {
    printf("malloc failed");
    free(matrix);
    free(visited);
    free(arr);
    free(parent);
    return 1;
  }
  return 0;
}

void deikstraAlgorithm(const size_t *matrix, size_t *distance, size_t *parent,
                       char *visited, const size_t vertex, const size_t start) {
  for (size_t i = 0; i < vertex; ++i) {
    visited[i] = 1;
    distance[i] = SIZE_T_MAX;
    parent[i] = -1;
  }
  distance[start] = 0;
  while (1) {
    size_t minIndex = SIZE_T_MAX;
    size_t min = SIZE_T_MAX;
    for (size_t i = 0; i < vertex; ++i) {
      if (visited[i] == 1 && distance[i] < min) {
        min = distance[i];
        minIndex = i;
      }
    }
    if (minIndex == SIZE_T_MAX)
      break;
    for (size_t i = 0; i < vertex; ++i) {
      if (matrix[minIndex * vertex + i] <= 0)
        continue;
      size_t tmp = min + matrix[minIndex * vertex + i];
      if (tmp < min || tmp < matrix[minIndex * vertex + i])
        tmp = SIZE_T_MAX;
      if (tmp < distance[i]) {
        distance[i] = tmp;
        parent[i] = minIndex;
      }
    }
    visited[minIndex] = 0;
  }
  free(visited);
}

void printDistance(const size_t *distance, const size_t start,
                   const size_t vertex) {
  for (size_t i = 0; i < vertex; ++i) {
    if (i == start)
      printf("0");
    else if (distance[i] == SIZE_T_MAX)
      printf("oo");
    else if (distance[i] > INT_MAX)
      printf("INT_MAX+");
    else
      printf("%zu", distance[i]);
    if (i < vertex - 1)
      printf(" ");
  }
  printf("\n");
}

void printPath(const size_t finish, const size_t *parent,
               const size_t *distance, const size_t vertex,
               const size_t start) {
  if (distance[finish] == SIZE_T_MAX) {
    printf("no path\n");
    return;
  }
  if (distance[finish] > INT_MAX) {
    printf("overflow\n");
    return;
  }
  size_t *path = malloc(vertex * sizeof(size_t));
  if (!path) {
    printf("malloc failed");
    free(path);
    return;
  }
  size_t path_len = 0;
  size_t current = finish;

  while (current != SIZE_T_MAX && current != start) {
    path[path_len++] = current;
    current = parent[current];
  }
  path[path_len++] = start;

  for (size_t i = 0; i < path_len; ++i) {
    printf("%zu", path[i] + 1);
    if (i < path_len - 1)
      printf(" ");
  }
  printf("\n");
  free(path);
}
