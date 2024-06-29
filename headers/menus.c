#include "menus.h"
#include <stdio.h> 
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
