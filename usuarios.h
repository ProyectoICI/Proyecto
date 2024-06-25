#ifndef USUARIOS_H
#define USUARIOS_H

#include "tdas/map.h"

typedef struct Usuario {
    char nombre[50];
    bool esAdmin;
} Usuario;

void cargarUsuarios(Map *usuarios);
bool checkPassword(const char *username, const char *password, const char *filePath);
void ingresoSesion(Map *usuarios);
void registroUsuario(Map *usuarios);

#endif // USUARIOS_H