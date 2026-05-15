#ifndef OPERATORS_H
#define OPERATORS_H

#define LEN_OF_OPER 5

typedef struct operator operator;
typedef struct operatorTable operatorTable;
typedef enum { OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_INVALID } operationType;

operatorTable *createOperatorTable(void);
void destroyOperatorTable(operatorTable *table);
void initOperators(operatorTable *table, const char *symbols,
                   char (*types)[LEN_OF_OPER], const short *priorities,
                   short countOfOperators);
operator* findOperator(operatorTable * table, char c);
int getPriority(const operator* op);
operationType getType(const operator* op);

#endif
