# SOFTWARE PARA GESTIÓN Y PLANIFICACIÓN DE RUTAS DE VIAJE
## Descripción General
_Este programa implementa diferentes estructuras de datos (TDA's) para gestionar rutas de buses y sus paraderos. El sistema permite añadir, editar y consultar rutas, paraderos y buses, utilizando colas de prioridad, mapas, listas y grafos._

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
- "headers/pqueue.h"
  
- "headers/extra.h"
- "headers/database.h"
  
Además, utiliza las bibliotecas personalizadas ubicadas en la carpeta _'tdas'_ para estructuras de datos y funciones auxiliares.
- "tdas/list.h"
- "tdas/extra.h"
- "tdas/map.h"
- "tdas/queue.h"

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
- Base de datos : La base de datos SQLITE con nombre 'database.db' funciona y guardaría cosas tales como los usuarios, paraderos y buses.
- Carga de datos desde la base de datos: La base de datos carga directamente a la memoria del programa los usuarios, paraderos y buses que contendría este.

- Añadir/Editar/Mostrar Buses : Uno puede añadir, editar o mostrar los buses que contiene el programa y por consiguiente de la base de datos.
- Añadir/Editar/Mostrar Paraderos : Uno puede añadir, editar o mostrar los paraderos que contiene el programa y por consiguiente de la base de datos.
- Añadir/Editar/Mostrar Rutas : Uno puede añadir, editar o mostrar las rutas que contiene el programa.
- Generar reporte: El administrador puede generar un reporte del programa en base a ciertas caracteristicas.

- Consultas horario por Parada/Ruta : El usuario común puede consultar los horarios de la parada o ruta que él quiera
- Consulta de buses disponibles : El usuario común puede consultar la lista de buses disponibles del programa.

## Errores con el programa: 
### Base de datos

- Faltaría aún la carga de las rutas, las cuales estarían provocando un búcle infinito en la implementacion actual debido a la llamada recursiva de
  findParaderoById(), la cual llamaría a cargarEdgesPorParadero() que llama a findParaderoById() devuelta. Falta solo cambiar la función para que no se llame de manera recursiva y solo se refiera a los nodos (paraderos) mediante las direcciones de memoria y no anidar las entidades infinitamente.

### Resto del programa

- El reporte solo genera un estado del programa
- La función de planificación de ruta no funciona como lo esperado
- Falta mejorar el checkeo de variables del usuario ( scanf() ) en múltiple funciones.
- Falta comentar parte de las funciones para crear una mejor documentación al respecto.


## Contribuciones

- Alfredo: Base de datos, interacción programa (memoria) con la base de datos, y todo lo relacionado con la carga de datos.
- Branco: Ajustes de localización, funciones para editar/añadir/listar paraderos, rutas, buses.
- Dante: Documentación, orden general del código, checkeos a ciertas funciones y creación de menús. Funciones de consulta.

## Licencia

This project is licensed under MIT license.
