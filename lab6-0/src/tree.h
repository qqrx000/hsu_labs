#ifndef TREE_H
#define TREE_H

typedef struct tree tree;


tree *createNode(int value);
void freeTree(tree *tree);
int getHeight(const tree *node);
enum {SL, SR, BL, BR};
tree *insert(tree *node, int value, int logEnable, int *idx);

#endif
