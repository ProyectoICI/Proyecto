#ifndef CARGAR_H
#define CARGAR_H

#include <stdbool.h>
typedef struct Map Map;

typedef struct Paradero Paradero;
typedef struct Bus Bus;
typedef struct Ruta Ruta;

typedef struct sqlite3 sqlite3;

void cargarUsuarios(Map *usuarios, sqlite3 *db);

// Carga las listas de entidades que usará el grafo
Paradero** cargarParaderos(sqlite3 *db, int* numParaderos);
Bus** cargarBuses(sqlite3 *db, int* numBuses);
Ruta** cargarRutas(sqlite3* db, int* numRutas);

Paradero* findParaderoById(sqlite3 *db, int id);

// Para cargas las entidades anidadas desde la base de datos
void cargarHorariosPorParadero(sqlite3 *db, Paradero *paradero, int paraderoKey);
void cargarEdgesPorParadero(sqlite3 *db, Paradero *paradero, int paraderoKey);
void cargarParaderosPorRuta(sqlite3* db, Ruta* ruta, int rutaKey);

#endif