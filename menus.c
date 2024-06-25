#include <stdio.h> 

void MostrarMenuAdmin() {
  printf("========================================");
  printf("\n     Menu Administrador");
  printf("\n========================================");
  printf("\n1) Paraderos");
  printf("\n2) Buses");
  printf("\n3) Rutas");
  printf("\n4) Otros");
  printf("\n5) Salir"); 
  printf("\n========================================");
}

void MostrarMenuParaderos() {
  printf("========================================");
  printf("\n     Menu Paraderos");
  printf("\n========================================");
  printf("\n1) Agregar Paradero");
  printf("\n2) Editar Paradero");
  printf("\n3) Listar Paraderos");
  printf("\n4) Salir");
  printf("\n========================================\n");
}

void MostrarMenuBuses() {
  printf("========================================");
  printf("\n     Menu Buses");
  printf("\n========================================");
  printf("\n1) Agregar Bus");
  printf("\n2) Editar Bus");
  printf("\n3) Listar Buses");
  printf("\n4) Salir");
  printf("\n========================================");
}

void MostrarMenuRutas() {
  printf("========================================");
  printf("\n     Menu Rutas");
  printf("\n========================================");
  printf("\n1) Agregar Ruta de Bus");
  printf("\n2) Editar Ruta de Bus");
  printf("\n3) Listar Rutas de Bus");
  printf("\n4) Salir");
  printf("\n========================================");
}

void MostrarMenuOtros() {
  printf("========================================");
  printf("\n     Menu Otros");
  printf("\n========================================");
  printf("\n1) Generar Reporte de Uso");
  printf("\n2) Salir");
  printf("\n========================================");
}


//----------------Menu Usuarios----------------------------

void MostrarMenuUsuarios() {
  printf("========================================");
  printf("\n     Menu Usuarios");
  printf("\n========================================");
  printf("\n1) Trayectos");
  printf("\n2) Consultas");
  printf("\n3) Salir");
  printf("\n========================================");

}

void MostrarMenuTrayecto() {
  printf("========================================");
  printf("\n     Menu Trayecto");
  printf("\n========================================");
  printf("\n1) Planificar Trayecto");
  printf("\n2) Salir");
  printf("\n========================================");
}

void MostrarMenuConsultas() {
  printf("========================================");
  printf("\n     Menu Consultas");
  printf("\n========================================");
  printf("\n1) Consulta Horarios por Parada");
  printf("\n2) Consulta Paraderos");
  printf("\n3) Salir");
  printf("\n========================================");
}