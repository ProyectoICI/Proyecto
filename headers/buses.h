#ifndef BUSES_H
#define BUSES_H

typedef struct Bus Bus;

void agregarBus(Bus **buses, int *numBuses);
void editarBus(Bus **buses, int *numBuses);
void listarBuses(Bus **buses, int *numBuses);

#endif