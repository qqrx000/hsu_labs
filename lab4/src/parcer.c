#include "parcer.h"
#include "operators.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

#define LEN_OF_EXPRESSION 1000
#define LBRACKET NULL // mark for left bracket in stack

typedef enum { TOKEN_NUMBER, TOKEN_OPERATOR, TOKEN_EMPTY } tokenType;

typedef enum { BR_L, BR_R } brackets;

typedef enum { EXPECT_OPERAND, EXPECT_OPERATOR } expectation;

struct token {
  tokenType type;
  int value;
  operationType operation;
};

token *createPostfix(void) {
  token *postfix = malloc(sizeof(token) * LEN_OF_EXPRESSION);
  if (!postfix) {
    return NULL;
  }

  for (int i = 0; i < LEN_OF_EXPRESSION; i++) {
    postfix[i].type = TOKEN_EMPTY;
    postfix[i].value = 0;
    postfix[i].operation = OP_INVALID;
  }
  return postfix;
}

void destroyPostfix(token *p) {
  if (!p) {
    return;
  }
  free(p);
}

int parcer(operatorTable *t, stack *s, const char *expr, token *postfix,
           short *size) {
  expectation state = EXPECT_OPERAND;
  *size = 0;

  for (size_t i = 0; expr[i] != '\0'; ++i) {
    if (expr[i] == ' ')
      continue;
    // numbers
    if (expr[i] >= '0' && expr[i] <= '9') {
      if (state != EXPECT_OPERAND) {
        return 1;
      }
      int value = 0;
      size_t j = i;
      while (expr[j] >= '0' && expr[j] <= '9') {
        value = value * 10 + (expr[j] - '0');
        j++;
      }
      postfix[*size].type = TOKEN_NUMBER;
      postfix[*size].value = value;
      (*size)++;

      state = EXPECT_OPERATOR;
      i = j - 1;
      continue;
    }
    // brackets
    if (expr[i] == '(') {
      if (state != EXPECT_OPERAND) {
        return 1;
      }
      stackPush(s, LBRACKET);
      continue;
    }
    if (expr[i] == ')') {
      if (state != EXPECT_OPERATOR) {
        return 1;
      }
      while (!stackIsEmpty(s) && stackTop(s) != LBRACKET) {
        const operator *op = stackPop(s);
        postfix[*size].type = TOKEN_OPERATOR;
        postfix[*size].operation = getType(op);
        (*size)++;
      }
      if (stackIsEmpty(s)) {
        return 1;
      }
      stackPop(s);
      continue;
    }
    // operators
    operator *op = findOperator(t, expr[i]);
    if (op != NULL) {
      if (state != EXPECT_OPERATOR) {
        return 1;
      }
      while (!stackIsEmpty(s) && stackTop(s) != LBRACKET &&
             getPriority(stackTop(s)) >= getPriority(op)) {
        const operator *top = stackPop(s);
        postfix[*size].type = TOKEN_OPERATOR;
        postfix[*size].operation = getType(top);
        (*size)++;
      }
      stackPush(s, op);
      state = EXPECT_OPERAND;
      continue;
    }
    return 1;
  }
  if (state == EXPECT_OPERAND) {
    return 1;
  }
  while (!stackIsEmpty(s)) {
    const operator *op = stackPop(s);
    if (op == LBRACKET)
      return 1;
    postfix[*size].type = TOKEN_OPERATOR;
    postfix[*size].operation = getType(op);
    (*size)++;
  }
  return 0;
}

int calculator(const token *postfix, const short size) {
  int values[LEN_OF_EXPRESSION];
  int top = -1;

  for (short i = 0; i < size; ++i) {
    if (postfix[i].type == TOKEN_NUMBER) {
      values[++top] = postfix[i].value;
      continue;
    }
    if (postfix[i].type == TOKEN_OPERATOR) {
      if (top < 1) {
        printf("syntax error\n");
        return 1;
      }
      const int right = values[top--];
      const int left = values[top--];
      int result = 0;

      switch (postfix[i].operation) {
      case OP_ADD:
        result = left + right;
        break;

      case OP_SUB:
        result = left - right;
        break;

      case OP_MUL:
        result = left * right;
        break;

      case OP_DIV:
        if (right == 0) {
          printf("division by zero\n");
          return 1;
        }
        result = left / right;
        break;

      default:
        printf("syntax error\n");
        return 1;
      }
      values[++top] = result;
    }
  }
  if (top != 0) {
    printf("syntax error\n");
    return 1;
  }
  printf("%d\n", values[top]);
  return 0;
}
