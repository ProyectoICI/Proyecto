#ifndef CARGAR_H
#define CARGAR_H

#include <stdbool.h>

typedef struct Map Map;

typedef struct Paradero Paradero;
typedef struct Bus Bus;
typedef struct Rutas Rutas;

void cargarUsuarios(Map *usuarios);

// Carga las listas de entidades que usará el grafo
Paradero** cargarParaderos(Paradero** paraderos, int* numNodes);
Bus** cargarBuses(Bus** buses, int* numBuses);
Rutas** cargarRutas(Rutas** rutas, int* numRutas);

// Función que checkea si un archivo .csv está vacío
bool isCSVFileEmpty(const char *filePath);

#endif