#include "../tdas/extra.h"
#include "menus.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sqlite3.h>

//-------------------------------------------------------------------------------------

typedef struct Paradero Paradero;  
typedef struct Edge Edge;  

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

typedef struct Graph {
    Paradero** nodes; 
    int numNodes;  
} Graph;

typedef struct Ruta {
    int busRuta;
    Paradero** paraderos;
    int numParaderos;
} Ruta;

//---------------------------- FUNCIONES AUXILIARES ------------------------------------

void updateDistance(Graph *graph, int startNumber, int endNumber, int newDistance) {
    for (int i = 0; i < graph->numNodes; i++) {
        if (graph->nodes[i]->numeroParadero == startNumber) {
            for (int j = 0; j < graph->nodes[i]->numEdges; j++) {
                if (graph->nodes[i]->edges[j]->endNode->numeroParadero == endNumber) {
                    graph->nodes[i]->edges[j]->distancia = newDistance;
                    return;
                }
            }
        }
    }
}

void updateSchedule(Graph *graph, int startNumber, char *newSchedule) {
    for (int i = 0; i < graph->numNodes; i++) {
        if (graph->nodes[i]->numeroParadero == startNumber) {
            for (int j = 0; j < graph->nodes[i]->numHorarios; j++) {
                strcpy((*graph->nodes[i]->horariosParadero[j]).tiempoLlegada, newSchedule);
                return;
            }
        }
    }
}

//-------------------------------------------------------------------------------------


