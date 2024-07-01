#include <stdio.h>
#include <stdlib.h>
#include "../tdas/extra.h"

#include <sqlite3.h>

//-------------------------------------------------------------------------------------

typedef struct Paradero Paradero;  // Forward declaration of Paradero
typedef struct Edge Edge;  // Forward declaration of Edge

typedef struct Bus {
    int numeroBus;
} Bus;

//-------------------------------------------------------------------------------------

void agregarBus(sqlite3 *db, Bus ***buses, int *numBuses) {
    Bus *newBus = (Bus *)malloc(sizeof(Bus));
    if (newBus == NULL) {
        printf("Error al asignar memoria para el nuevo bus.\n");
        return;
    }

    printf("Ingrese el número del bus: ");
    scanf("%d", &newBus->numeroBus);

    const char *sql = "INSERT INTO Buses (Number) VALUES (?)";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        free(newBus);
        return;
    }

    sqlite3_bind_int(stmt, 1, newBus->numeroBus);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Error al agregar el bus a la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        free(newBus);
        return;
    }
    sqlite3_finalize(stmt);

    *buses = (Bus **)realloc(*buses, (*numBuses + 1) * sizeof(Bus *));
    if (*buses == NULL) {
        printf("Error al reasignar memoria para la lista de buses.\n");
        free(newBus);
        return;
    }

    (*buses)[*numBuses] = newBus;
    (*numBuses)++;

}

void listarBuses(Bus** buses, int *numBuses) {
  if (*numBuses == 0) {
    printf("No hay buses para mostrar.\n\n");
    presioneTeclaParaContinuar();
    return;
  }

  printf("Listado de Buses Disponibles:\n");
  for (int i = 0; i < *numBuses; i++) {
    printf("%d) Bus: %d\n", i + 1, buses[i]->numeroBus);
  }
  presioneTeclaParaContinuar();
}

/* TODO: Agregar Borrar un bus */
void editarBus(sqlite3 *db, Bus **buses, int *numBuses) {
    int currentNumber, newNumber;
    sqlite3_stmt *stmt;

    printf("Ingrese el número del bus que desea editar: ");
    scanf("%d", &currentNumber);

    for (int i = 0; i < *numBuses; i++) {
        if (buses[i]->numeroBus == currentNumber) {
            printf("Ingrese el nuevo número del bus: ");
            scanf("%d", &newNumber);
            buses[i]->numeroBus = newNumber;

            const char *sql = "UPDATE Buses SET Number = ? WHERE Number = ?";
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
                fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
                return;
            }

            sqlite3_bind_int(stmt, 1, newNumber);
            sqlite3_bind_int(stmt, 2, currentNumber);

            if (sqlite3_step(stmt) != SQLITE_DONE) {
                fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
            }

            sqlite3_finalize(stmt);
            return;
        }
    }
    printf("Bus no encontrado.\n");
}

//-------------------------------------------------------------------------------------