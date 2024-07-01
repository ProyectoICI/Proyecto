// ** LIBRERIAS EXTRAS **
#include "../tdas/extra.h"
#include "../tdas/map.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sqlite3.h>

//-------------------------------------------------------------------------------------

typedef struct Paradero Paradero; 
typedef struct Edge Edge;         

Paradero *findParaderoById(sqlite3 *db, int id);

typedef struct Usuario {
  char nombre[50];
  bool esAdmin;
} Usuario;

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

typedef struct Bus {
  int numeroBus;
} Bus;

typedef struct Ruta {
  int busRuta;
  Paradero **paraderos;
  int numParaderos;
} Ruta;

//--------------------------  FUNCIONES AUXILIARES  -----------------------------------------------

void cargarHorariosPorParadero(sqlite3 *db, Paradero *paradero,
                               int paraderoKey) {
  sqlite3_stmt *stmt;
  const char *sql =
      "SELECT BusID, ArrivalTime FROM Horarios WHERE ParaderoID = ?";
  int result;
  int index = 0;

  result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (result != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare select statement: %s\n",
            sqlite3_errmsg(db));
    return;
  }

  sqlite3_bind_int(stmt, 1, paraderoKey);

  paradero->horariosParadero = (Horario **)malloc(paradero->numHorarios * sizeof(Horario *));

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    Horario *horario = (Horario *)malloc(sizeof(Horario));

    strcpy(horario->numeroBus, (char *)sqlite3_column_text(stmt, 0));
    strcpy(horario->tiempoLlegada, (char *)sqlite3_column_text(stmt, 1));

    paradero->horariosParadero =realloc(paradero->horariosParadero, (paradero->numHorarios + 1) * sizeof(Horario *));
    paradero->horariosParadero[index] = horario;
    index++;
  }

  sqlite3_finalize(stmt);
}

/*
  TODO: Replantear la forma en la que la función carga las direcciones de memoria
  de los 'Edge's de cada nodo
  
*/

void cargarEdgesPorParadero(sqlite3 *db, Paradero *paradero, int paraderoKey) {
  sqlite3_stmt *stmt;
  const char *sql = "SELECT StartParaderoID, EndParaderoID, Distance FROM Edges WHERE StartParaderoID = ? OR EndParaderoID = ?";
  int result;
  int index = 0;

  result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (result != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare select statement: %s\n",
            sqlite3_errmsg(db));
    return;
  }

  sqlite3_bind_int(stmt, 1, paraderoKey);
  sqlite3_bind_int(stmt, 2, paraderoKey);

  paradero->edges = (Edge **)malloc(paradero->numEdges * sizeof(Edge *));

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    if (paradero->edges == NULL) {
      paradero->edges = (Edge **)malloc(sizeof(Edge *));
    } else {
      paradero->edges =
          realloc(paradero->edges, (paradero->numEdges + 1) * sizeof(Edge *));
    }

    Edge *edge = (Edge *)malloc(sizeof(Edge));
    // Assuming findParaderoById is implemented elsewhere

    /* Deben ser punteros a direcciones de memorias de los paraderos
    edge->startNode = &startNode;
    edge->endNode = &endNode;
    */
    
    edge->distancia = sqlite3_column_int(stmt, 2);

    paradero->edges[index] = edge;
    index++;
  }

  sqlite3_finalize(stmt);

}

void cargarParaderosPorRuta(sqlite3 *db, Ruta *ruta, int rutaKey) {
    sqlite3_stmt *stmt;
    int index = 0;
    const char *sql = "SELECT ParaderoID FROM RouteParaderos WHERE RouteID = ?";
    ruta->paraderos = (Paradero **)malloc(ruta->numParaderos * sizeof(Paradero*)); 
    printf("Here");

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, rutaKey); 

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int paraderoID = sqlite3_column_int(stmt, 0); 

            Paradero *paradero = findParaderoById(db, paraderoID);
            ruta->paraderos[index] = paradero;
            index++;
        }
        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "Failed to select data: %s\n", sqlite3_errmsg(db));
    }
}

