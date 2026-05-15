#include "operators.h"
#include "parcer.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

int read(short *cntOfOper, char **symbols, char (**types)[LEN_OF_OPER],
         short **priorities);

int readExpression(char *expr);

int main(void) {
  short countOfOperators;
  char *symbols;
  char (*types)[LEN_OF_OPER];
  short *priorities;

  if (read(&countOfOperators, &symbols, &types, &priorities) == 1) {
    return EXIT_SUCCESS;
  }
  operatorTable *table = createOperatorTable();
  if (!table) {
    goto End;
  }
  initOperators(table, symbols, types, priorities, countOfOperators);

  stack *s = createStack();
  if (!s) {
    destroyOperatorTable(table);
    goto End;
  }
  char expression[1001];
  if (readExpression(expression) == 1) {
    destroyStack(s);
    destroyOperatorTable(table);
    goto End;
  }
  token *postfix = createPostfix();
  if (!postfix) {
    printf("token error");
    destroyStack(s);
    destroyOperatorTable(table);
    goto End;
  }
  short size = 0;
  if (parcer(table, s, expression, postfix, &size) == 1) {
    printf("syntax error");
    destroyPostfix(postfix);
    destroyStack(s);
    destroyOperatorTable(table);
    goto End;
  }
  if (calculator(postfix, size) == 1) {
    destroyPostfix(postfix);
    destroyStack(s);
    destroyOperatorTable(table);
    goto End;
  }
  destroyPostfix(postfix);
  destroyStack(s);
  destroyOperatorTable(table);
End:
  free(symbols);
  free(types);
  free(priorities);
  return EXIT_SUCCESS;
}

int read(short *cntOfOper, char **symbols, char (**types)[LEN_OF_OPER],
         short **priorities) {
  if (scanf("%hd", cntOfOper) != 1 || *cntOfOper > 50 || *cntOfOper < 0) {
    printf("syntax error");
    return 1;
  }
  *symbols = malloc(*cntOfOper * sizeof(char));
  if (!*symbols) {
    printf("bad mem");
    return 1;
  }
  *priorities = malloc(*cntOfOper * sizeof(short));
  if (!*priorities) {
    printf("bad mem");
    free(*symbols);
    return 1;
  }
  *types = malloc(sizeof(**types) * *cntOfOper);
  if (!*types) {
    printf("bad mem");
    free(*symbols);
    free(*priorities);
    return 1;
  }
  for (short i = 0; i < *cntOfOper; ++i) {
    if (scanf(" %c %4s %hd", &(*symbols)[i], (*types)[i], &(*priorities)[i]) !=
        3) {
      printf("syntax error");
      free(*symbols);
      free(*types);
      free(*priorities);
      return 1;
    }
  }
  return 0;
}

int readExpression(char *expr) {
  if (scanf(" %1000[^\n]", expr) != 1) {
    printf("syntax error");
    return 1;
  }
  const int c = getchar();
  if (c != '\n' && c != EOF) {
    printf("syntax error");
    return 1;
  }
  return 0;
}
