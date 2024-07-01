#ifndef RUTAS_H
#define RUTAS_H

#include <sqlite3.h>

typedef struct Graph Graph;
typedef struct Ruta Ruta;

void agregarRutaBus(sqlite3* db, Graph *graph, Ruta **rutas, int *numRutas);
void editarRutaBus(Graph *graph, Ruta **rutas, int *numRutas);
void listarRutaBus(Ruta **rutas, int numRutas);
void planificarTrayecto(Graph *graph, Ruta **rutas, int numRutas);

#endif