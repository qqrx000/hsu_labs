#include "kan.h"
#include "list.h"
#include <stdlib.h>

struct queue {
  size_t *data;
  size_t head;
  size_t tail;
};

static queue *initQueue(const size_t maxSize) {
  queue *q = malloc(sizeof(struct queue));
  if (!q)
    return NULL;

  q->data = malloc(sizeof(size_t) * maxSize);
  if (!q->data) {
    free(q);
    return NULL;
  }

  q->head = 0;
  q->tail = 0;
  return q;
}

static void push(queue *q, const size_t value) { q->data[q->tail++] = value; }

static size_t pop(queue *q) { return q->data[q->head++]; }

static int isEmpty(const queue *q) { return q->head == q->tail; }

int topoSort(const size_t vertex, node **adjList, size_t *inDegree,
             size_t *result) {

  queue *q = initQueue(vertex);
  if (!q)
    return 1;

  for (size_t i = 1; i <= vertex; i++) {
    if (inDegree[i] == 0) {
      push(q, i);
    }
  }

  size_t count = 0;

  while (!isEmpty(q)) {
    const size_t u = pop(q);
    result[count++] = u;

    const node *cur = adjList[u];
    while (cur) {
      const size_t v = getVertex(cur);
      inDegree[v]--;

      if (inDegree[v] == 0) {
        push(q, v);
      }

      cur = getNext(cur);
    }
  }

  free(q->data);
  free(q);

  return count != vertex;
}
