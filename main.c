// ** DEPENDENCIAS ** 
#include "tdas/extra.h"     // Libreria de funciones extras
#include "tdas/list.h"      // Libreria de listas
#include "tdas/map.h"       // Libreria de mapas
#include "headers/pqueue.h" // Libreria de colas de prioridad

// ** HEADERS **
#include "headers/cargar.h"    // Libreria de carga de datos
#include "headers/menus.h"     // Libreria de menus
#include "headers/buses.h"     // Libreria de buses
#include "headers/paraderos.h" // Libreria de paraderos
#include "headers/rutas.h"     // Libreria de rutas
#include "headers/consultas.h" // Libreria de consultas

// ** STANDARD LIBRARY **
#include <ctype.h>   // Libreria de funciones de caracteres
#include <stdbool.h> // Libreria de booleanos
#include <stdio.h>   // Libreria de entrada y salida
#include <stdlib.h>  // Libreria de funciones de memoria
#include <string.h>  // Libreria de funciones de cadenas

#include <sqlite3.h>


typedef struct Paradero Paradero; // Forward declaration of Paradero
typedef struct Edge Edge;         // Forward declaration of Edge

// Declaración de entidades
// -- TODO: Modificar el informe porque está cambiada la entidad
// - Paradero, -Graph

//===========Declaración de Structs======================

typedef struct Horario { // Horario de un bus
  char numeroBus[50];    // Número de bus
  char tiempoLlegada[6]; // Hora de llegada
} Horario;

typedef struct PriorityQueueNode { // Nodo de la cola de prioridad
  Paradero* paradero;              // Paradero asociado al nodo
  int priority;                    // Prioridad del nodo
} PriorityQueueNode;               // Tipo de dato de la cola de prioridad

typedef struct PriorityQueue {  // Cola de prioridad
  PriorityQueueNode* nodes;     // Nodos de la cola de prioridad
  int size;                     // Tamaño de la cola de prioridad
  int capacity;                 // Capacidad de la cola de prioridad
} PriorityQueue;                // Tipo de dato de la cola de prioridad

typedef struct Paradero {       // Paradero de un bus
    char nombreParadero[100];   // Nombre del paradero
    int numeroParadero;         // Número del paradero
    Horario** horariosParadero; // Horarios de parada
    Edge** edges;               // Edges de un paradero
    int numEdges;               // Número de edges 
    int numHorarios;            // Número de horarios
} Paradero;                     // Tipo de dato de un paradero

struct Edge {            // Edge de un bus
    Paradero* startNode; // Nodo de inicio
    Paradero* endNode;   // Nodo de fin
    int distancia;       // Distancia entre los nodos
};

typedef struct Graph {   // Graph de un bus
    Paradero** nodes;    // Nodos del graph
    int numNodes;        // Número de nodos
} Graph;                 // Tipo de dato de un graph

typedef struct Usuario { // Usuario de un bus
    char nombre[50];     // Nombre del usuario
    bool esAdmin;        // Indica si el usuario es Administrador
} Usuario;               // Tipo de dato de un usuario

typedef struct Bus {     // Bus de un usuario
    int numeroBus;       // Número de bus
} Bus;                   // Tipo de dato de un bus

typedef struct Ruta {    // Ruta de un usuario
    int busRuta;         // Número de bus
    Paradero** paraderos;// Paraderos de la ruta
    int numParaderos;    // Número de paraderos
} Ruta;                  // Tipo de dato de una ruta

//==============================FUNCIONES PRINCIPALES==================================

bool contieneEspacios(const char *str) {    // Función para verificar si una cadena contiene espacios
    while (*str) {                          // Mientras haya caracteres en la cadena
        if (isspace((unsigned char)*str)) { // Verifica si el carácter es un espacio en blanco
            return true;                    // Si encuentra un espacio, devuelve true
        } str++;                            // Avanza al siguiente carácter
    }
    return false;                           // Si no encuentra espacios, devuelve false
}

//-------------------------------------------------------------------------------------

