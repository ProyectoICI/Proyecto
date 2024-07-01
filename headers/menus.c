#include "menus.h"
#include "extras.h"
#include "paraderos.h"
#include "buses.h"
#include "rutas.h"
#include "consultas.h"
#include "../tdas/extra.h"
#include "../tdas/map.h"

#include <stdio.h> 
#include <stdbool.h>
#include <ctype.h>

typedef struct Paradero Paradero; 
typedef struct Edge Edge;  


typedef struct Horario { 
  char numeroBus[50];    
  char tiempoLlegada[6]; 
} Horario;

typedef struct Usuario { 
    char nombre[50];    
    bool esAdmin;       
} Usuario; 

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

typedef struct Graph {   
    Paradero** nodes;    
    int numNodes;        
} Graph; 

//----------------Menu General----------------------------

void MostrarMenuPrincipal() {
  printf("========================================\n");
  printf("   \033[1mSISTEMA DE BUSES\033[0m 🚌\n");
  printf("========================================\n");
  printf("1) Iniciar Sesión\n");
  printf("2) Registrarse\n");
  printf("3) Salir\n");
  printf("\n\033[1mEscoja una opción:\033[0m\n");
}

void MostrarIniciarSesion() {
  printf("========================================\n");
  printf("   \033[1mINICIAR SESIÓN\033[0m\n");
  printf("========================================\n");
}

void MostrarRegistroUsuario() {
  printf("========================================\n");
  printf("   \033[1mREGISTRO DE USUARIO\033[0m\n");
  printf("========================================\n");
}


//----------------Menu Usuarios----------------------------

void MostrarMenuAdmin() {
  printf("========================================\n");
  printf("   \033[1mMENU ADMINISTRADOR\033[0m\n");
  printf("========================================");
  printf("\n1) Paraderos");
  printf("\n2) Buses");
  printf("\n3) Rutas");
  printf("\n4) Otros");
  printf("\n5) Cerrar Sesión"); 
  printf("\n========================================\n");
  printf("\n\033[1mEscoja una opción:\033[0m\n");
}

void MostrarMenuParaderos() {
  printf("========================================\n");
  printf("   \033[1mMENU PARADEROS\033[0m\n");
  printf("========================================");
  printf("\n1) Agregar Paradero");
  printf("\n2) Editar Paradero");
  printf("\n3) Listar Paraderos");
  printf("\n4) Volver a Menú Administrador");
  printf("\n========================================\n");
  printf("\n\033[1mEscoja una opción:\033[0m\n");
}

void MostrarMenuBuses() {
  printf("========================================\n");
  printf("   \033[1mMENU BUSES\033[0m\n");
  printf("========================================");
  printf("\n1) Agregar Bus");
  printf("\n2) Editar Bus");
  printf("\n3) Listar Buses");
  printf("\n4) Volver a Menú Administrador");
  printf("\n========================================\n");
  printf("\n\033[1mEscoja una opción:\033[0m\n");
}

void MostrarMenuRutas() {
  printf("========================================\n");
  printf("   \033[1mMENU RUTAS\033[0m\n");
  printf("========================================");
  printf("\n1) Agregar Ruta de Bus");
  printf("\n2) Editar Ruta de Bus");
  printf("\n3) Listar Rutas de Bus");
  printf("\n4) Volver a Menú Administrador");
  printf("\n========================================\n");
  printf("\n\033[1mEscoja una opción:\033[0m\n");
}

void MostrarMenuOtros() {
  printf("========================================\n");
  printf("   \033[1mMENU OTROS\033[0m\n");
  printf("========================================");
  printf("\n1) Generar Reporte de Uso");
  printf("\n2) Volver a Menú Administrador");
  printf("\n========================================\n");
  printf("\n\033[1mEscoja una opción:\033[0m\n");
}


//----------------Menu Usuarios----------------------------

