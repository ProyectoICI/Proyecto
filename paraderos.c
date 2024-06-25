#include "paraderos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void agregarParadero(Map *mapParaderos) {
    Paradero *newParadero = (Paradero*)malloc(sizeof(Paradero));
    if (newParadero == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo paradero.\n");
        return;
    }
    printf("Ingrese el nombre del paradero: ");
    scanf(" %[^\n]", newParadero->nombreParadero);

    printf("Ingrese el número del paradero: ");
    scanf("%d", &newParadero->numeroParadero);

    printf("Ingrese la cantidad de horarios para el paradero: ");
    scanf("%d", &newParadero->cantHorarios);

    newParadero->horariosParadero = (Horario*)malloc(newParadero->cantHorarios * sizeof(Horario));

    for (int i = 0; i < newParadero->cantHorarios; i++) {
        printf("Ingrese el número de bus para el horario %d: ", i + 1);
        scanf(" %[^\n]", newParadero->horariosParadero[i].numeroBus);

        printf("Ingrese el tiempo de llegada para el horario %d (HHMM): ", i + 1);
        scanf(" %[^\n]", newParadero->horariosParadero[i].tiempoLlegada);
    }

    map_insert(mapParaderos, newParadero->nombreParadero, newParadero);
}
