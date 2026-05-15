#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

#define LEN_OF_EXPRESSION 1000

typedef struct operator operator;
typedef struct stack stack;

struct stack {
  operator *value[LEN_OF_EXPRESSION];
  int top;
};

stack *createStack(void) {
  stack *s = malloc(sizeof(stack));
  if (!s) {
    printf("stack error");
    return NULL;
  }
  s->top = -1;
  return s;
}

void destroyStack(stack *s) {
  if (!s) {
    return;
  }
  free(s);
}

void stackPush(stack *s, operator *op) {
  if (!s || s->top >= LEN_OF_EXPRESSION - 1) {
    return;
  }
  s->top++;
  s->value[s->top] = op;
}

operator *stackPop(stack *s) {
  if (!s || s->top < 0) {
    return NULL;
  }
  return s->value[s->top--];
}

operator *stackTop(const stack *s) {
  if (!s || s->top < 0) {
    return NULL;
  }
  return s->value[s->top];
}

int stackIsEmpty(const stack *s) {
  if (!s || s->top < 0) {
    return 1;
  }
  return 0;
}