void agregarRutaBus(sqlite3* db, Graph *graph, Ruta **rutas, int *numRutas) {
  int busNumber, startNumber, endNumber, distancia, numTrayectos;
  char tiempoLlegada[6]; 
  char tiempoPartida[6];
  printf("Ingrese el bús que realizará la ruta: ");
  scanf("%d", &busNumber);
  printf("Ingrese la cantidad de trayectos en la ruta: ");
  scanf("%d", &numTrayectos);

  Ruta *newRuta = (Ruta *)malloc(sizeof(Ruta));
  newRuta->busRuta = busNumber;
  newRuta->paraderos = (Paradero **)malloc((numTrayectos + 1) * sizeof(Paradero *));
  newRuta->numParaderos = 0;
    
  //--------------------- SE INSERTA LA RUTA EN LA BASE DE DATOS --------------------------------
    
  const char *sqlInsertRoute = "INSERT INTO Routes (BusID, numParaderos) VALUES (?, ?)";
  sqlite3_stmt *stmtInsertRoute;
  sqlite3_prepare_v2(db, sqlInsertRoute, -1, &stmtInsertRoute, NULL);
  sqlite3_bind_int(stmtInsertRoute, 1, busNumber);
  sqlite3_bind_int(stmtInsertRoute, 2, numTrayectos + 1);
  if (sqlite3_step(stmtInsertRoute) != SQLITE_DONE) {
      printf("Failed to insert route\n");
  }
  sqlite3_finalize(stmtInsertRoute);

  //-------------------------------------------------------------------------------------


  int routeID = (int)sqlite3_last_insert_rowid(db);

  for (int i = 0; i < numTrayectos; i++) {

      Paradero *startParadero = NULL;
      Paradero *endParadero = NULL;

      printf("Ingrese el número del paradero de inicio: ");
      scanf("%d", &startNumber);

      for (int i = 0; i < graph->numNodes; i++) {
          if (graph->nodes[i]->numeroParadero == startNumber) {
              startParadero = graph->nodes[i];
          } 
      }

      if (startParadero == NULL) {
          printf("El paradero de inicio no se encontró.\n");
          return;
      }

      /* ------------------- SE BUSCA EL ID DEL PARADERO INICIO ----------------------------- */

      const char *sqlFetchStartParaderoID = "SELECT ParaderoID FROM Paraderos WHERE Number = ?";
      sqlite3_stmt *stmtFetchStartParadero;
      int startParaderoID;

      sqlite3_prepare_v2(db, sqlFetchStartParaderoID, -1, &stmtFetchStartParadero, NULL);

      sqlite3_bind_int(stmtFetchStartParadero, 1, startNumber);

      if (sqlite3_step(stmtFetchStartParadero) == SQLITE_ROW) {
          startParaderoID = sqlite3_column_int(stmtFetchStartParadero, 0);
      } else {
          printf("Failed to find start paradero ID\n");
      }

      sqlite3_finalize(stmtFetchStartParadero);

      //-------------------------------------------------------------------------------------


      printf("Ingrese el número del paradero de destino: ");
      scanf("%d", &endNumber);

      for (int i = 0; i < graph->numNodes; i++) {
          if (graph->nodes[i]->numeroParadero == endNumber) {
              endParadero = graph->nodes[i];
          } 
      }

      if (endParadero == NULL) {
          printf("El paradero de destino no se encontró.\n");
          return;
      }

      /* ------------------- SE BUSCA EL ID DEL PARADERO DESTINO ----------------------------- */

      
      const char *sqlFetchEndParaderoID = "SELECT ParaderoID FROM Paraderos WHERE Number = ?";
      sqlite3_stmt *stmtFetchEndParadero;
      int endParaderoID;

      sqlite3_prepare_v2(db, sqlFetchEndParaderoID, -1, &stmtFetchEndParadero, NULL);
      
      sqlite3_bind_int(stmtFetchEndParadero, 1, endNumber);

      if (sqlite3_step(stmtFetchEndParadero) == SQLITE_ROW) {
          endParaderoID = sqlite3_column_int(stmtFetchEndParadero, 0);
      } else {
          printf("Failed to find end paradero ID\n");
      }

      sqlite3_finalize(stmtFetchEndParadero);

      //-------------------------------------------------------------------------------------


      printf("Ingrese la distancia entre los paraderos (en metros): ");
      scanf("%d", &distancia);

      printf("Ingrese el tiempo de partida al paradero de inicio (HH:MM): ");
      scanf("%s", tiempoPartida);
      printf("Ingrese el tiempo de llegada al paradero de destino (HH:MM): ");
      scanf("%s", tiempoLlegada);

      /* ------------------- SE PUEBLAN LOS DATOS EN LA MEMORIA ----------------------------- */


      Edge *newEdgeStartToEnd = (Edge *)malloc(sizeof(Edge));
      newEdgeStartToEnd->startNode = startParadero;
      newEdgeStartToEnd->endNode = endParadero;
      newEdgeStartToEnd->distancia = distancia;

      startParadero->edges = (Edge **)realloc(startParadero->edges, (startParadero->numEdges + 2) * sizeof(Edge *));
      startParadero->edges[startParadero->numEdges] = newEdgeStartToEnd;
      startParadero->numEdges++;

      Edge *newEdgeEndToStart = (Edge *)malloc(sizeof(Edge));
      newEdgeEndToStart->startNode = endParadero;
      newEdgeEndToStart->endNode = startParadero;
      newEdgeEndToStart->distancia = distancia;

      endParadero->edges = (Edge **)realloc(endParadero->edges, (endParadero->numEdges + 2) * sizeof(Edge *));
      endParadero->edges[endParadero->numEdges] = newEdgeEndToStart;
      endParadero->numEdges++;

      /* ------------------- SE INSERTAN LOS BORDES EN LA BASE DE DATOS ----------------------------- */

      
      const char *sqlInsertEdge = "INSERT INTO Edges (StartParaderoID, EndParaderoID, Distance) VALUES (?, ?, ?)";
      sqlite3_stmt *stmtInsertEdge;

      sqlite3_prepare_v2(db, sqlInsertEdge, -1, &stmtInsertEdge, NULL);
      sqlite3_bind_int(stmtInsertEdge, 1, startParaderoID);
      sqlite3_bind_int(stmtInsertEdge, 2, endParaderoID);
      sqlite3_bind_int(stmtInsertEdge, 3, distancia);
      if (sqlite3_step(stmtInsertEdge) != SQLITE_DONE) {
          printf("Failed to insert edge\n");
      }
      sqlite3_reset(stmtInsertEdge); 

      sqlite3_bind_int(stmtInsertEdge, 1, endParaderoID);
      sqlite3_bind_int(stmtInsertEdge, 2, startParaderoID);
      sqlite3_bind_int(stmtInsertEdge, 3, distancia);
      if (sqlite3_step(stmtInsertEdge) != SQLITE_DONE) {
          printf("Failed to insert reverse edge\n");
      }
      sqlite3_finalize(stmtInsertEdge); 

      /* ------------------ SE ACTUALIZAN LA CANT. BORDES EN LA BASE DE DATOS ------------------- */
      
      const char *sqlUpdateStartParadero = "UPDATE Paraderos SET numEdges = numEdges + 1 WHERE ParaderoID = ?";
      sqlite3_stmt *stmtUpdateStartParadero;
      sqlite3_prepare_v2(db, sqlUpdateStartParadero, -1, &stmtUpdateStartParadero, NULL);
      sqlite3_bind_int(stmtUpdateStartParadero, 1, startParaderoID);
      if (sqlite3_step(stmtUpdateStartParadero) != SQLITE_DONE) {
          printf("Failed to update start paradero\n");
      }
      sqlite3_finalize(stmtUpdateStartParadero); 

      const char *sqlUpdateEndParadero = "UPDATE Paraderos SET numEdges = numEdges + 1 WHERE ParaderoID = ?";
      sqlite3_stmt *stmtUpdateEndParadero;
      sqlite3_prepare_v2(db, sqlUpdateEndParadero, -1, &stmtUpdateEndParadero, NULL);
      sqlite3_bind_int(stmtUpdateEndParadero, 1, endParaderoID);
      if (sqlite3_step(stmtUpdateEndParadero) != SQLITE_DONE) {
          printf("Failed to update end paradero\n");
      }
      sqlite3_finalize(stmtUpdateEndParadero); 

      /* ------------------------------ SE ACTUALIZA EN MEMORIA -------------------------------- */

      newRuta->paraderos[newRuta->numParaderos] = startParadero;
      newRuta->numParaderos++;
      newRuta->paraderos[newRuta->numParaderos] = endParadero;
      newRuta->numParaderos++;

      Horario *horarioPartida = (Horario *)malloc(sizeof(Horario));
      strcpy(horarioPartida->tiempoLlegada, tiempoPartida);
      if (startParadero->horariosParadero == NULL) {
          startParadero->horariosParadero = (Horario **)malloc(sizeof(Horario *) * 100); 
          startParadero->numHorarios = 0;
      }
      startParadero->horariosParadero[startParadero->numHorarios] = horarioPartida;
      startParadero->numHorarios++;

      Horario *horarioLlegada = (Horario *)malloc(sizeof(Horario));
      strcpy(horarioLlegada->tiempoLlegada, tiempoLlegada);
      if (endParadero->horariosParadero == NULL) {
          endParadero->horariosParadero = (Horario **)malloc(sizeof(Horario *) * 100); 
          endParadero->numHorarios = 0;
      }
      
      endParadero->horariosParadero[endParadero->numHorarios] = horarioLlegada;
      endParadero->numHorarios++;

        /* ----------------- SE ACTUALIZA LA CANT. DE HORARIOS EN LA BASE DE DATOS ------------------ */

      const char *sqlUpdateStartParaderoHorarios = "UPDATE Paraderos SET numHorarios = numHorarios + 1 WHERE ParaderoID = ?";
      sqlite3_stmt *stmtUpdateStartParaderoHorarios;
      sqlite3_prepare_v2(db, sqlUpdateStartParaderoHorarios, -1, &stmtUpdateStartParaderoHorarios, NULL);
      sqlite3_bind_int(stmtUpdateStartParaderoHorarios, 1, startParaderoID);
      if (sqlite3_step(stmtUpdateStartParaderoHorarios) != SQLITE_DONE) {
          printf("Failed to update numHorarios for start paradero\n");
      }
      sqlite3_finalize(stmtUpdateStartParaderoHorarios); 

      const char *sqlUpdateEndParaderoHorarios = "UPDATE Paraderos SET numHorarios = numHorarios + 1 WHERE ParaderoID = ?";
      sqlite3_stmt *stmtUpdateEndParaderoHorarios;
      sqlite3_prepare_v2(db, sqlUpdateEndParaderoHorarios, -1, &stmtUpdateEndParaderoHorarios, NULL);
      sqlite3_bind_int(stmtUpdateEndParaderoHorarios, 1, endParaderoID);
      if (sqlite3_step(stmtUpdateEndParaderoHorarios) != SQLITE_DONE) {
          printf("Failed to update numHorarios for end paradero\n");
      }
      sqlite3_finalize(stmtUpdateEndParaderoHorarios);

      /* ----------------------- SE INSERTAN LOS HORARIOS EN LA BASE DE DATOS ------------------------ */

      const char *sqlInsertHorario = "INSERT INTO Horarios (ParaderoID, BusID, ArrivalTime) VALUES (?, ?,?)";
      sqlite3_stmt *stmtInsertHorario;

      sqlite3_prepare_v2(db, sqlInsertHorario, -1, &stmtInsertHorario, NULL);
      sqlite3_bind_int(stmtInsertHorario, 1, startParaderoID);
      sqlite3_bind_int(stmtInsertHorario, 2, busNumber);
      sqlite3_bind_text(stmtInsertHorario, 3, tiempoPartida, -1, SQLITE_STATIC);
      if (sqlite3_step(stmtInsertHorario) != SQLITE_DONE) {
          printf("Failed to insert horario partida\n");
      }
      sqlite3_reset(stmtInsertHorario); 

      sqlite3_bind_int(stmtInsertHorario, 1, endParaderoID);
      sqlite3_bind_int(stmtInsertHorario, 2, busNumber);
      sqlite3_bind_text(stmtInsertHorario, 3, tiempoLlegada, -1, SQLITE_STATIC);
      if (sqlite3_step(stmtInsertHorario) != SQLITE_DONE) {
          printf("Failed to insert horario llegada\n");
      }
      sqlite3_finalize(stmtInsertHorario); 

      const char *sqlInsertRouteParadero = "INSERT INTO RouteParaderos (RouteID, ParaderoID) VALUES (?,?) ";
      sqlite3_stmt *stmtInsertRouteParadero;
      sqlite3_prepare_v2(db, sqlInsertRouteParadero, -1, &stmtInsertRouteParadero, NULL);

      sqlite3_bind_int(stmtInsertRouteParadero, 1, routeID);
      sqlite3_bind_int(stmtInsertRouteParadero, 2, startParaderoID); 

      if (sqlite3_step(stmtInsertRouteParadero) != SQLITE_DONE) {
          printf("Failed to link paradero to route\n");
      }

      sqlite3_reset(stmtInsertRouteParadero);
      sqlite3_bind_int(stmtInsertRouteParadero, 1, routeID);
      sqlite3_bind_int(stmtInsertRouteParadero, 2, endParaderoID); 
      if (sqlite3_step(stmtInsertRouteParadero) != SQLITE_DONE) {
          printf("Failed to link paradero to route\n");
      }
      sqlite3_finalize(stmtInsertRouteParadero);

        /* ------------------------------------------------------------------------------------ */


  }

  rutas[*numRutas] = newRuta;
  (*numRutas)++;


  printf("Ruta agregada con éxito.\n");
}

