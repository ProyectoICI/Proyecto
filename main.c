// ** DEPENDENCIAS ** 
#include "tdas/extra.h"     
#include "tdas/list.h"      
#include "tdas/map.h"       
#include "headers/pqueue.h" 

// ** HEADERS **
#include "headers/cargar.h"    
#include "headers/menus.h"    
#include "headers/buses.h"    
#include "headers/paraderos.h" 
#include "headers/rutas.h"   
#include "headers/consultas.h" 
#include "headers/database.h"
#include "headers/extras.h"

// ** STANDARD LIBRARY **
#include <ctype.h>   
#include <stdbool.h> 
#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  

// ** SQLITE **
#include <sqlite3.h> 

//===========--------- DECLARACIÓN DE ENTIDADES ---------======================


// 'Forward-Declaration' de estas entidades para el compilador
typedef struct Paradero Paradero; 
typedef struct Edge Edge;  


typedef struct Horario { 
  char numeroBus[50];    
  char tiempoLlegada[6]; 
} Horario;

typedef struct PriorityQueueNode { 
  Paradero* paradero;              
  int priority;                    
} PriorityQueueNode;               

typedef struct PriorityQueue { 
  PriorityQueueNode* nodes;     
  int size;                     
  int capacity;                 
} PriorityQueue;                

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

typedef struct Usuario { 
    char nombre[50];    
    bool esAdmin;       
} Usuario;               

typedef struct Bus {    
    int numeroBus;      
} Bus;                   

typedef struct Ruta {   
    int busRuta;         
    Paradero** paraderos;
    int numParaderos;   
} Ruta;                  

// ----------------------------------------------------------------------------------

int main() {
    sqlite3* db;
    connectDatabase(&db, "database.db");

    /* -- ELIMINAR EN PROD --
       Genera un usuario (admin) con usuario y contraseña 'admin'
       en la base de datos.
    */
    //addAdminUser(db);
    
    Bus** buses = (Bus **)malloc(100 * sizeof(Bus));
    int numBuses = 0;

    Ruta** rutas = (Ruta **)malloc(100 * sizeof(Ruta));
    int numRutas = 0;

    Graph* graph = (Graph *)malloc(100 * sizeof(Graph));

    if (graph->nodes == NULL) {
      graph->nodes = (Paradero **)malloc(sizeof(Paradero *) * 100);
      graph->numNodes = 0;
    }
    graph->numNodes = 0;

    Map *MapUsuarios = map_create(is_equal_str);
    
    cargarUsuarios(MapUsuarios, db);
    
    buses = cargarBuses(db, &numBuses);
    graph->nodes = cargarParaderos(db, &graph->numNodes);

    /* 
    La función findParaderoById() genera un bucle infinito, por lo que la función cargarRutas() no
    funcionaría correctamente. Mas detalles en el README
    */
    //rutas = cargarRutas(db, &numRutas);
    
    mostrarIngreso(MapUsuarios, graph, buses, &numBuses, rutas, &numRutas, db);
    
    return 0;
}