#include <stdio.h>
#include <stdlib.h>

//-------------------------------------------------------------------------------------

typedef struct Paradero Paradero; 
typedef struct Edge Edge;         

typedef struct Horario { 
    char numeroBus[50]; 
    char tiempoLlegada[6]; 
} Horario;

typedef struct Paradero { 
    char nombreParadero[100]; 
    int numeroParadero; 
    Horario** horariosParadero;
    Edge** edges; 
    int numEdges; 
    int numHorarios; 
} Paradero;

struct Edge { 
    Paradero* startNode; 
    Paradero* endNode; 
    int distancia; 
};

typedef struct PriorityQueueNode {
    Paradero* paradero;
    int priority; 
} PriorityQueueNode;

typedef struct PriorityQueue {
    PriorityQueueNode* nodes; 
    int size; 
    int capacity; 
} PriorityQueue;

//-------------------------------------------------------------------------------------


void pqInsert(PriorityQueue* pq, Paradero* paradero, int priority) {
  printf("pqInsert\n");
}

void pqDecreaseKey(PriorityQueue* pq, Paradero* paradero, int newPriority) {
  printf("pqInsert\n");
}

void pqInit(PriorityQueue* pq, int capacity) {
  printf("pqInsert\n");
}

void pqFree(PriorityQueue* pq) {
  printf("pqInsert\n");
}

Paradero* pqExtractMin(PriorityQueue* pq) {
  return NULL;
}

//-------------------------------------------------------------------------------------
