#include <stdio.h>
#include <stdlib.h>
#include "../tdas/extra.h"

typedef struct Paradero Paradero;  // Forward declaration of Paradero
typedef struct Edge Edge;  // Forward declaration of Edge

typedef struct Bus {
    int numeroBus;
} Bus;

void agregarBus(Bus **buses, int *numBuses) {
  Bus *newBus = (Bus *)malloc(sizeof(Bus));
  printf("Ingrese el número del bus: ");
  scanf("%d", &newBus->numeroBus);

  buses[*numBuses] = newBus;
  (*numBuses)++;

  printf("Bus agregado con éxito.\n");
}

void editarBus(Bus **buses, int *numBuses) {
  int currentNumber, newNumber;
  printf("Ingrese el número del bus que desea editar: ");
  scanf("%d", &currentNumber);

  for (int i = 0; i < *numBuses; i++) {
    if (buses[i]->numeroBus == currentNumber) {
      printf("Ingrese el nuevo número del bus: ");
      scanf("%d", &newNumber);
      buses[i]->numeroBus = newNumber;
      printf("Número de bus actualizado con éxito.\n");
      return;
    }
  }
  printf("Bus no encontrado.\n");
}

void listarBuses(Bus** buses, int *numBuses) {
  if (*numBuses == 0) {
    printf("No hay buses para mostrar.\n\n");
    return;
  }

  printf("Listado de Buses Disponibles:\n");
  for (int i = 0; i < *numBuses; i++) {
    printf("%d) Bus: %d\n", i + 1, buses[i]->numeroBus);
  }
}