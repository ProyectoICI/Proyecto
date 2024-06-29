#include "../tdas/extra.h"
#include "menus.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Paradero Paradero;  // Forward declaration of Paradero
typedef struct Edge Edge;  // Forward declaration of Edge

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

typedef struct Graph {
    Paradero** nodes; 
    int numNodes;  
} Graph;

typedef struct Ruta {
    int busRuta;
    Paradero** paraderos;
    int numParaderos;
} Ruta;

/*
-- FUNCIONES AUXILIARES PARA ACTUALIZAR LO EDITADO
   DE LAS RUTAS --
*/

void updateDistance(Graph *graph, int startNumber, int endNumber, int newDistance) {
    for (int i = 0; i < graph->numNodes; i++) {
        if (graph->nodes[i]->numeroParadero == startNumber) {
            for (int j = 0; j < graph->nodes[i]->numEdges; j++) {
                if (graph->nodes[i]->edges[j]->endNode->numeroParadero == endNumber) {
                    graph->nodes[i]->edges[j]->distancia = newDistance;
                    return;
                }
            }
        }
    }
}

void updateSchedule(Graph *graph, int startNumber, char *newSchedule) {
    for (int i = 0; i < graph->numNodes; i++) {
        if (graph->nodes[i]->numeroParadero == startNumber) {
            for (int j = 0; j < graph->nodes[i]->numHorarios; j++) {
                strcpy((*graph->nodes[i]->horariosParadero[j]).tiempoLlegada, newSchedule);
                return;
            }
        }
    }
}

void agregarRutaBus(Graph *graph, Ruta **rutas, int *numRutas) {
  int busNumber, startNumber, endNumber, distancia, numTrayectos;
  char tiempoLlegada[6]; // HH:MM format
  char tiempoPartida[6]; // HH:MM format
  printf("Ingrese el bús que realizará la ruta: ");
  scanf("%d", &busNumber);
  printf("Ingrese la cantidad de trayectos en la ruta: ");
  scanf("%d", &numTrayectos);

  Ruta *newRuta = (Ruta *)malloc(sizeof(Ruta));
  newRuta->busRuta = busNumber;
  newRuta->paraderos = (Paradero **)malloc((numTrayectos + 1) * sizeof(Paradero *));
  newRuta->numParaderos = 0;

  for (int i = 0; i < numTrayectos; i++) {

      Paradero *startParadero = NULL;
      Paradero *endParadero = NULL;

      printf("Ingrese el número del paradero de inicio: ");
      scanf("%d", &startNumber);

      for (int i = 0; i < graph->numNodes; i++) {
          if (graph->nodes[i]->numeroParadero == startNumber) {
              startParadero = graph->nodes[i];
          } 
      }

      if (startParadero == NULL) {
          printf("El paradero de inicio no se encontró.\n");
          return;
      }

      printf("Ingrese el número del paradero de destino: ");
      scanf("%d", &endNumber);

      for (int i = 0; i < graph->numNodes; i++) {
          if (graph->nodes[i]->numeroParadero == endNumber) {
              endParadero = graph->nodes[i];
          } 
      }

      if (endParadero == NULL) {
          printf("El paradero de destino no se encontró.\n");
          return;
      }


      printf("Ingrese la distancia entre los paraderos (en metros): ");
      scanf("%d", &distancia);

      printf("Ingrese el tiempo de partida al paradero de inicio (HH:MM): ");
      scanf("%s", tiempoPartida);
      printf("Ingrese el tiempo de llegada al paradero de destino (HH:MM): ");
      scanf("%s", tiempoLlegada);

      // Crear la arista (Edge) de inicio a destino
      Edge *newEdgeStartToEnd = (Edge *)malloc(sizeof(Edge));
      newEdgeStartToEnd->startNode = startParadero;
      newEdgeStartToEnd->endNode = endParadero;
      newEdgeStartToEnd->distancia = distancia;

      // Agregar la arista al paradero de inicio
      startParadero->edges = (Edge **)realloc(startParadero->edges, (startParadero->numEdges + 1) * sizeof(Edge *));
      startParadero->edges[startParadero->numEdges] = newEdgeStartToEnd;
      startParadero->numEdges++;

      // Crear la arista (Edge) de destino a inicio para bidireccionalidad
      Edge *newEdgeEndToStart = (Edge *)malloc(sizeof(Edge));
      newEdgeEndToStart->startNode = endParadero;
      newEdgeEndToStart->endNode = startParadero;
      newEdgeEndToStart->distancia = distancia;

      // Agregar la arista al paradero de destino
      endParadero->edges = (Edge **)realloc(endParadero->edges, (endParadero->numEdges + 1) * sizeof(Edge *));
      endParadero->edges[endParadero->numEdges] = newEdgeEndToStart;
      endParadero->numEdges++;

      // Add both paraderos to the route paraderos list
      newRuta->paraderos[newRuta->numParaderos] = startParadero;
      newRuta->numParaderos++;
      newRuta->paraderos[newRuta->numParaderos] = endParadero;
      newRuta->numParaderos++;

      // Correctly handle horariosParadero for startParadero
      Horario *horarioPartida = (Horario *)malloc(sizeof(Horario));
      strcpy(horarioPartida->tiempoLlegada, tiempoPartida);
      if (startParadero->horariosParadero == NULL) {
          startParadero->horariosParadero = (Horario **)malloc(sizeof(Horario *) * 100); // Allocate array of Horario pointers
          startParadero->numHorarios = 0;
      }
      startParadero->horariosParadero[startParadero->numHorarios] = horarioPartida;
      startParadero->numHorarios++;

      // Correctly handle horariosParadero for endParadero
      Horario *horarioLlegada = (Horario *)malloc(sizeof(Horario));
      strcpy(horarioLlegada->tiempoLlegada, tiempoLlegada);
      if (endParadero->horariosParadero == NULL) {
          endParadero->horariosParadero = (Horario **)malloc(sizeof(Horario *) * 100); // Allocate array of Horario pointers
          endParadero->numHorarios = 0;
      }
      endParadero->horariosParadero[endParadero->numHorarios] = horarioLlegada;
      endParadero->numHorarios++;

  }

  // Add the new route to the routes array
  rutas[*numRutas] = newRuta;
  (*numRutas)++;


  printf("Ruta agregada con éxito.\n");
}


