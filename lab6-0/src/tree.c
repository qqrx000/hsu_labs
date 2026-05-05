#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

tree *createNode(tree *mem, int *idx, const int value) {
  tree *node = &mem[(*idx)++];
  node->value = value;
  node->height = 1;
  node->left = node->right = NULL;
  return node;
}

char getHeight(const tree *node) { return node ? node->height : 0; }

static int balance(const tree *node) {
  if (node == NULL) {
    return 0;
  }
  return getHeight(node->left) - getHeight(node->right);
}

static char max(const char left, const char right) {
  return left > right ? left : right;
}

static tree *smallRight(tree *node) {
  tree *leftChild = node->left;
  tree *subTreeChild = leftChild->right;
  leftChild->right = node;
  node->left = subTreeChild;
  node->height = (char)(max(getHeight(node->left), getHeight(node->right)) + 1);
  leftChild->height =
      (char)(max(getHeight(leftChild->left), getHeight(leftChild->right)) + 1);
  return leftChild;
}

static tree *smallLeft(tree *node) {
  tree *rightChild = node->right;
  tree *subTreeChild = rightChild->left;
  rightChild->left = node;
  node->right = subTreeChild;
  node->height = (char)(max(getHeight(node->left), getHeight(node->right)) + 1);
  rightChild->height =
      (char)(max(getHeight(rightChild->left), getHeight(rightChild->right)) +
             1);
  return rightChild;
}

static tree *bigRight(tree *node) {
  node->left = smallLeft(node->left);
  return smallRight(node);
}

static tree *bigLeft(tree *node) {
  node->right = smallRight(node->right);
  return smallLeft(node);
}

static tree *rotates(tree *node, const char logEnable) {
  if (!node)
    return NULL;
  const int bal = balance(node);
  if (bal < -1) {
    if (balance(node->right) <= 0) {
      if (logEnable)
        printf("SL ");
      return smallLeft(node);
    }
    if (logEnable)
      printf("BL ");
    return bigLeft(node);
  }
  if (bal > 1) {
    if (balance(node->left) >= 0) {
      if (logEnable)
        printf("SR ");
      return smallRight(node);
    }
    if (logEnable)
      printf("BR ");
    return bigRight(node);
  }
  return node;
}

tree *insert(tree *node, const int value, const char logEnable, tree *mem,
             int *memIdx) {
  if (node == NULL) {
    return createNode(mem, memIdx, value);
  }
  if (value < node->value) {
    node->left = insert(node->left, value, logEnable, mem, memIdx);
  } else if (value > node->value) {
    node->right = insert(node->right, value, logEnable, mem, memIdx);
  } else
    return node;
  // recalculate height
  node->height = (char)(max(getHeight(node->left), getHeight(node->right)) + 1);

  return rotates(node, logEnable);
}
