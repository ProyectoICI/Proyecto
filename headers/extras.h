#ifndef EXTRAS_H
#define EXTRAS_H

#include <stdbool.h>

bool contieneEspacios(const char *str);
bool checkPassword(const char *username, const char *password, 
 const char *filePath);
int obtenerOpcionValida(int min, int max); 

#endif