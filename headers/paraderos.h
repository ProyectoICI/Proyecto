#ifndef PARADEROS_H
#define PARADEROS_H

#include <sqlite3.h>

typedef struct Graph Graph;

void agregarParadero(sqlite3* db, Graph *graph);
void editarParadero(Graph *graph);
void listaDeParaderos(Graph *graph);

#endif