void editarRutaBus(Graph *graph, Ruta **rutas, int *numRutas) {
    int busNumber, option, startNumber, endNumber, distancia, rutaIndex = -1;
    char tiempoLlegada[6]; // HH:MM format
    char tiempoPartida[6]; // HH:MM format

    printf("Ingrese el número del bus de la ruta a editar: ");
    scanf("%d", &busNumber);

    // Buscar la ruta por el número de bus
    for (int i = 0; i < *numRutas; i++) {
        if (rutas[i]->busRuta == busNumber) {
            rutaIndex = i;
            break;
        }
    }

    if (rutaIndex == -1) {
        printf("Ruta no encontrada.\n");
        return;
    }

    MostrarMenuEditarRuta();
    scanf("%d", &option);
    /* TODO: CASO N°2 */
    switch (option) {
        case 1:
            printf("Ingrese el nuevo número de bus: ");
            scanf("%d", &busNumber);
            rutas[rutaIndex]->busRuta = busNumber;
            printf("Número de bus actualizado.\n");
            break;
        case 2:
            printf("Funcionalidad para editar paraderos no implementada.\n");
            // Aquí se implementaría la lógica para editar paraderos
            break;
        case 3:
            printf("Ingrese el número del paradero de inicio: ");
            scanf("%d", &startNumber);
            printf("Ingrese el número del paradero de destino: ");
            scanf("%d", &endNumber);
            printf("Ingrese la nueva distancia entre los paraderos (en metros): ");
            scanf("%d", &distancia);

            // Aquí se buscarían los paraderos y se actualizaría la distancia
            updateDistance(graph, startNumber, endNumber, distancia);

            printf("Distancia actualizada.\n");
            break;
        case 4:
            printf("Ingrese el número del paradero: ");
            scanf("%d", &startNumber);
            printf("Ingrese el tiempo de partida al paradero (HH:MM): ");
            scanf("%s", tiempoLlegada);

            updateSchedule(graph, startNumber, tiempoLlegada);

            printf("Tiempos actualizados.\n");
            break;
        case 5:
            //eliminarRuta();
        case 6:
            limpiarPantalla();
            MostrarMenuRutas();
        default:
            printf("Opción no válida.\n");
            break;
    }
}

void listarRutaBus(Ruta **rutas, int numRutas) {
  printf("Listado de Rutas:\n");
  for (int i = 0; i < numRutas; i++) {
      Ruta *ruta = rutas[i];
      printf("Ruta %d: Bus %d\n", i + 1, ruta->busRuta);
      printf("Número de Paraderos: %d\n", ruta->numParaderos);
      for (int j = 0; j < ruta->numParaderos; j++) {
          Paradero *paradero = ruta->paraderos[j];
          printf("  Paradero %d: %d\n", j + 1, paradero->numeroParadero);
          // Print horarios for each paradero
          printf("    Horarios:\n");
          for (int k = 0; k < paradero->numHorarios; k++) {
              printf("      %s\n", paradero->horariosParadero[k]->tiempoLlegada);
          }
      }
  }
}