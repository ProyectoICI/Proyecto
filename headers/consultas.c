#include <stdio.h>
#include <stdlib.h>
#include "../tdas/extra.h"

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

typedef struct Graph {
    Paradero** nodes;
    int numNodes;
} Graph;

typedef struct Ruta { 
    int busRuta;
    Paradero** paraderos; 
    int numParaderos;
} Ruta;

//-------------------------------------------------------------------------------------

void consultaHorarioParada(Graph* graph) {
    int numParada;
    printf("Ingrese el número de parada: ");
    scanf("%d", &numParada);

    for (int i = 0; i < graph->numNodes; i++) {
        if (graph->nodes[i]->numeroParadero == numParada) {
            Paradero* paradero = graph->nodes[i];
            printf("Horarios para la parada %d - %s:\n", numParada, paradero->nombreParadero);
            for (int j = 0; j < paradero->numHorarios; j++) {
                printf("Bus: %s, Llegada: %s\n", paradero->horariosParadero[j]->numeroBus, paradero->horariosParadero[j]->tiempoLlegada);
            }
            presioneTeclaParaContinuar();
            return; 
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
            return; 
        }
    }
    presioneTeclaParaContinuar();
    printf("No se encontró la ruta para el bus %d.\n", busDeRuta);
}

void generarReporte(Ruta** rutas, int numRutas) {
    FILE *archivo = fopen("reporte.txt", "w");
    if (archivo == NULL) {
        perror("Error al abrir el archivo para el reporte");
        return;
    }

    fprintf(archivo, "Reporte de Rutas:\n");
    fprintf(archivo, "=================\n\n");

    for (int i = 0; i < numRutas; i++) {
        Ruta *ruta = rutas[i];
        fprintf(archivo, "Ruta del Bus: %d\n", ruta->busRuta);
        fprintf(archivo, "Número de Paraderos: %d\n", ruta->numParaderos);

        for (int j = 0; j < ruta->numParaderos; j++) {
            Paradero *paradero = ruta->paraderos[j];
            fprintf(archivo, "  Paradero: %s (Número: %d)\n", paradero->nombreParadero, paradero->numeroParadero);

            fprintf(archivo, "  Horarios de Llegada:\n");
            for (int k = 0; k < paradero->numHorarios; k++) {
                Horario *horario = paradero->horariosParadero[k];
                fprintf(archivo, "    Bus: %s, Hora de Llegada: %s\n", horario->numeroBus, horario->tiempoLlegada);
            }

            fprintf(archivo, "  Edges:\n");
            for (int e = 0; e < paradero->numEdges; e++) {
                Edge *edge = paradero->edges[e];
                fprintf(archivo, "    De: %s a %s, Distancia: %d\n",
                        edge->startNode->nombreParadero,
                        edge->endNode->nombreParadero,
                        edge->distancia);
            }
            fprintf(archivo, "\n");
        }
        fprintf(archivo, "---------------------------\n");
    }

    fclose(archivo);
    printf("Reporte generado con éxito en 'reporte.txt'.\n");
}

//-------------------------------------------------------------------------------------
