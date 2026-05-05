#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue queue;

queue* createQueue(int capacity);
void freeQueue(queue *q);
void push(queue *q, short value);
short pop(queue *q);
int isEmpty(const queue *q);

#endif
