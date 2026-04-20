#ifndef TREE_H
#define TREE_H

typedef struct tree {
  int value;
  char height;
  struct tree *left;
  struct tree *right;
}tree;

char getHeight(const tree *node);
tree *insert(tree *node, int value, char logEnable, tree *mem, int *memIdx);

#endif
