#include "queue.h"
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    void* data;
    struct Node* next;
};

struct Queue {
    struct Node* front;
    struct Node* rear;
};

Queue* queue_create() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void queue_push(Queue* queue, void* data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = node;
        return;
    }
    queue->rear->next = node;
    queue->rear = node;
}

void* queue_pop(Queue* queue) {
    if (queue->front == NULL) return NULL;
    struct Node* node = queue->front;
    void* data = node->data;
    queue->front = node->next;
    if (queue->front == NULL) queue->rear = NULL;
    free(node);
    return data;
}

bool queue_is_empty(const Queue* queue) {
    return queue->front == NULL;
}

void queue_destroy(Queue* queue) {
    struct Node* node = queue->front;
    while (node != NULL) {
        struct Node* next = node->next;
        free(node);
        node = next;
    }
    free(queue);
}
