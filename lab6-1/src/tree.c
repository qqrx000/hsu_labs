#include "tree.h"
#include <stdlib.h>

#define RED 0
#define BLACK 1
#define EMPTY_IDX (-1)

typedef struct node {
  int value;
  int left;
  int right;
  int parent;
  char color;
} node;

struct rbtree {
  node *mem;
  int root;
  int size;
};

rbtree *newTree(const int maxNodes) {
  rbtree *t = malloc(sizeof(rbtree));
  if (!t)
    return NULL;
  t->mem = malloc((size_t)maxNodes * sizeof(node));
  if (!t->mem) {
    free(t);
    return NULL;
  }
  t->size = 0;
  t->root = EMPTY_IDX;
  return t;
}

static node *gNode(const rbtree *t, const int idx) { return &t->mem[idx]; }

static int getColor(const rbtree *t, const int idx) {
  return idx == EMPTY_IDX ? BLACK : gNode(t, idx)->color;
}

static int makeNode(rbtree *t, const int value) {
  const int idx = t->size++;
  node *n = gNode(t, idx);
  n->right = EMPTY_IDX;
  n->left = EMPTY_IDX;
  n->parent = EMPTY_IDX;
  n->value = value;
  n->color = RED;
  return idx;
}

static void rotR(rbtree *t, const int x) {
  const int y = gNode(t, x)->left;
  gNode(t, x)->left = gNode(t, y)->right;
  if (gNode(t, y)->right != EMPTY_IDX)
    gNode(t, gNode(t, y)->right)->parent = x;
  gNode(t, y)->parent = gNode(t, x)->parent;
  const int px = gNode(t, x)->parent;
  if (px == EMPTY_IDX)
    t->root = y;
  else if (gNode(t, px)->right == x)
    gNode(t, px)->right = y;
  else
    gNode(t, px)->left = y;
  gNode(t, y)->right = x;
  gNode(t, x)->parent = y;
}

static void rotL(rbtree *t, const int x) {
  const int y = gNode(t, x)->right;
  gNode(t, x)->right = gNode(t, y)->left;
  if (gNode(t, y)->left != EMPTY_IDX)
    gNode(t, gNode(t, y)->left)->parent = x;
  gNode(t, y)->parent = gNode(t, x)->parent;
  const int px = gNode(t, x)->parent;
  if (px == EMPTY_IDX)
    t->root = y;
  else if (gNode(t, px)->left == x)
    gNode(t, px)->left = y;
  else
    gNode(t, px)->right = y;
  gNode(t, y)->left = x;
  gNode(t, x)->parent = y;
}

static void fixInsert(rbtree *t, int z) {
  while (getColor(t, gNode(t, z)->parent) == RED) {
    int p = gNode(t, z)->parent;
    int pp = gNode(t, p)->parent;
    if (p == gNode(t, pp)->left) {
      const int y = gNode(t, pp)->right;
      if (getColor(t, y) == RED) {
        gNode(t, y)->color = BLACK;
        gNode(t, pp)->color = RED;
        gNode(t, p)->color = BLACK;
        z = pp;
      } else {
        if (z == gNode(t, p)->right) {
          z = p;
          rotL(t, z);
          p = gNode(t, z)->parent;
          pp = gNode(t, p)->parent;
        }
        gNode(t, p)->color = BLACK;
        gNode(t, pp)->color = RED;
        rotR(t, pp);
      }
    } else {
      const int y = gNode(t, pp)->left;
      if (getColor(t, y) == RED) {
        gNode(t, y)->color = BLACK;
        gNode(t, pp)->color = RED;
        gNode(t, p)->color = BLACK;
        z = pp;
      } else {
        if (z == gNode(t, p)->left) {
          z = p;
          rotR(t, z);
          p = gNode(t, z)->parent;
          pp = gNode(t, p)->parent;
        }
        gNode(t, pp)->color = RED;
        gNode(t, p)->color = BLACK;
        rotL(t, pp);
      }
    }
  }
  gNode(t, t->root)->color = BLACK;
}

void insert(rbtree *t, const int value) {
  const int z = makeNode(t, value);
  int x = t->root;
  int y = EMPTY_IDX;
  while (x != EMPTY_IDX) {
    y = x;
    if (value < gNode(t, x)->value)
      x = gNode(t, x)->left;
    else if (value > gNode(t, x)->value)
      x = gNode(t, x)->right;
    else {
      t->size--;
      return;
    }
  }
  gNode(t, z)->parent = y;
  if (y == EMPTY_IDX)
    t->root = z;
  else if (value < gNode(t, y)->value)
    gNode(t, y)->left = z;
  else
    gNode(t, y)->right = z;
  fixInsert(t, z);
}

int getBlackHeight(const rbtree *t) {
  if (!t || t->root == EMPTY_IDX)
    return 0;
  int x = t->root;
  int h = 1;
  while (x != EMPTY_IDX) {
    if (gNode(t, x)->color == BLACK)
      h++;
    x = gNode(t, x)->left;
  }
  return h;
}

void freeTree(rbtree *t) {
  if (!t)
    return;
  free(t->mem);
  free(t);
}