bool checkPassword(const char *username, const char *password, 
                   const char *filePath) {      // Función para verificar la contraseña
    FILE *file = fopen(filePath, "r");          // Abre el archivo en modo lectura
    if (!file) {                                // Si no se puede abrir el archivo
        perror("Error opening file");           // Mensaje de error
        return false;                           // Error al abrir el archivo
    }

    char line[1024];                            // Buffer para leer una línea del archivo
    while (fgets(line, sizeof(line), file)) {   // Leer una línea del archivo
        line[strcspn(line, "\n")] = 0;          // Eliminar el salto de línea al final de la línea
        char *token = strtok(line, ",");        // Separar la línea en tokens por "," como delimitador
        if (strcmp(token, username) == 0) {     // Comparar el nombre de usuario con el token
            token = strtok(NULL, ",");          // Obtener el token siguiente
            if (strcmp(token, password) == 0) { // Comparar la contraseña con el token
                fclose(file);                   // Cerrar el archivo
                return true;                    // La contraseña es correcta
            }
            break;                              // Salir del bucle si se encuentra el usuario
        }
    }
    fclose(file);                               // Cerrar el archivo
    return false;                               // La contraseña es incorrecta
}
//-------------------------------------------------------------------------------------

int timeToMinutes(const char* time) {           // Convertir tiempo de formato HH:MM a minutos
    int hours, minutes;                         // Variables para almacenar horas y minutos
    sscanf(time, "%d:%d", &hours, &minutes);    // Leer el tiempo desde la cadena
    return hours * 60 + minutes;                // Devolver el tiempo en minutos
}

//-------------------------------------------------------------------------------------

/* Ruta** filtrarRutasPorHora(Map *rutas, int numRutas, const char* hora, int* numRutasFiltradas) {
    int horaMinutos = timeToMinutes(hora); // Convertir la hora a minutos
    Ruta** rutasFiltradas = (Ruta**)malloc(numRutas * sizeof(Ruta*)); // Asignar memoria para las rutas filtradas
    *numRutasFiltradas = 0; // Inicializar el número de rutas filtradas
    for (int i = 0; i < numRutas; i++) { // Recorrer todas las rutas
        for (int j = 0; j < rutas[i]->numParaderos; j++) {
            for (int k = 0; k < rutas[i]->paraderos[j]->numHorarios; k++) {
                int tiempoLlegadaMinutos = timeToMinutes(rutas[i]->paraderos[j]->horariosParadero[k]->tiempoLlegada);
                if (tiempoLlegadaMinutos >= horaMinutos) { // Verificar si el tiempo de llegada es mayor o igual a la hora
                    rutasFiltradas[(*numRutasFiltradas)++] = rutas[i]; // Agregar la ruta a las rutas filtradas
                    break;
                }
            }
        }
    }
    return rutasFiltradas; // Devolver las rutas filtradas
}

bool rutaContieneParaderos(Ruta* ruta, int paraderoInicio, int paraderoDestino) {
    bool inicioEncontrado = false, destinoEncontrado = false; // Inicializar variables de búsqueda
    for (int i = 0; i < ruta->numParaderos; i++) {
        if (ruta->paraderos[i]->numeroParadero == paraderoInicio) { // Buscar el paradero de inicio
            inicioEncontrado = true; // Marcar el paradero de inicio como encontrado
        }
        if (ruta->paraderos[i]->numeroParadero == paraderoDestino) { // Marcar el paradero de destino como encontrado
            destinoEncontrado = true; // Marcar el paradero de destino como encontrado
        }
    }
    return inicioEncontrado && destinoEncontrado; // Devolver true si ambos paraderos fueron encontrados
}*/

// Función para encontrar la mejor ruta


//-------------------------------------------------------------------------------------

