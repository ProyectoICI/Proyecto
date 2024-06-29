#include <stdio.h>
#include <stdlib.h>
#include "../tdas/extra.h"

typedef struct Paradero Paradero; // Forward declaration of Paradero
typedef struct Edge Edge;         // Forward declaration of Edge

typedef struct Horario { // Horario de un bus
  char numeroBus[50]; // Número de bus
  char tiempoLlegada[6]; // Hora de llegada
} Horario;

typedef struct Paradero { // Paradero de un bus
    char nombreParadero[100]; // Nombre del paradero
    int numeroParadero; // Número del paradero
    Horario** horariosParadero; // Horarios de parada
    Edge** edges; // Edges de un paradero
    int numEdges; // Número de edges 
    int numHorarios; // Número de horarios
} Paradero;

struct Edge { // Edge de un bus
    Paradero* startNode; // Nodo de inicio
    Paradero* endNode; // Nodo de fin
    int distancia; // Distancia entre los nodos
};

typedef struct Graph { // Graph de un bus
    Paradero** nodes; // Nodos del graph
    int numNodes; // Número de nodos
} Graph;

typedef struct Ruta { // Ruta de un usuario
    int busRuta; // Número de bus
    Paradero** paraderos; // Paraderos de la ruta
    int numParaderos; // Número de paraderos
} Ruta;

void consultaHorarioParada(Graph* graph) {
    int numParada;
    printf("Ingrese el número de parada: ");
    scanf("%d", &numParada); // Corrected to remove '\n'

    // Iterate through the graph's nodes to find the matching Paradero
    for (int i = 0; i < graph->numNodes; i++) {
        if (graph->nodes[i]->numeroParadero == numParada) {
            // Found the matching Paradero
            Paradero* paradero = graph->nodes[i];
            printf("Horarios para la parada %d - %s:\n", numParada, paradero->nombreParadero);
            for (int j = 0; j < paradero->numHorarios; j++) {
                printf("Bus: %s, Llegada: %s\n", paradero->horariosParadero[j]->numeroBus, paradero->horariosParadero[j]->tiempoLlegada);
            }
            presioneTeclaParaContinuar();
            return; // Exit the function after printing the horarios
        }
    }
    presioneTeclaParaContinuar();
    printf("Paradero con número %d no encontrado.\n", numParada);
}

void consultaHorarioRuta(Ruta** rutas, int numRutas) {
    int busDeRuta;
    printf("Ingrese el número de la ruta (bus): \n");
    scanf("%d", &busDeRuta); 


    for (int i = 0; i < numRutas; i++) {
        if (rutas[i]->busRuta == busDeRuta) {
            printf("Horarios para la ruta del bus %d:\n", busDeRuta);
            for (int j = 0; j < rutas[i]->numParaderos; j++) {
                Paradero* paraderoActual = rutas[i]->paraderos[j];
                printf("Paradero %d - %s:\n", paraderoActual->numeroParadero, paraderoActual->nombreParadero);
                for (int k = 0; k < paraderoActual->numHorarios; k++) {
                    Horario* horarioActual = paraderoActual->horariosParadero[k];
                    if (atoi(horarioActual->numeroBus) == busDeRuta) {
                        printf("\tBus: %s, Llegada: %s\n", horarioActual->numeroBus, horarioActual->tiempoLlegada);
                    }
                }
            }
            presioneTeclaParaContinuar();
            return; // Found the route and printed the schedule, exit the function
        }
    }
    presioneTeclaParaContinuar();
    printf("No se encontró la ruta para el bus %d.\n", busDeRuta);
}