/* ------------------ TODO: CASO N°2 ----------------- */
void editarRutaBus(Graph *graph, Ruta **rutas, int *numRutas) {
    int busNumber, option, startNumber, endNumber, distancia, rutaIndex = -1;
    char tiempoLlegada[6]; 
    char tiempoPartida[6]; 

    printf("Ingrese el número del bus de la ruta a editar: ");
    scanf("%d", &busNumber);

    for (int i = 0; i < *numRutas; i++) {
        if (rutas[i]->busRuta == busNumber) {
            rutaIndex = i;
            break;
        }
    }

    if (rutaIndex == -1) {
        printf("Ruta no encontrada.\n");
        return;
    }

    MostrarMenuEditarRuta();
    scanf("%d", &option);
    
    switch (option) {
        case 1:
            printf("Ingrese el nuevo número de bus: ");
            scanf("%d", &busNumber);
            rutas[rutaIndex]->busRuta = busNumber;
            printf("Número de bus actualizado.\n");
            break;
        case 2:
            printf("Funcionalidad para editar paraderos no implementada.\n");
            // Aquí se implementaría la lógica para editar paraderos
            break;
        case 3:
            printf("Ingrese el número del paradero de inicio: ");
            scanf("%d", &startNumber);
            printf("Ingrese el número del paradero de destino: ");
            scanf("%d", &endNumber);
            printf("Ingrese la nueva distancia entre los paraderos (en metros): ");
            scanf("%d", &distancia);

            updateDistance(graph, startNumber, endNumber, distancia);

            printf("Distancia actualizada.\n");
            break;
        case 4:
            printf("Ingrese el número del paradero: ");
            scanf("%d", &startNumber);
            printf("Ingrese el tiempo de partida al paradero (HH:MM): ");
            scanf("%s", tiempoLlegada);

            updateSchedule(graph, startNumber, tiempoLlegada);

            printf("Tiempos actualizados.\n");
            break;
        case 5:
            //eliminarRuta();
        case 6:
            limpiarPantalla();
            MostrarMenuRutas();
        default:
            printf("Opción no válida.\n");
            break;
    }
}