int obtenerOpcionValida(int min, int max)        // Función para obtener una opción válida del usuario
{
    char input[50];                              // Buffer para almacenar la entrada del usuario
    int opcion;                                  // Variable para almacenar la opción seleccionada
    static int contImpresiones = 0;              // Contador de impresiones

    while (true) {                               // Bucle infinito
        scanf("%49s", input);                    // Leer la entrada del usuario
        int esNumero = 1;                        // Variable para verificar si la entrada es un número
        for (int i = 0; input[i] != '\0'; i++) { // Recorrer la entrada
            if (!isdigit(input[i])) {            // Verificar si el carácter no es un dígito
                esNumero = 0;                    // Marcar la variable como no válida
                break;                           // Salir del bucle
            }
        }
        if (esNumero) {                          // Si la entrada es un número
            opcion = atoi(input);                // Convertir la entrada a un número entero
            if (opcion >= min && opcion <= max) break; // Salir del bucle si la opción es válida
        }
        if (contImpresiones == 0) {              // Si es la primera vez que se imprime el mensaje de error
            printf("\033[1;32m%s\033[0m\n","Opción inválida. Por favor, ingrese una opción válida.\n");
            contImpresiones++;                   // Incrementar el contador de impresiones
        }
    }
    contImpresiones = 0;                         // Reiniciar el contador de impresiones
    return opcion;                               // Retornar la opción seleccionada
}

//-------------------------------------------------------------------------------------

/*void planificarTrayecto(Graph *graph, Map *rutasMap) {
    int paraderoInicio, paraderoDestino;
    char hora[6];
    int numRutasFiltradas = 0;
    Ruta **rutasFiltradas = NULL;

    printf("Ingrese la hora de inicio (HH:MM): ");
    scanf("%5s", hora);

    rutasFiltradas = filtrarRutasPorHora(rutasMap, graph->numNodes, hora, &numRutasFiltradas);

    if (numRutasFiltradas == 0) {
        printf("No hay rutas disponibles para la hora especificada.\n");
        return;
    }

    printf("Rutas disponibles para la hora %s:\n", hora);
    for (int i = 0; i < numRutasFiltradas; i++) {
        printf("Ruta %d\n", i + 1);
        // Imprimir detalles de la ruta si es necesario
    }

    printf("Ingrese el número de la ruta que desea seleccionar: ");
    int opcion;
    scanf("%d", &opcion);

    if (opcion < 1 || opcion > numRutasFiltradas) {
        printf("Opción inválida.\n");
        return;
    }

    Ruta *rutaSeleccionada = rutasFiltradas[opcion - 1];

    printf("Ingrese el número de paradero de inicio: ");
    scanf("%d", &paraderoInicio);

    printf("Ingrese el número de paradero de destino: ");
    scanf("%d", &paraderoDestino);

    Ruta *mejorRuta = encontrarMejorRuta(rutaSeleccionada, paraderoInicio, paraderoDestino);
    if (mejorRuta != NULL) {
        printf("La mejor ruta encontrada es la Ruta del Bus: %d\n", mejorRuta->busRuta);
        // Puedes realizar más acciones o imprimir detalles adicionales de la ruta encontrada si es necesario
    } else {
        printf("No se encontró una ruta que conecte los paraderos de inicio y destino.\n");
    }

    // Liberar la memoria asignada para las rutas filtradas
    if (rutasFiltradas != NULL) {
        free(rutasFiltradas);
    }
}

*/

//-------------------------------------------------------------------------------------

void generarReporte(Ruta** rutas, int numRutas) {
    FILE *archivo = fopen("reporte.txt", "w");
    if (archivo == NULL) {
        perror("Error al abrir el archivo para el reporte");
        return;
    }

    fprintf(archivo, "Reporte de Rutas:\n");
    fprintf(archivo, "=================\n\n");

    for (int i = 0; i < numRutas; i++) {
        Ruta *ruta = rutas[i];
        fprintf(archivo, "Ruta del Bus: %d\n", ruta->busRuta);
        fprintf(archivo, "Número de Paraderos: %d\n", ruta->numParaderos);

        for (int j = 0; j < ruta->numParaderos; j++) {
            Paradero *paradero = ruta->paraderos[j];
            fprintf(archivo, "  Paradero: %s (Número: %d)\n", paradero->nombreParadero, paradero->numeroParadero);

            fprintf(archivo, "  Horarios de Llegada:\n");
            for (int k = 0; k < paradero->numHorarios; k++) {
                Horario *horario = paradero->horariosParadero[k];
                fprintf(archivo, "    Bus: %s, Hora de Llegada: %s\n", horario->numeroBus, horario->tiempoLlegada);
            }

            fprintf(archivo, "  Edges:\n");
            for (int e = 0; e < paradero->numEdges; e++) {
                Edge *edge = paradero->edges[e];
                fprintf(archivo, "    De: %s a %s, Distancia: %d\n",
                        edge->startNode->nombreParadero,
                        edge->endNode->nombreParadero,
                        edge->distancia);
            }
            fprintf(archivo, "\n");
        }
        fprintf(archivo, "---------------------------\n");
    }

    fclose(archivo);
    printf("Reporte generado con éxito en 'reporte.txt'.\n");
}

