#ifndef TREE_H
#define TREE_H

typedef struct rbtree rbtree;

rbtree *newTree(int maxNodes);
void freeTree(rbtree *t);
void insert(rbtree *t, int value);
int getBlackHeight(const rbtree *t);

#endif
