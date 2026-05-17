#ifndef TREE_H
#define TREE_H

typedef struct tree tree;

tree *newTree(int maxNodes);
void freeTree(tree *root);
tree *insert(tree *root, int value);
int getBlackHeight(const tree *root);

#endif
