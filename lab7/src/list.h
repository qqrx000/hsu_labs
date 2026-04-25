#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct node node;

node *createNode(size_t value);
void pushFront(node **head, size_t value);
void freeNodes(node *l);

size_t getVertex(const node *n);
node *getNext(const node *n);

#endif
