#include "operators.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_OPERATORS 50

struct operator {
  char symbol;
  operationType type;
  int priority;
};

struct operatorTable {
  operator ops[50];
  int count;
};

static operationType mapType(const char *t) {
  switch (t[0]) {
  case 'A':
    return OP_ADD;
  case 'S':
    return OP_SUB;
  case 'M':
    return OP_MUL;
  case 'D':
    return OP_DIV;
  default:
    return OP_INVALID;
  }
}

operatorTable *createOperatorTable(void) {
  operatorTable *table = malloc(sizeof(operatorTable));
  if (!table) {
    printf("table error");
    return NULL;
  }
  table->count = 0;
  return table;
}

void destroyOperatorTable(operatorTable *table) {
  if (!table) {
    return;
  }
  free(table);
}

void initOperators(operatorTable *table, const char *symbols,
                   char (*types)[LEN_OF_OPER], const short *priorities,
                   const short countOfOperators) {
  table->count = 0;

  for (short i = 0; i < countOfOperators; i++) {
    table->ops[i].symbol = symbols[i];
    table->ops[i].type = mapType(types[i]);
    table->ops[i].priority = priorities[i];
  }
  table->count = countOfOperators;
}

operator *findOperator(operatorTable *table, const char c) {
  for (int i = 0; i < table->count; i++) {
    if (table->ops[i].symbol == c) {
      return &table->ops[i];
    }
  }
  return NULL;
}

int getPriority(const operator *op) {
  if (!op) {
    return -1;
  }
  return op->priority;
}

operationType getType(const operator *op) {
  if (!op) {
    return -1;
  }
  return op->type;
}
