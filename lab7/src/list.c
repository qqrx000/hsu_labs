#include "list.h"
#include <stdlib.h>

struct node {
  size_t vertex;
  node *next;
};

node *createNode(const size_t value) {
  node *n = malloc(sizeof(node));
  if (!n)
    return NULL;

  n->vertex = value;
  n->next = NULL;
  return n;
}

void pushFront(node **head, const size_t value) {
  node *n = createNode(value);
  if (!n)
    return;

  n->next = *head;
  *head = n;
}

void freeNodes(node *l) {
  while (l) {
    node *tmp = l;
    l = l->next;
    free(tmp);
  }
}

size_t getVertex(const node *n) { return n->vertex; }

node *getNext(const node *n) { return n->next; }
