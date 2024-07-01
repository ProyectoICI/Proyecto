#ifndef DATABASE_H
#define DATABASE_H

#include <stdbool.h>

typedef struct sqlite3 sqlite3;

int connectDatabase(sqlite3** db, const char* filename);
int tableExists(sqlite3 *db, const char *tableName);
void createTableIfNotExists(sqlite3 *db, const char *tableName, const char *createTableSQL);
void ensureAllTablesExist(sqlite3 *db);

bool userExists(sqlite3 *db, const char *name);
void addAdminUser(sqlite3 *db);

// Para nuestra funcion searchDatabase
static int callback(void* data, int argc, char** argv, char** azColName);

#endif