#ifndef BUSES_H
#define BUSES_H

#include <sqlite3.h>

typedef struct Bus Bus;

void agregarBus(sqlite3 *db, Bus ***buses, int *numBuses);
void editarBus(sqlite3 *db, Bus **buses, int *numBuses);
void listarBuses(Bus** buses, int *numBuses);

#endif