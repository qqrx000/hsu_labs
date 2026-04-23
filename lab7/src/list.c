#include "list.h"
#include <stdlib.h>

struct node {
  size_t vertex;
  node *next;
};

node *createNode(const size_t value) {
  node *newNode = malloc(sizeof(node));
  if (!newNode) {
    return NULL;
  }
  newNode->vertex = value;
  newNode->next = NULL;
  return newNode;
}

void pushFront(node **head, const size_t value) {
  node *newNode = createNode(value);
  if (!newNode) return;
  newNode->next = *head;
  *head = newNode;
}

//freeNodes()