void MostrarMenuUsuarios() {
  printf("========================================\n");
  printf("   \033[1mMENU USUARIOS\033[0m\n");
  printf("========================================");
  printf("\n1) Trayectos");
  printf("\n2) Consultas");
  printf("\n3) Cerrar Sesión");
  printf("\n========================================\n");
  printf("\n\033[1mEscoja una opción:\033[0m\n");

}

void MostrarMenuTrayecto() {
  printf("========================================\n");
  printf("   \033[1mMENU TRAYECTOS\033[0m\n");
  printf("========================================");
  printf("\n1) Planificar Trayecto");
  printf("\n2) Salir");
  printf("\n========================================\n"); 
  printf("\n\033[1mEscoja una opción:\033[0m\n");
}

void MostrarMenuConsultas() {
  printf("========================================\n");
  printf("   \033[1mMENU CONSULTAS\033[0m\n");
  printf("========================================");
  printf("\n1) Consulta Horarios por Parada");
  printf("\n2) Consulta Horarios por Ruta");
  printf("\n3) Consulta Paraderos");
  printf("\n4) Salir");
  printf("\n========================================\n");
  printf("\n\033[1mEscoja una opción:\033[0m\n");
}


//----------------Edición de entidades----------------------------

void MostrarMenuEditarBus() {
  printf("========================================\n");
  printf("   \033[1mEDITAR BUS\033[0m\n");
  printf("========================================");
  printf("\n1) Número de bus");
  printf("\n2) Eliminar bus ");
  printf("\n3) Salir");
  printf("\n========================================\n");
}

void MostrarMenuEditar() {
  printf("========================================\n");
  printf("   \033[1mEDITAR PARADERO\033[0m\n");
  printf("========================================");
  printf("\n1) Nombre del paradero");
  printf("\n2) Eliminar paradero ");
  printf("\n3) Salir");
  printf("\n========================================\n");
}

void MostrarMenuEditarRuta() {
  printf("========================================\n");
  printf("   \033[1mEDITAR RUTA\033[0m\n");
  printf("========================================");
  printf("\n1) Número de bus");
  printf("\n2) Paraderos");
  printf("\n3) Distancia entre paraderos");
  printf("\n4) Tiempo de partida y llegada");
  printf("\n5) Eliminar ruta ");
  printf("\n6) Salir");
  printf("\n========================================\n");
}


//-------------------------------------------------------------------------------------

void MenuAdmin(Graph *graph, Bus **buses, int *numBuses, Ruta** rutas, int* numRutas, sqlite3* db) {
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
                    agregarParadero(db, graph);
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
                    agregarBus(db, &buses, numBuses);
                    limpiarPantalla();
                    printf("Bus añadido correctamente.\n");
                } else if (opcion2 == 2) {
                    editarBus(db, buses, numBuses);
                    limpiarPantalla();
                } else if (opcion2 == 3) {
                    listarBuses(buses, numBuses);
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
                    agregarRutaBus(db, graph, rutas, numRutas);
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

    } while (opcion != 5); 
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
       planificarTrayecto(graph, rutas, *numRutas); 
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
        limpiarPantalla(); 
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

