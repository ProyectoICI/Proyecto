#ifndef PQUEUE_H
#define PQUEUE_H

typedef struct PriorityQueue PriorityQueue;
typedef struct Paradero Paradero;

void pqInsert(PriorityQueue* pq, Paradero* paradero, int priority);
void pqDecreaseKey(PriorityQueue* pq, Paradero* paradero, int newPriority);
void pqInit(PriorityQueue* pq, int capacity);
void pqFree(PriorityQueue* pq);
Paradero* pqExtractMin(PriorityQueue* pq);

#endif