#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include "menus.c"

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

//

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

int is_equal_str(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2) == 0;
}


void cargarUsuarios(Map *usuarios)
{
    FILE* archivo = fopen("usuarios.csv", "r");
    if (archivo == NULL) {
        perror(
            "Error al abrir el archivo de usuarios.csv"); // Mensaje de error"
        return;
        
    }

    char **campos;

    campos = leer_linea_csv(archivo, ',');

    while((campos = leer_linea_csv(archivo, ',')) != NULL) {
        Usuario *usuario = (Usuario*)malloc(sizeof(Usuario));
        strcpy(usuario->nombre, campos[1]);
        if (strcmp(campos[2], "1") == 0) {
            usuario->esAdmin = true;
        }
        else 
            usuario->esAdmin = false;

        map_insert(usuarios, usuario->nombre, usuario);
    }
    fclose(archivo);    
}


void MenuAdmin()
{
    char opcion;
    do 
    {
        
        MostrarMenuAdmin();
        printf("\nIngrese su opción");
        scanf(" %c", &opcion);
        switch (opcion)
        {
            case '1':
            {

            }


            case '2':
            {

            }


            case '3':
            {

            }


            case '4':
            {

            }

            default:
            {
                printf("\n");
            }
        }
        
        
    } while (opcion != '5');
}

void MenuUsuario()
{

}


void ingresoSesion(Map *usuarios) {
    char usuario[50];
    printf("Ingreso a sesion\n");
    printf("Por favor ingrese su Usuario: ");
    scanf("%s", usuario);
    while(true)
        {
            MapPair *pair = map_search(usuarios, usuario);
            if (pair != NULL)
            {
                Usuario *usuarioEnc  = pair->value;
                if (usuarioEnc->esAdmin == true)
                    MenuAdmin();
                else
                    MenuUsuario();
                break;
            }
            else 
            {
                printf("Usuario no encontrado, intente de nuevo: ");
                ingresoSesion(usuarios);
            }
            
        }
}



void registroUsuario() {
    printf("Registro de usuario\n");
}


void mostrarIngreso() {
    char input[10];
    int opcion;
    int isNumber;
    Map *MapUsuarios = map_create(is_equal_str);
    cargarUsuarios(MapUsuarios);

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
        // hola

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
        ingresoSesion(MapUsuarios);
        
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