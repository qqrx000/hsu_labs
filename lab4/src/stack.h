#ifndef STACK_H
#define STACK_H

struct operator;
struct stack;

struct stack *createStack(void);
void destroyStack(struct stack *s);
void stackPush(struct stack *s, struct operator* op);
struct operator* stackPop(struct stack *s);
struct operator* stackTop(const struct stack *s);
int stackIsEmpty(const struct stack *s);

#endif
