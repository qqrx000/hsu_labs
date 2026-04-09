#include <stdio.h>
#include <stdlib.h>

#define SIZE_T_MAX ULONG_MAX

int read(size_t *vertex, size_t *edge, size_t *start, size_t *finish,
         size_t ***matrix);

int main(void) {
  size_t vertex, edge, start, finish;
  size_t **matrix = NULL;

  if (read(&vertex, &edge, &start, &finish, &matrix) == 1)
    return EXIT_SUCCESS;

  //--------------------------------------algorithm----------------------------------------




  //----------------------------------end------------------------------------------
  for (size_t i = 0; i <= vertex; i++) free(matrix[i]);
  free(matrix);
  return EXIT_SUCCESS;
}


int read(size_t *vertex, size_t *edge, size_t *start, size_t *finish,
         size_t ***matrix) {
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

  *matrix = malloc(*vertex * sizeof(size_t *));
  if (!*matrix) {
    printf("malloc failed");
    return 1;
  }

  for (size_t i = 0; i <= *vertex; i++) {
    (*matrix)[i] = calloc(*vertex, sizeof(size_t));
    if (!(*matrix)[i]) {
      for (size_t j = 0; j < i; j++)
        free((*matrix)[j]);
      free(*matrix);
      return 1;
    }
  }

  for (size_t i = 0; i < *edge; ++i) {
    size_t from, to, len;
    if (scanf("%zu %zu %zu", &from, &to, &len) != 3) {
      printf("bad number of lines");
      return 1;
    }
    if (from > *vertex || to > *vertex) {
      printf("bad vertex");
      return 1;
    }
    if (len > INT_MAX) {
      printf("bad length");
      return 1;
    }
    *matrix[from][to] = len;
  }
  return 0;
}