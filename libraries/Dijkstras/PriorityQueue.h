// PriorityQueue.h

#ifndef PriorityQueue_h
#define PriorityQueue_h

#include "Arduino.h"

typedef struct {
    int priority;
    int value;
} pqNode;

typedef struct {
    pqNode* nodes;
    int capacity;
    int size;
} priorityQueue;

void pq_init(priorityQueue* pq, int capacity);
void pq_push(priorityQueue* pq, int priority, int value);
int pq_top(priorityQueue* pq);
void pq_pop(priorityQueue* pq);
bool pq_empty(priorityQueue* pq);

#endif