//-------------------------------------------------------------------------------------

void MenuAdmin(Graph *graph, Bus **buses, int *numBuses, Ruta** rutas, int* numRutas) {
    int opcion;
    int opcion2;
    do {
        MostrarMenuAdmin();
        opcion = obtenerOpcionValida(1, 5);
        printf("\n");

        switch (opcion) {
            case 1:
                limpiarPantalla();
                MostrarMenuParaderos();
                opcion2 = obtenerOpcionValida(1, 4);
                printf("\n");

                if (opcion2 == 1) {
                    listaDeParaderos(graph);
                    agregarParadero(graph);
                    limpiarPantalla();
                    printf("Paradero añadido correctamente.\n");
                } else if (opcion2 == 2) {
                    editarParadero(graph);
                    limpiarPantalla();
                } else if (opcion2 == 3) {
                    listaDeParaderos(graph);
                    limpiarPantalla();
                } else {
                    limpiarPantalla();
                }
                break;

            case 2:
                limpiarPantalla();
                MostrarMenuBuses();
                opcion2 = obtenerOpcionValida(1, 4);
                printf("\n");

                if (opcion2 == 1) {
                    listarBuses(buses, numBuses);
                    agregarBus(buses, numBuses);
                    limpiarPantalla();
                    printf("Bus añadido correctamente.\n");
                } else if (opcion2 == 2) {
                    editarBus(buses, numBuses);
                    limpiarPantalla();
                } else if (opcion2 == 3) {
                    listarBuses(buses, numBuses);
                    presioneTeclaParaContinuar();
                    limpiarPantalla();
                } else {
                    limpiarPantalla();
                }
                break;

            case 3:
                limpiarPantalla();
                MostrarMenuRutas();
                opcion2 = obtenerOpcionValida(1, 4);
                printf("\n");

                if (opcion2 == 1) {
                    agregarRutaBus(graph, rutas, numRutas);
                } else if (opcion2 == 2) {
                    editarRutaBus(graph, rutas, numRutas);
                } else if (opcion2 == 3) {
                    listarRutaBus(rutas, *numRutas);
                } else {
                    limpiarPantalla();
                }
                break;

            case 4:
                limpiarPantalla();
                MostrarMenuOtros();
                opcion2 = obtenerOpcionValida(1, 2);
                printf("\n");

                if (opcion2 == 1) {
                    generarReporte(rutas, *numRutas);
                } else {
                    limpiarPantalla();
                }
                break;
        }

    } while (opcion != 5); // Salir del do-while principal al elegir opción 5
    limpiarPantalla();
}

//-------------------------------------------------------------------------------------

void MenuUsuario(Graph *graph, Ruta** rutas, int* numRutas) {
  int opcion, opcion2, consulta;
  do {
    limpiarPantalla();
    MostrarMenuUsuarios();
    opcion = obtenerOpcionValida(1, 3);
    printf("\n");
    
    switch (opcion) {
    case 1: {
      limpiarPantalla();
      MostrarMenuTrayecto();
      opcion2 = obtenerOpcionValida(1,2);
      if (opcion == 1) {
        // planificarTrayecto();
      }
      break;
    }

    case 2: {
      limpiarPantalla();
      MostrarMenuConsultas();
      consulta = obtenerOpcionValida(1,4);
      if (consulta == 1) {
        consultaHorarioParada(graph);
      } else if (consulta == 2) {
        consultaHorarioRuta(rutas, numRutas);
      } else if (consulta == 3) {
        listaDeParaderos(graph);
      } else if (consulta == 4) {
        limpiarPantalla(); // Salir del submenú de paraderos
      } else {
        limpiarPantalla();
        MostrarMenuUsuarios();
      }
    }
      default:
       limpiarPantalla();
    }
  } while (opcion != 3);
  limpiarPantalla();
}

