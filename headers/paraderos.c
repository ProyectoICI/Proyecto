#include <stdio.h>
#include <stdlib.h>
// Include extra.h header
#include "../tdas/extra.h"

typedef struct Paradero Paradero; // Forward declaration of Paradero
typedef struct Edge Edge;         // Forward declaration of Edge

typedef struct Horario {
  char numeroBus[50];
  char tiempoLlegada[6];
} Horario;

typedef struct Paradero {
  char nombreParadero[100];
  int numeroParadero;
  Horario **horariosParadero;
  Edge **edges;
  int numEdges;
  int numHorarios;
} Paradero;

struct Edge {
  Paradero *startNode;
  Paradero *endNode;
  int distancia;
};

typedef struct Graph {
  Paradero **nodes;
  int numNodes;
} Graph;

void agregarParadero(Graph *graph) {
  Paradero *paradero = (Paradero *)malloc(sizeof(Paradero));
  printf("Ingrese el nombre del paradero: ");
  scanf("%s", paradero->nombreParadero);
  printf("Ingrese el número del paradero: ");
  scanf("%d", &paradero->numeroParadero);

  paradero->horariosParadero = NULL;
  paradero->edges = NULL;
  paradero->numEdges = 0;

  graph->nodes[graph->numNodes++] = paradero;

  printf("Paradero agregado con éxito.\n");
}

void editarParadero(Graph *graph) {
  int currentNumber;
  printf("Ingrese el número del paradero que desea editar: ");
  scanf("%d", &currentNumber);

  for (int i = 0; i < graph->numNodes; i++) {
    if (graph->nodes[i]->numeroParadero == currentNumber) {
      printf("Ingrese el nuevo nombre del paradero: ");
      scanf("%s", graph->nodes[i]->nombreParadero);
      printf("Ingrese el nuevo número del paradero: ");
      scanf("%d", &graph->nodes[i]->numeroParadero);
      printf("Paradero actualizado con éxito.\n");
      return;
    }
  }
  printf("Paradero no encontrado.\n");
  presioneTeclaParaContinuar();
}

void listaDeParaderos(Graph *graph) {
  if (graph->numNodes == 0) {
    printf("No hay paraderos para mostrar.\n");
    return;
  }

  printf("Listado de Paraderos:\n");
  for (int i = 0; i < graph->numNodes; i++) {
    printf("Nombre: %s, Número: %d\n", graph->nodes[i]->nombreParadero,
           graph->nodes[i]->numeroParadero);
  }
  presioneTeclaParaContinuar();
}