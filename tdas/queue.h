#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>
typedef struct Queue Queue;

Queue* queue_create();
void queue_push(Queue* queue, void* data);
void* queue_pop(Queue* queue);
bool queue_is_empty(const Queue* queue);
void queue_destroy(Queue* queue);

#endif // QUEUE_H