void listarRutaBus(Ruta **rutas, int numRutas) {
  printf("Listado de Rutas:\n");
  for (int i = 0; i < numRutas; i++) {
      Ruta *ruta = rutas[i];
      printf("Ruta %d: Bus %d\n", i + 1, ruta->busRuta);
      printf("Número de Paraderos: %d\n", ruta->numParaderos);
      for (int j = 0; j < ruta->numParaderos; j++) {
          Paradero *paradero = ruta->paraderos[j];
          printf("  Paradero %d: %d\n", j + 1, paradero->numeroParadero);
          printf("    Horarios:\n");
          for (int k = 0; k < paradero->numHorarios; k++) {
              printf("      %s\n", paradero->horariosParadero[k]->tiempoLlegada);
          }
      }
  }
}

//-------------------------------------------------------------------------------------
/*
void planificarTrayecto(Graph *graph, Ruta **rutas, int numRutas)
{
    Paradero *paraderoInicio = NULL;
    Paradero *paraderoFin = NULL;
    int paraderoSubida; 
    int paraderoBajada; 
    char hora; 
    int seEncontroHora = 0; 
    

    printf("Ingrese el numero del paradero de inicio: ");
    scanf("%d", &paraderoSubida);
    printf("\nIngrese el numero del paradero de destino: ");
    scanf("%d", &paraderoBajada);
    int x = 0;
    
    for (int i = 0; i < graph->numNodes && x != 2; i++)
        {  
            if (graph->nodes[i]->numeroParadero == paraderoSubida)
            {
                x++;
                paraderoInicio = graph->nodes[i];
                
            }
                
            
            if (graph->nodes[i]->numeroParadero == paraderoBajada)
            {
                paraderoFin = graph->nodes[i];
                x++;
            }      
        }
    if (x == 2)
    {
        printf("\nIngrese horario de salida en formato HH:MM : ");
        scanf("%s", &hora);
        for (int i = 0; i < paraderoInicio->numHorarios; i++)
        {
            if (strcmp(paraderoInicio->horariosParadero[i]->tiempoLlegada, &hora) == 0) 
            {
                seEncontroHora = 1;
                char *numeroBusT = paraderoInicio->horariosParadero[i]->numeroBus;
                printf("\nBus a tomar: %s", numeroBusT);
                
                for (int k = 0; k < numRutas; k++)
                    {
                        Ruta *ruta = rutas[k];
                        if (ruta->busRuta == atoi(numeroBusT))
                        {
                            for (x = 0; x< ruta->numParaderos; x++)
                                {
                                    if (ruta->paraderos[x]->numeroParadero == paraderoBajada)  
                                        printf("\nRuta encontrada!! Bus a tomar : %d\n",  ruta->busRuta);
                                }
                            
                                
                        }
                    }
            }
            else{
                printf("\nNo se encontro el horario de salida");
                presioneTeclaParaContinuar();
            }
            
                    
        }
        if (seEncontroHora == 0) printf("No se encontro ningun bus con ese horario en el paradero de salida\n");

    }
    else
    {
        printf("No se encontro el paradero de inicio o destino\n");
        presioneTeclaParaContinuar();
        return;
    }
        

    return;
}
*/
//-------------------------------------------------------------------------------------
void planificarTrayecto(Graph *graph, Ruta **rutas, int numRutas)
{
    Paradero *paraderoInicio = NULL;
    Paradero *paraderoFin = NULL;
    int paraderoSubida; 
    int paraderoBajada; 
    char hora[6]; // Asegúrate de que 'hora' sea un array de caracteres
    int seEncontroHora = 0; 


    printf("Ingrese el numero del paradero de inicio: ");
    scanf("%d", &paraderoSubida);
    printf("\nIngrese el numero del paradero de destino: ");
    scanf("%d", &paraderoBajada);
    int x = 0;

    for (int i = 0; i < graph->numNodes && x != 2; i++)
        {  
            if (graph->nodes[i]->numeroParadero == paraderoSubida)
            {
                x++;
                paraderoInicio = graph->nodes[i];

            }


            if (graph->nodes[i]->numeroParadero == paraderoBajada)
            {
                paraderoFin = graph->nodes[i];
                x++;
            }      
        }
    if (x == 2)
    {
        printf("\nIngrese horario de salida en formato HH:MM : ");
        scanf("%5s", hora); // Asegúrate de leer un máximo de 5 caracteres
        for (int i = 0; i < paraderoInicio->numHorarios; i++)
        {
            if (strcmp(paraderoInicio->horariosParadero[i]->tiempoLlegada, hora) == 0) 
            {
                seEncontroHora = 1;
                char *numeroBusT = paraderoInicio->horariosParadero[i]->numeroBus;
                printf("\nBus a tomar: %s", numeroBusT);

                for (int k = 0; k < numRutas; k++)
                    {
                        Ruta *ruta = rutas[k];
                        if (ruta->busRuta == atoi(numeroBusT))
                        {
                            for (x = 0; x< ruta->numParaderos; x++)
                                {
                                    if (ruta->paraderos[x]->numeroParadero == paraderoBajada)  
                                        printf("\nRuta encontrada!! Bus a tomar : %d\n",  ruta->busRuta);
                                }


                        }
                    }
            }
            /*else{
                printf("\nNo se encontro el horario de salida");
                presioneTeclaParaContinuar();
            }*/


        }
        if (seEncontroHora == 0) printf("No se encontro ningun bus con ese horario en el paradero de salida\n");

    }
    else
    {
        printf("No se encontro el paradero de inicio o destino\n");
        presioneTeclaParaContinuar();
        return;
    }


    return;
}