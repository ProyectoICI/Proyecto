#include <stdio.h>
#include <stdlib.h>
#include "../tdas/extra.h"

#include <sqlite3.h>

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

typedef struct Graph {
  Paradero **nodes;
  int numNodes;
} Graph;

//-------------------------------------------------------------------------------------


void agregarParadero(sqlite3* db, Graph *graph) {
  Paradero *paradero = (Paradero *)malloc(sizeof(Paradero));
  int numero;
  int numNodesGraph;
  if (!paradero) {
      printf("Error al asignar memoria para el paradero.\n");
      return;
  }
  paradero->numeroParadero = 0;
  paradero->horariosParadero = NULL;
  paradero->edges = NULL;
  paradero->numHorarios = 0;
  paradero->numEdges = 0;

  printf("Ingrese el nombre del paradero: \n");
  scanf("%s", paradero->nombreParadero); 

  printf("Ingrese el número del paradero: \n");
  scanf("%d", &numero);

  paradero->numeroParadero = numero;


  const char *checkSql = "SELECT * FROM Paraderos WHERE Number = ?";
  sqlite3_stmt *checkStmt;
  if (sqlite3_prepare_v2(db, checkSql, -1, &checkStmt, NULL) != SQLITE_OK) {
    printf("Failed to prepare check statement\n");
    presioneTeclaParaContinuar();
    return;
  }

  sqlite3_bind_int(checkStmt, 1, paradero->numeroParadero);

  if (sqlite3_step(checkStmt) == SQLITE_ROW) {
    printf("Paradero '%d' ya existe.\n", paradero->numeroParadero);
    sqlite3_finalize(checkStmt);
    presioneTeclaParaContinuar();

    return;
  }
  sqlite3_finalize(checkStmt);

  numNodesGraph = graph->numNodes;
  graph->nodes[numNodesGraph] = paradero;
  graph->numNodes++;

  const char *sql = "INSERT INTO Paraderos (Name, Number, numEdges, numHorarios) VALUES (?, ?, ?, ?)";
  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
    printf("Failed to prepare statement\n");
    presioneTeclaParaContinuar();

    return;
  }

  sqlite3_bind_text(stmt, 1, paradero->nombreParadero, -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 2, paradero->numeroParadero);
  sqlite3_bind_int(stmt, 3, paradero->numEdges); 
  sqlite3_bind_int(stmt, 4, paradero->numHorarios);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    printf("Failed to execute statement: %s\n", sqlite3_errmsg(db));
    presioneTeclaParaContinuar();

  } 

  sqlite3_finalize(stmt);
}

void editarParadero(Graph *graph) {
  int currentNumber;
  printf("Ingrese el número del paradero que desea editar: ");
  scanf("%d", &currentNumber);

  for (int i = 0; i < graph->numNodes; i++) {
    if (graph->nodes[i]->numeroParadero == currentNumber) {
      printf("Ingrese el nuevo nombre del paradero: ");
      scanf("%s", graph->nodes[i]->nombreParadero);
      printf("Ingrese el nuevo número del paradero: ");
      scanf("%d", &graph->nodes[i]->numeroParadero);
      printf("Paradero actualizado con éxito.\n");
      return;
    }
  }
  printf("Paradero no encontrado.\n");
  presioneTeclaParaContinuar();
}

void listaDeParaderos(Graph *graph) {
  if (graph->numNodes == 0) {
    printf("No hay paraderos para mostrar.\n");
    presioneTeclaParaContinuar();
    return;
  }

  printf("Listado de Paraderos:\n");
  for (int i = 0; i < graph->numNodes; i++) {
    printf("Nombre: %s, Número: %d\n", graph->nodes[i]->nombreParadero,
           graph->nodes[i]->numeroParadero);
  }
  presioneTeclaParaContinuar();
}

//-------------------------------------------------------------------------------------
