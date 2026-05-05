#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

struct queue {
  short *data;
  int head;
  int tail;
  int capacity;
};

queue* createQueue(const int capacity) {
  if (capacity <= 0) return NULL;
  queue *q = malloc(sizeof(queue));
  if (!q) {
    printf("bad memory");
    return NULL;
  }
    
  q->data = (short*)malloc(capacity * sizeof(short));
  if (!q->data) {
    printf("bad memory");
    free(q);
    return NULL;
  }
  q->head = 0;
  q->tail = 0;
  q->capacity = capacity;
  return q;
}

void freeQueue(queue *q) {
  if (q) {
    free(q->data);
    free(q);
  }
}

void push(queue *q, const short value) {
  if (q && q->data && q->tail < q->capacity) {
    q->data[q->tail++] = value;
  }
}

short pop(queue *q) {
  if (q && q->data && q->head < q->tail) {
    return q->data[q->head++];
  }
  return -1;
}

int isEmpty(const queue *q) {
  return !q || !q->data || q->head >= q->tail;
}
