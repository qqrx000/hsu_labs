#include "tree.h"
#include <stdlib.h>

struct tree {
  int value;
  size_t height;
  tree *left;
  tree *right;
};

tree *createNode(const int value) {
  tree *newNode = malloc(sizeof(tree));
  if (!newNode) {
    // printf("tree malloc failed");
    return NULL;
  }
  newNode->height = 1;
  newNode->value = value;
  newNode->left = newNode->right = NULL;
  return newNode;
}

void freeTree(tree *tree) {
  if (tree == NULL)
    return;
  freeTree(tree->left);
  freeTree(tree->right);
  free(tree);
}

size_t getHeight(const tree *node) { return node ? node->height : 0; }

int balance(const tree *node) {
  return (int)(getHeight(node->right) - getHeight(node->left));
}

size_t max(const size_t left, const size_t right) {
  return (left > right ? left : right);
}

tree *smallRight(tree *node) {
  tree *leftChild = node->left;
  tree *subTreeChild = leftChild->right;
  leftChild->right = node;
  node->left = subTreeChild;
  node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
  leftChild->height =
      max(getHeight(leftChild->left), getHeight(leftChild->right)) + 1;
  return leftChild;
}

tree *smallLeft(tree *node) {
  tree *rightChild = node->right;
  tree *subTreeChild = rightChild->left;
  rightChild->left = node;
  node->right = subTreeChild;
  node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
  rightChild->height =
      max(getHeight(rightChild->left), getHeight(rightChild->right)) + 1;
  return rightChild;
}

tree *bigRight(tree *node) {
  node->right = smallRight(node->right);
  return smallLeft(node);
}

tree *bigLeft(tree *node) {
  node->left = smallLeft(node->left);
  return smallRight(node);
}

tree *insert(tree *node, const int value, int *log, const int logEnable,
             int *idx) {
  if (node == NULL) {
    tree *tmp = createNode(value);
    if (!tmp)
      return NULL;
    return tmp;
  }
  if (value < node->value) {
    node->left = insert(node->left, value, log, logEnable, idx);
  } else {
    node->right = insert(node->right, value, log, logEnable, idx);
  }
  // recalculate height
  node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

  // rotates
  const int bal = balance(node);
  if (bal <= -2) {
    if (balance(node->left) <= 0) {
      if (logEnable)
        log[(*idx)++] = SR;
      return smallRight(node);
    }
    if (logEnable)
      log[(*idx)++] = BL;
    return bigLeft(node);
  }
  if (bal >= 2) {
    if (balance(node->right) >= 0) {
      if (logEnable)
        log[(*idx)++] = SL;
      return smallLeft(node);
    }
    if (logEnable)
      log[(*idx)++] = BR;
    return bigRight(node);
  }
  return node;
}
