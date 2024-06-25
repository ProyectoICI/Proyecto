#ifndef PARADEROS_H
#define PARADEROS_H

#include "tdas/map.h"

typedef struct Horario {
    char numeroBus[50];
    char tiempoLlegada[6];
} Horario;

typedef struct Paradero {
    char nombreParadero[100];
    int numeroParadero;
    Horario* horariosParadero;
    int cantHorarios;
    struct Edge** edges;  
    int numEdges;  
} Paradero;

typedef struct Edge {
    Paradero* startNode;
    Paradero* endNode;
    int distancia;
} Edge;

typedef struct Graph {
    Paradero** nodes; 
    int numNodes;  
} Graph;

void agregarParadero(Map *mapParaderos);

#endif // PARADEROS_H
