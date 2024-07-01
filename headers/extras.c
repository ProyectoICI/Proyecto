#include <stdio.h>

#include <string.h>
#include <ctype.h> 
#include <stdlib.h>  

#include <stdbool.h>

//==============================FUNCIONES PRINCIPALES==================================

bool contieneEspacios(const char *str) {    
    while (*str) {                          
        if (isspace((unsigned char)*str)) { 
            return true;                    
        } str++;                            
    }
    return false;                           
}

//-------------------------------------------------------------------------------------

bool checkPassword(const char *username, const char *password, 
                   const char *filePath) {     
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

//-------------------------------------------------------------------------------------

int obtenerOpcionValida(int min, int max)       
{
    char input[50];                           
    int opcion;                              
    static int contImpresiones = 0;            

    while (true) {                        
        scanf("%49s", input);                   
        int esNumero = 1;                    
        for (int i = 0; input[i] != '\0'; i++) { 
            if (!isdigit(input[i])) {         
                esNumero = 0;                 
                break;                       
            }
        }
        if (esNumero) {                     
            opcion = atoi(input);               
            if (opcion >= min && opcion <= max) break; 
        }
        if (contImpresiones == 0) {             
            printf("\033[1;32m%s\033[0m\n","Opción inválida. Por favor, ingrese una opción válida.\n");
            contImpresiones++;              
        }
    }
    contImpresiones = 0;                         
    return opcion;                            
}