//-------------------------------------------------------------------------------------

void ingresoSesion(Map *usuarios, Graph* graph, Bus*** buses, int* numBuses, Ruta*** rutas, int* numRutas) {
      char usuario[50];
      char contrasena[50];

      MostrarIniciarSesion();
      while (true)
      {
        printf("\033[1;32m%s\033[0m\n","(Presione 0 para volver al menú principal)");
        printf("Ingrese su usuario: ");
        scanf("%49s", usuario);

          if (strcmp(usuario, "0") == 0) {
              limpiarPantalla();
              return; // Salir de la función si se ingresa "0"
          }
          if (contieneEspacios(usuario)) {
              printf("\033[1;31m%s\033[0m\n","El nombre de usuario no puede contener espacios en blanco.\n");
              while (getchar() != '\n'); // Limpiar el buffer de entrada
              continue;
          }
          

          int intentos = 0;
          bool usuarioEncontrado = false;

          while (true) {
              MapPair *pair = map_search(usuarios, usuario);
              if (pair != NULL) {
                  usuarioEncontrado = true;
                  while (intentos < 3) {
                      printf("Ingrese su contraseña: ");
                      scanf("%49s", contrasena);

                      if (checkPassword(usuario, contrasena, "data/usuarios.csv")) {
                          limpiarPantalla();
                          Usuario *usuarioEnc = pair->value;
                          if (usuarioEnc->esAdmin) {
                              MenuAdmin(graph, *buses, numBuses, *rutas, numRutas);
                          } else {
                              MenuUsuario(graph, *rutas, numRutas);
                          }
                          return;
                      } else {
                          printf("\nLa contraseña ingresada es incorrecta.\n");
                          printf("Intentos permitidos: %d\n\n", 2 - intentos);
                          intentos++;
                      }
                  }
                  limpiarPantalla();
                  printf("\033[1;31m%s\033[0m\n","Número de intentos excedido.");
                  return;
              } else {
                  if (!usuarioEncontrado) {
                      limpiarPantalla();
                      printf("\033[1;31m%s\033[0m\n","El usuario no existe.");
                      printf("\033[1;32m%s\033[0m\n","Seleccione la opción 2 del Menú Principal para registrarse.");
                      return;
                  } else {
                      printf("\nIntente con un usuario ya registrado:\n");
                      printf("Intentos permitidos: %d\n", 2 - intentos);
                      scanf("%49s", usuario);
                      intentos++;
                  }
              }
          }
      }
  }

//-------------------------------------------------------------------------------------

