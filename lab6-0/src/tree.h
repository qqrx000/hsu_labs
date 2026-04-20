#ifndef TREE_H
#define TREE_H

typedef struct tree tree;


tree *createNode(int value);
void freeTree(tree *tree);
char getHeight(const tree *node);
tree *insert(tree *node, int value, char logEnable);

#endif
