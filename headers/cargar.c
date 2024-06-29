// ** LIBRERIAS EXTRAS **
#include "../tdas/extra.h"
#include "../tdas/map.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <sqlite3.h>

typedef struct Paradero Paradero; // Forward declaration of Paradero
typedef struct Edge Edge;         // Forward declaration of Edge

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
    Horario** horariosParadero;
    Edge** edges;  
    int numEdges;  
    int numHorarios;
} Paradero;

struct Edge {
    Paradero* startNode;
    Paradero* endNode;
    int distancia;
};

typedef struct Bus {
    int numeroBus;
} Bus;

typedef struct Ruta {
    int busRuta;
    Paradero** paraderos;
    int numParaderos;
} Ruta;

// Function para checkear si un .csv está vacío
bool isCSVFileEmpty(const char *filePath) {
    FILE *file = fopen(filePath, "r"); 
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return true; 
    }

    fseek(file, 0, SEEK_END); 
    long fileSize = ftell(file); 
    fclose(file); 

    return fileSize == 0;
}

void cargarUsuarios(Map *usuarios) {
  FILE *archivo = fopen("data/usuarios.csv", "r");
  if (archivo == NULL) {
    perror("Error al abrir el archivo de usuarios.csv");
    return;
  }

  char **campos;
  campos = leer_linea_csv(archivo, ',');

  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    Usuario *usuario = (Usuario *)malloc(sizeof(Usuario));
    strcpy(usuario->nombre, campos[0]);

    if (strcmp(campos[2], "1") == 0) {
      usuario->esAdmin = true;
    } else {
      usuario->esAdmin = false;
    }
    map_insert(usuarios, usuario->nombre, usuario);
  }
  fclose(archivo);
}

Paradero** cargarParaderos(Paradero** paraderos, int* numNodes)
{
    FILE *archivo = fopen("data/paraderos.csv", "r"); 
    if (archivo == NULL) {
        perror("Error al abrir el archivo de paraderos.csv");
        return NULL;
    }

    char **campos;
    campos = leer_linea_csv(archivo, ',');

    while ((campos = leer_linea_csv(archivo, ',')) != NULL)
        {
            Paradero *paradero = (Paradero *)malloc(sizeof(Paradero));
            *paradero->nombreParadero = atoi(campos[0]);
            paradero->numeroParadero = atoi(campos[1]);
            
            // Ver como hacerlo aca
            paradero->horariosParadero = (Horario **)malloc(sizeof(Horario *));
            paradero->edges = (Edge **)malloc(sizeof(Edge *));

            paradero->numEdges = atoi(campos[4]);
            paradero->numHorarios = atoi(campos[5]);
            
            paraderos[(*numNodes)] = paradero;
            (*numNodes)++;
        }
    fclose(archivo);
    return paraderos;
}

Bus** cargarBuses(Bus** buses, int* numBuses)
{
    FILE *archivo = fopen("data/buses.csv", "r"); 
    if (archivo == NULL) {
        perror("Error al abrir el archivo de buses.csv");
        return NULL;
    }

    char **campos;
    campos = leer_linea_csv(archivo, ',');

    while ((campos = leer_linea_csv(archivo, ',')) != NULL)
        {
            Bus *bus = (Bus *)malloc(sizeof(Bus));
            bus->numeroBus = atoi(campos[1]);
            buses[(*numBuses)] = bus;
            (*numBuses)++;
        }
    fclose(archivo);
    return buses;
}

Ruta** cargarRutas(Ruta** rutas, int* numRutas) {
    FILE *archivo = fopen("data/rutas.csv", "r"); 
    if (archivo == NULL) {
        perror("Error al abrir el archivo de rutas.csv");
        return NULL;
    }

    char **campos;
    campos = leer_linea_csv(archivo, ',');

    while ((campos = leer_linea_csv(archivo, ',')) != NULL)
        {
            Ruta *ruta = (Ruta *)malloc(sizeof(Ruta));
            ruta->busRuta = atoi(campos[0]);

            // Ver aca como hacerlo
            /*
            FILE *archivoHorario = fopen("data/horarios.csv", "r");
            if (archivo == NULL) {
                
            }
            */
            ruta->paraderos = (Paradero **)malloc(sizeof(Paradero *));
            
            ruta->numParaderos = atoi(campos[2]);
            rutas[(*numRutas)] = ruta;
            (*numRutas)++;
        }
    fclose(archivo);
    return rutas;
}
