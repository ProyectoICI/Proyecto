# USO DE TDA'S PARA GESTIÓN DE RUTAS DE BUSES
## Descripción General
_Este programa implementa diferentes estructuras de datos (TDA's) para gestionar rutas de buses y sus paraderos. El sistema permite añadir, editar y consultar rutas, paraderos y buses, utilizando colas de prioridad, mapas, listas y grafos._

## Cómo compilar y ejecutar
Para compilar y ejecutar el programa, sigue estos pasos:
1. Visita Repl.it.
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Luego presiona "New Repl" y elige la opción "Import from Github".
4. Repl.it clonará el repositorio y preparará el código para ejecutarlo.
5. Instalar la dependencia de sqlite3 desde la pestaña 'Dependencias' de repl.it llamada
   ````
   'sqlite', 'A self-contained, serverless, zero-configuration, transactional SQL database engine'
   ````
7. El comando para ejecutarlo desde shell sería el siguiente
   ````
   "gcc tdas/*.c headers/*.c -l sqlite3 main.c -Wno-unused-result -o main"
   ````
8. Luego ejecutar desde shell
   ````
   ./main
   ````

# Funcionalidades
## Funcionando correctamente:
- Inicio y registro de Sesión: Permite registrar usuarios nuevos e iniciar sesión
  - Solo se añaden los usuarios (Administradores se asignan manualmente).
- Gestión de Paraderos: Permite agregar, editar y listar paraderos.
  - Se utiliza una estructura Graph que contiene nodos (Paradero), cada uno con su lista de horarios (Horario) y conexiones (Edge).
  - Los paraderos pueden conectarse entre sí mediante edges, que representan las distancias entre ellos.
- Gestión de Buses: Permite agregar, editar y listar buses.
  - Cada bus se identifica por un número y puede estar asignado a una o varias rutas.
- Gestión de Rutas: Permite agregar, editar y listar rutas.
  - Las rutas se almacenan en una cola de prioridad (PriorityQueue), ordenadas por criterios específicos, como la distancia total o el tiempo de llegada.

## Problemas conocidos:
- La implementación actual puede no ser óptima para sistemas con una gran cantidad de paraderos y rutas. Se podrían optimizar las funciones de búsqueda y filtrado.

## A mejorar:
- Implementar algoritmos más avanzados de búsqueda de rutas para mejorar la eficiencia y el tiempo de ejecución.
- Agregar opciones adicionales de configuración, como la capacidad de ingresar un estado inicial personalizado para el sistema de rutas.

## Dependencias:
El programa hace uso de las siguientes bibliotecas estándar de C:
- 'stdio.h'
- 'stdlib.h'
- 'string.h'
- 'stdbool.h'
- 'ctype.h'

La dependencia 'sqlite3' para el manejo de la base de datos relacional
- 'sqlite3.h'

Los headers de nuestro programa serían los siguientes
- "headers/cargar.h"
- "headers/menus.h" 
- "headers/buses.h"
- "headers/paraderos.h"
- "headers/rutas.h"
- "headers/consultas.h"
  
Además, utiliza las bibliotecas personalizadas ubicadas en la carpeta _'tdas'_ para estructuras de datos y funciones auxiliares.
- "tdas/list.h"
- "tdas/extra.h"
- "tdas/map.h"
- "tdas/queue.h"

# Ejemplos de uso

## Gestión de Paraderos
- Opción seleccionada: 1) 

```` c
````