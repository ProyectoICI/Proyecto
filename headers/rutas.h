#ifndef RUTAS_H
#define RUTAS_H

typedef struct Graph Graph;
typedef struct Ruta Ruta;

void agregarRutaBus(Graph *graph, Ruta **rutas, int *numRutas);
void editarRutaBus(Graph *graph, Ruta **rutas, int *numRutas);
void listarRutaBus(Ruta **rutas, int numRutas);

#endif