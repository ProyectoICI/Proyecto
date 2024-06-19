#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // for isdigit
#include <string.h> // for strlen
#include <stdbool.h>

typedef struct Paradero Paradero;  // Forward declaration of Paradero
typedef struct Edge Edge;  // Forward declaration of Edge


// Declaración de entidades
// -- TODO: Modificar el informe porque está cambiada la entidad
// - Paradero, -Graph

typedef struct Horario {
    char numeroBus[50];
    char tiempoLlegada[6];
} Horario;

typedef struct Paradero {
    char nombreParadero[100];
    int numeroParadero;
    Horario* horariosParadero;
    Edge** edges;  
    int numEdges;  
} Paradero;

struct Edge {
    Paradero* startNode;
    Paradero* endNode;
    int distancia;
};

typedef struct Graph {
    Paradero** nodes; 
    int numNodes;  
} Graph;

typedef struct Usuario {
    char nombre[50];
    bool esAdmin;
} Usuario;

// -- BUSES -- //

typedef struct Bus {
    int numeroBus;
} Bus;

typedef struct Ruta {
    int busRuta;
    Paradero* paraderos;
} Ruta;


// -- TODO: Implementar funciones -- //

void ingresoSesion() {
    printf("Ingreso a sesion\n");
}

void registroUsuario() {
    printf("Registro de usuario\n");
}


void mostrarIngreso() {
    char input[10];
    int opcion;
    int isNumber;

    do {
        printf(" ** SISTEMA DE BUSES **\n");
        printf(" 1) Iniciar Sesion\n");
        printf(" 2) Registrarse\n");
        printf(" 3) Salir\n");

        fgets(input, sizeof(input), stdin);

        if (strlen(input) > 0 && input[strlen(input)-1] == '\n') {
            input[strlen(input)-1] = '\0';
        }

        isNumber = 1;
        
        for (int i = 0; i < strlen(input); i++) {
            if (!isdigit(input[i])) {
                isNumber = 0;
                break;
            }
        }

        if (isNumber) {
            opcion = atoi(input);
        }

        if (!isNumber || opcion < 1 || opcion > 3) {
            printf("Opcion invalida, ingrese una opción válida\n");
        }
    } while (!isNumber || opcion < 1 || opcion > 3);

    switch (opcion)
    {
    case 1:
        ingresoSesion();
        break;
    case 2:
        registroUsuario();
        break;
    case 3:
        printf("Salir\n");
        break;
    default:
        break;
    }
}


int main() {
    int opcion;

    mostrarIngreso();
}