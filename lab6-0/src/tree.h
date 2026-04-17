#ifndef TREE_H
#define TREE_H
#include <stddef.h>

typedef struct tree tree;


tree *createNode(int value);
void freeTree(tree *tree);
size_t getHeight(const tree *node);
enum {SL, SR, BL, BR};
tree *insert(tree *node, int value, int *log, int logEnable, int *idx);

#endif