void registroUsuario(Map *usuarios) {
    MostrarRegistroUsuario();
    char nombre[50];
    char contrasena[50];
    char opcion;
  printf("\033[1;32m%s\033[0m\n", "(Presione 0 para volver al menú principal)");

    while (true) {
        printf("Ingrese su usuario: ");
        scanf(" %49[^\n]", nombre); // Leer hasta que se encuentre un salto de línea

        if (strcmp(nombre, "0") == 0) {
            limpiarPantalla();
            return;
        }
        // Verificar si el nombre contiene espacios en blanco
        if (contieneEspacios(nombre)) {
            printf("\033[1;31m%s\033[0m\n","El nombre de usuario no puede"
                                        "contener espacios en blanco.\n");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }
        if (strlen(nombre) > 50) {
            printf("\033[1;31m%s\033[0m\n","El nombre de usuario no puede"
                                        "contener más de 50 caracteres.\n");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }

        if (map_search(usuarios, nombre) != NULL) {
            printf("\033[1;31m%s\033[0m\n","\nEl usuario ya existe."
            "\nPor favor, elija otro nombre de usuario o inicie sesión.\n");
            continue;
        }

        printf("Ingrese su contraseña: ");
        scanf(" %49[^\n]", contrasena); // Leer hasta que se encuentre un salto de línea

        // Verificar si la contraseña contiene espacios en blanco
        if (contieneEspacios(contrasena)) {
            printf("\033[1;32m%s\033[0m\n","La contraseña no puede contener"
                "espacios en blanco. Por favor, inténtelo nuevamente.\n");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }

        if (strlen(contrasena) > 50) {
          printf("\033[1;31m%s\033[0m\n","La contraseña no puede contener"
                                                "más de 50 caracteres.\n");
          while (getchar() != '\n' ); // Limpiar el buffer de entrada
          continue;
        }

        Usuario* nuevoUsuario = (Usuario*)malloc(sizeof(Usuario));
        strcpy(nuevoUsuario->nombre, nombre);
        nuevoUsuario->esAdmin = false;

        map_insert(usuarios, nuevoUsuario->nombre, nuevoUsuario);

        FILE *archivo = fopen("data/usuarios.csv", "a");
        if (archivo != NULL) {
            fprintf(archivo, "%s,%s,%d\n", nuevoUsuario->nombre, contrasena,
                    nuevoUsuario->esAdmin ? 1 : 0);
            fclose(archivo);
        } else {
            perror("Error al abrir el archivo de usuarios.csv");
        }
        limpiarPantalla();
        printf("\033[1;32m%s\033[0m\n", "Usuario registrado exitosamente.\n");
        break; // Salir del bucle de registro
    }
}

//-------------------------------------------------------------------------------------

void mostrarIngreso(Map* MapUsuarios, Graph* graph, Bus** buses,
                    int* numBuses, Ruta** rutas, int* numRutas)
{
    char input[10];
    int opcion;
    int isNumber;

    do {
        MostrarMenuPrincipal();
        scanf(" %s", input);
        if (strlen(input) == 1 && isdigit(input[0]))
            opcion = input[0] - '0';
        else
            opcion = -1;

        switch (opcion) {
        case 1:
            limpiarPantalla();
            ingresoSesion(MapUsuarios, graph, &buses, numBuses, &rutas, numRutas);
            break;
        case 2:
            limpiarPantalla();
            registroUsuario(MapUsuarios);
            break;
        case 3:
            printf("\nSaliendo del sistema...\n");
            break;
        default:
            limpiarPantalla();
            printf("Por favor, ingrese una opción válida.\n");
        }
    } while (opcion != 3);
    
    for (int i = 0; i < graph->numNodes; i++) {
        free(graph->nodes[i]->horariosParadero);
        free(graph->nodes[i]);
    }
    free(graph->nodes);
    free(graph);
}

//-------------------------------------------------------------------------------------

int main() {
    sqlite3* db; 
    int exit = 0; 
    exit = sqlite3_open("database.db", &db); 
    
    if (exit)
        printf("Error al abrir la DB\n");
    else {
        printf("** BASE DE DATOS CONECTADA **\n");
        sqlite3_close(db); 
    }
    
    Bus** buses = (Bus **)malloc(100 * sizeof(Bus));
    int numBuses = 0;

    Ruta** rutas = (Ruta **)malloc(100 * sizeof(Ruta));
    int numRutas = 0;

    Graph* graph = (Graph *)malloc(sizeof(Graph));
    graph->nodes = (Paradero **)malloc(100 * sizeof(Paradero *));
    graph->numNodes = 0;
    
    if (!isCSVFileEmpty("data/buses.csv")) {
      buses = cargarBuses(buses, &numBuses);
    }
    
    /*
    if (!isCSVFileEmpty("data/rutas.csv")) {
       //rutas = cargarRutas(rutas, &numRutas);
    }

    // Como los paraderos son los nodos, se puebla el grafo con los paraderos
    
    if (!isCSVFileEmpty("data/paraderos.csv")) {
      graph->nodes = cargarParaderos(graph->nodes, &graph->numNodes);
    }
    */
    
    Map *MapUsuarios = map_create(is_equal_str);
    cargarUsuarios(MapUsuarios);
    mostrarIngreso(MapUsuarios, graph, buses, &numBuses, rutas, &numRutas);
    
    return 0;
}