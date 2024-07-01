#ifndef MENUS_H
#define MENUS_H

#include <stdio.h> 
#include <sqlite3.h>

typedef struct Graph Graph;
typedef struct Bus Bus;
typedef struct Ruta Ruta;
typedef struct Map Map;

void MostrarMenuPrincipal();
void MostrarIniciarSesion();
void MostrarRegistroUsuario();

void MostrarMenuAdmin();
void MostrarMenuParaderos();
void MostrarMenuBuses();
void MostrarMenuRutas();
void MostrarMenuOtros();

void MostrarMenuUsuarios();
void MostrarMenuTrayecto();
void MostrarMenuConsultas();

void MostrarMenuEditarBus();
void MostrarMenuEditar();
void MostrarMenuEditarRuta();

void MenuAdmin(Graph *graph, Bus **buses, int *numBuses, Ruta** rutas, int* numRutas, sqlite3* db);
void MenuUsuario(Graph *graph, Ruta** rutas, int* numRutas);

void ingresoSesion(sqlite3 *db, Graph* graph, Bus*** buses, int* numBuses, Ruta*** rutas, int* numRutas);
void registroUsuario(Map *usuarios, sqlite3 *db);

void mostrarIngreso(Map* MapUsuarios, Graph* graph, Bus** buses,
int* numBuses, Ruta** rutas, int* numRutas, sqlite3* db);

#endif