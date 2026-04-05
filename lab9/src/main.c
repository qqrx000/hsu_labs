#include <stdio.h>п
#include <stdlib.h>


#define SIZE_T_MAX ULONG_MAX

int read(size_t *vertex, size_t *edge, size_t *start, size_t *finish);

int main(void) {

//-------------------------------read-----------------------------------------------------
  size_t vertex, edge, start, finish;
  if (read(&vertex, &edge, &start, &finish) == 1)
    return EXIT_SUCCESS;

  //--------------------------------------algorithm----------------------------------------

  //----------------------------------end------------------------------------------

  return EXIT_SUCCESS;
}

//----------------------------------read-----------------------------------------
int read(size_t *vertex, size_t *edge, size_t *start, size_t *finish) {
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
  return 0;
}