void ingresoSesion(sqlite3 *db, Graph* graph, Bus*** buses, int* numBuses, Ruta*** rutas, int* numRutas) {
  char usuario[50];
  char contrasena[50];

  MostrarIniciarSesion();

  while (true) {
      printf("\033[1;32m%s\033[0m\n", "(Presione 0 para volver al menú principal)");
      printf("Ingrese su usuario: ");
      scanf("%49s", usuario);

      if (strcmp(usuario, "0") == 0) {
          limpiarPantalla();
          return; 
      }
      if (contieneEspacios(usuario)) {
          printf("\033[1;31m%s\033[0m\n", "El nombre de usuario no puede contener espacios en blanco.\n");
          while (getchar() != '\n'); 
          continue;
      }

      printf("Ingrese su contraseña: ");
      scanf("%49s", contrasena);

      const char *sql = "SELECT isAdmin FROM Users WHERE Name = ? AND Password = ?";
      sqlite3_stmt *stmt;
      if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
          sqlite3_bind_text(stmt, 1, usuario, -1, SQLITE_STATIC);
          sqlite3_bind_text(stmt, 2, contrasena, -1, SQLITE_STATIC);

          if (sqlite3_step(stmt) == SQLITE_ROW) {
              limpiarPantalla();
              bool esAdmin = sqlite3_column_int(stmt, 0);
              if (esAdmin) {
                  MenuAdmin(graph, *buses, numBuses, *rutas, numRutas, db);
              } else {
                  MenuUsuario(graph, *rutas, numRutas);
              }
              sqlite3_finalize(stmt);
              return;
          } else {
              limpiarPantalla();
              printf("\033[1;31m%s\033[0m\n", "Usuario o contraseña incorrectos.");
              sqlite3_finalize(stmt);

              return;
          }
      } else {
          fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
      }
      sqlite3_finalize(stmt); 
  }
}

//-------------------------------------------------------------------------------------

void registroUsuario(Map *usuarios, sqlite3 *db) {
  MostrarRegistroUsuario();
  char nombre[50];
  char contrasena[50];
  printf("\033[1;32m%s\033[0m\n", "(Presione 0 para volver al menú principal)");

  while (true) {
      printf("Ingrese su usuario: ");
      scanf(" %49[^\n]", nombre); 

      if (strcmp(nombre, "0") == 0) {
          limpiarPantalla();
          return;
      }

      if (contieneEspacios(nombre) || strlen(nombre) > 50) {
          printf("\033[1;31m%s\033[0m\n", "El nombre de usuario no puede contener espacios en blanco ni más de 50 caracteres.\n");
          while (getchar() != '\n'); 
          continue;
      }

      if (map_search(usuarios, nombre) != NULL) {
          printf("\033[1;31m%s\033[0m\n", "\nEl usuario ya existe.\nPor favor, elija otro nombre de usuario o inicie sesión.\n");
          continue;
      }

      printf("Ingrese su contraseña: ");
      scanf(" %49[^\n]", contrasena);

      if (contieneEspacios(contrasena) || strlen(contrasena) > 50) {
          printf("\033[1;31m%s\033[0m\n", "La contraseña no puede contener espacios en blanco ni más de 50 caracteres.\n");
          while (getchar() != '\n');
          continue;
      }

      Usuario* nuevoUsuario = (Usuario*)malloc(sizeof(Usuario));
      strcpy(nuevoUsuario->nombre, nombre);
      nuevoUsuario->esAdmin = false;
      map_insert(usuarios, nuevoUsuario->nombre, nuevoUsuario);


      const char *sql = "INSERT INTO Users (Name, Password, isAdmin) VALUES (?, ?, ?)";
      sqlite3_stmt *stmt;
      if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

          sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);
          sqlite3_bind_text(stmt, 2, contrasena, -1, SQLITE_STATIC);
          sqlite3_bind_int(stmt, 3, nuevoUsuario->esAdmin ? 1 : 0);

          if (sqlite3_step(stmt) != SQLITE_DONE) {
              printf("Error al registrar el usuario: %s\n", sqlite3_errmsg(db));
          } else {
              printf("\033[1;32m%s\033[0m\n", "Usuario registrado exitosamente.\n");
          }
          sqlite3_finalize(stmt);
      } else {
          fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
      }

      limpiarPantalla();
      break; 
  }
}

//-------------------------------------------------------------------------------------

void mostrarIngreso(Map* MapUsuarios, Graph* graph, Bus** buses,
                  int* numBuses, Ruta** rutas, int* numRutas, sqlite3* db)
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
          ingresoSesion(db, graph, &buses, numBuses, &rutas, numRutas);
          break;
      case 2:
          limpiarPantalla();
          registroUsuario(MapUsuarios, db);
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