#ifndef PARCER_H
#define PARCER_H

typedef struct stack stack;
typedef struct token token;
struct operatorTable;

token *createPostfix(void);
void destroyPostfix(token *p);
int parcer(struct operatorTable *t, stack *s, const char *expr, token *postfix,
           short *size);
int calculator(const token *postfix, short size);

#endif
