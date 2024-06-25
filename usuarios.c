#include "tdas/extra.h"
#include "usuarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "menus.h"
#include "paraderos.h"

int is_equal_str(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2) == 0;
}

void MenuAdmin()
{
    Map *mapParaderos = map_create(is_equal_str);
    char opcion;
    do {
        MostrarMenuAdmin();
        printf("\nIngrese su opción: ");
        scanf(" %c", &opcion);

        switch (opcion)
        {
            case '1':
            {
                MostrarMenuParaderos();
                scanf(" %c", &opcion);
                if (opcion == '1') {
                    agregarParadero(mapParaderos);
                } else if (opcion == '2') {
                    //editarParadero();
                } else if (opcion == '3') {
                    //listarParaderos();
                }
                break;
            }

            case '2':
            {
                MostrarMenuBuses();
                scanf(" %c", &opcion);
                if (opcion == '1') {
                    //agregarBus();
                } else if (opcion == '2') {
                    //editarBus();
                } else if (opcion == '3') {
                    //listaBuses();
                } 
                break; 
            }

            case '3':
            {
                MostrarMenuRutas();
                scanf(" %c", &opcion);
                if (opcion == '1') {
                    //agregarRutaBus();
                } else if (opcion == '2') {
                    //editarRutaBus();
                } else if (opcion == '3') {
                    //listaRutaBus();
                }
                break;
            }

            case '4':
            {
                MostrarMenuOtros();
                scanf(" %c", &opcion);
                if (opcion == '1') {
                    //generarReporte();
                }
                break;
            }
            default:
                printf("\n");
        }
    } while (opcion != '5');   
    limpiarPantalla();
    map_clean(mapParaderos);
}

void MenuUsuario() {
    char opcion;

    do 
    {
        limpiarPantalla();
        MostrarMenuUsuarios();
        printf("\nIngrese su opción: ");
        scanf(" %c", &opcion);
        switch (opcion)
        {
            case '1':
            {
                limpiarPantalla();
                MostrarMenuTrayecto();
                scanf(" %c", &opcion);
                if (opcion == '1')
                    // planificarTrayecto();
                break;
            }


            case '2':
            {
                limpiarPantalla();
                MostrarMenuConsultas();
                scanf(" %c", &opcion);
                if (opcion == '1')
                /* ConsultaHorariosP();
                else if (opcion == '2')
                    ConsultaParaderos(); */
                break;
            }
            default:
                printf("\n");
        }
    } while (opcion != '3');
}


bool checkPassword(const char *username, const char *password, const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        perror("Error opening file");
        return false;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char *token = strtok(line, ",");
        if (strcmp(token, username) == 0) {
            token = strtok(NULL, ",");
            if (strcmp(token, password) == 0) {
                fclose(file);
                return true;
            }
            break;
        }
    }

    fclose(file);
    return false;
}

void cargarUsuarios(Map *usuarios) {
    FILE* archivo = fopen("usuarios.csv", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo de usuarios.csv");
        return;
    }

    char **campos;
    campos = leer_linea_csv(archivo, ',');

    while((campos = leer_linea_csv(archivo, ',')) != NULL) {
        Usuario *usuario = (Usuario*)malloc(sizeof(Usuario));
        strcpy(usuario->nombre, campos[0]);

        usuario->esAdmin = (strcmp(campos[2], "1") == 0);
        map_insert(usuarios, usuario->nombre, usuario);
    }
    fclose(archivo);    
}



void ingresoSesion(Map *usuarios) {
    char usuario[50];
    char contrasena[50];
    printf("========================================\n");
    printf("\033[1mIniciar Sesión\033[0m\n");
    printf("========================================\n");

    printf("Ingrese su usuario: ");
    scanf("%49s", usuario);

    printf("Ingrese su contraseña: ");
    scanf("%49s", contrasena);

    int aux = 0;

    while(true) {
        MapPair *pair = map_search(usuarios, usuario);
        if (pair != NULL) {
            if (checkPassword(usuario, contrasena, "usuarios.csv")) {
                limpiarPantalla();
                printf("========================================\n");
                printf("   \033[1mSISTEMA DE BUSES\033[0m\n");
                printf("========================================\n");
                Usuario *usuarioEnc = pair->value;
                if (usuarioEnc->esAdmin) {
                    limpiarPantalla();
                    MenuAdmin();
                } else {
                    limpiarPantalla();
                    MenuUsuario();
                }
                break;
            } else {
                printf("La contraseña ingresada es incorrecta.\n");
                printf("Intentos permitidos: %d\n", 2 - aux);
                scanf("%49s", contrasena);
                if (aux == 1) {
                    return;
                }
                aux++;
            }
        } else if (aux >= 2) {
            printf("\n\033[1mDebe registrarse primero\033[0m\n");
            printf("Seleccione la opción 2 del Menú Principal\n");
            presioneTeclaParaContinuar();
            limpiarPantalla();
            return;
        } else {
            printf("\nIntente con un usuario ya registrado:\n");
            printf("Intentos permitidos: %d\n", 2 - aux);
            scanf("%49s", usuario);
            aux++;
        }
    }
}

void registroUsuario(Map *usuarios) {
    printf("Registro de usuario\n");
    char nombre[50];
    char contrasena[50];

    printf("Ingrese su nombre: ");
    scanf("%49s", nombre);

    printf("Ingrese su contraseña: ");
    scanf("%49s", contrasena);

    Usuario* nuevoUsuario = (Usuario*)malloc(sizeof(Usuario));
    strcpy(nuevoUsuario->nombre, nombre);
    nuevoUsuario->esAdmin = false;

    map_insert(usuarios, nuevoUsuario->nombre, nuevoUsuario);

    FILE* archivo = fopen("usuarios.csv", "a"); 
    if (archivo != NULL) {
        fprintf(archivo, "%s,%s,%d\n", nuevoUsuario->nombre, contrasena, nuevoUsuario->esAdmin ? 1 : 0);
        fclose(archivo);
    } else {
        perror("Error al abrir el archivo de usuarios.csv");
    }
    printf("Usuario registrado con éxito.\n");
}