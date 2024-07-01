#ifndef CONSULTAS_H
#define CONSULTAS_H

typedef struct Graph Graph;
typedef struct Ruta Ruta;

void consultaHorarioParada(Graph* graph);
void consultaHorarioRuta(Ruta** rutas, int* numRutas);

void generarReporte(Ruta** rutas, int numRutas);

#endif