Paradero *findParaderoById(sqlite3 *db, int id) {
  const char *sql = "SELECT Name, Number, numEdges, numHorarios FROM Paraderos "
                    "WHERE ParaderoID = ?";
  sqlite3_stmt *stmt;
  Paradero *paradero = NULL;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
      paradero = (Paradero *)malloc(sizeof(Paradero));
      strncpy(paradero->nombreParadero, (char *)sqlite3_column_text(stmt, 0),
              sizeof(paradero->nombreParadero) - 1);
      paradero->nombreParadero[sizeof(paradero->nombreParadero) - 1] = '\0';
      paradero->numeroParadero = sqlite3_column_int(stmt, 1);
      paradero->numEdges = sqlite3_column_int(stmt, 2);
      paradero->numHorarios = sqlite3_column_int(stmt, 3);

      cargarHorariosPorParadero(db, paradero, id);
      cargarEdgesPorParadero(db, paradero, id);
    }

    sqlite3_finalize(stmt);
  } else {
    fprintf(stderr, "Failed to prepare select statement: %s\n",
            sqlite3_errmsg(db));
  }

  return paradero;
}

//-------------------------------------------------------------------------------------

void cargarUsuarios(Map *usuarios, sqlite3 *db) {
  sqlite3_stmt *stmt;
  const char *sql = "SELECT Name, isAdmin FROM Users";

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      Usuario *usuario = (Usuario *)malloc(sizeof(Usuario));
      strcpy(usuario->nombre, (const char *)sqlite3_column_text(stmt, 0));
      usuario->esAdmin = sqlite3_column_int(stmt, 1);
      map_insert(usuarios, usuario->nombre, usuario);
    }
    sqlite3_finalize(stmt);
  } else {
    fprintf(stderr, "Failed to select data: %s\n", sqlite3_errmsg(db));
  }
}

Bus **cargarBuses(sqlite3 *db, int *numBuses) {
  sqlite3_stmt *stmt;
  const char *sql = "SELECT Number FROM Buses";
  Bus **buses = NULL;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      buses = realloc(buses, (*numBuses + 1) * sizeof(Bus *));
      Bus *bus = (Bus *)malloc(sizeof(Bus));
      bus->numeroBus = sqlite3_column_int(stmt, 0);
      buses[(*numBuses)] = bus;
      (*numBuses)++;
    }
    sqlite3_finalize(stmt);
  } else {
    fprintf(stderr, "Failed to select data: %s\n", sqlite3_errmsg(db));
  }

  return buses;
}

Paradero **cargarParaderos(sqlite3 *db, int *numParaderos) {
  sqlite3_stmt *stmt;
  int paraderoKey;
  const char *sql =
      "SELECT ParaderoID, Name, Number, numEdges, numHorarios FROM Paraderos";
  Paradero **paraderos = (Paradero**)malloc(100 * sizeof(Paradero*));

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
    while (sqlite3_step(stmt) == SQLITE_ROW) {

      paraderoKey = sqlite3_column_int(
          stmt, 0); 

      paraderos = realloc(paraderos, (*numParaderos + 1) * sizeof(Paradero *));
      Paradero *paradero = (Paradero *)malloc(sizeof(Paradero));

      strcpy(paradero->nombreParadero, (char *)sqlite3_column_text(stmt, 1));
      paradero->numeroParadero = sqlite3_column_int(stmt, 2);

      paradero->numEdges = sqlite3_column_int(stmt, 3);
      paradero->numHorarios = sqlite3_column_int(stmt, 4);

      cargarHorariosPorParadero(db, paradero, paraderoKey);
      cargarEdgesPorParadero(db, paradero, paraderoKey);

      paraderos[(*numParaderos)] = paradero;
      (*numParaderos)++;
    }
    sqlite3_finalize(stmt);
  } else {
    fprintf(stderr, "Failed to select data: %s\n", sqlite3_errmsg(db));
  }

  return paraderos;
}

Ruta** cargarRutas(sqlite3* db, int* numRutas) {
    printf("Here\n");
    sqlite3_stmt *stmt;
    const char *sql = "SELECT RouteID, BusID, NumParaderos FROM Routes";
    Ruta **rutas = (Ruta**)malloc(100 * sizeof(Ruta*));
    printf("Here\n");

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int rutaKey = sqlite3_column_int(stmt, 0); 

            rutas = realloc(rutas, (*numRutas + 1) * sizeof(Ruta*)); 
          
            Ruta *ruta = (Ruta *)malloc(sizeof(Ruta));
            ruta->busRuta = sqlite3_column_int(stmt, 1);
            ruta->numParaderos = sqlite3_column_int(stmt, 2);
            ruta->paraderos = (Paradero**)malloc(100 * sizeof(Paradero*));
            printf("Here\n");

            cargarParaderosPorRuta(db, ruta, rutaKey); 

            rutas[*numRutas] = ruta; 
            (*numRutas)++; 
        }
        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "Failed to select data: %s\n", sqlite3_errmsg(db));
    }

    return rutas;
}

//-------------------------------------------------------------------------------------