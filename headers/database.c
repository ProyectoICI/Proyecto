#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//-------------------------------------------------------------------------------------

int tableExists(sqlite3 *db, const char *tableName) {
  char *errMsg = 0;
  char sql[256];
  int exists = 0;
  sqlite3_stmt *stmt;

  sprintf(sql, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='%s';", tableName);
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
      if (sqlite3_step(stmt) == SQLITE_ROW) {
          exists = sqlite3_column_int(stmt, 0);
      }
      sqlite3_finalize(stmt);
  }
  return exists;
}

void createTableIfNotExists(sqlite3 *db, const char *tableName, const char *createTableSQL) {
  if (!tableExists(db, tableName)) {
    char *errMsg = 0;
    if (sqlite3_exec(db, createTableSQL, 0, 0, &errMsg) != SQLITE_OK) {
        printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } 
  }
}

void ensureAllTablesExist(sqlite3 *db) {
    const char *createTableStatements[] = {
        "CREATE TABLE Buses (BusID INTEGER PRIMARY KEY AUTOINCREMENT, Number INTEGER NOT NULL);",
        "CREATE TABLE Users (UserID INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT NOT NULL, Password TEXT NOT NULL, IsAdmin BOOLEAN NOT NULL);",
        "CREATE TABLE Paraderos (ParaderoID INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT NOT NULL, Number INTEGER NOT NULL, numEdges INTEGER NOT NULL, numHorarios INTEGER NOT NULL);",
        "CREATE TABLE Routes (RouteID INTEGER PRIMARY KEY AUTOINCREMENT, BusID INTEGER, NumParaderos INTEGER, FOREIGN KEY (BusID) REFERENCES Buses(BusID));",
        "CREATE TABLE Horarios (HorarioID INTEGER PRIMARY KEY AUTOINCREMENT, ParaderoID INTEGER, BusID INTEGER, ArrivalTime TEXT NOT NULL, FOREIGN KEY (ParaderoID) REFERENCES Paraderos(ParaderoID), FOREIGN KEY (BusID) REFERENCES Buses(BusID));",
        "CREATE TABLE Edges (EdgeID INTEGER PRIMARY KEY AUTOINCREMENT, StartParaderoID INTEGER, EndParaderoID INTEGER, Distance INTEGER NOT NULL, FOREIGN KEY (StartParaderoID) REFERENCES Paraderos(ParaderoID), FOREIGN KEY (EndParaderoID) REFERENCES Paraderos(ParaderoID));",
        "CREATE TABLE RouteParaderos (RouteID INTEGER, ParaderoID INTEGER, PRIMARY KEY (RouteID, ParaderoID), FOREIGN KEY (RouteID) REFERENCES Routes(RouteID), FOREIGN KEY (ParaderoID) REFERENCES Paraderos(ParaderoID));"
    };
    int numStatements = sizeof(createTableStatements) / sizeof(createTableStatements[0]);

    for (int i = 0; i < numStatements; i++) {
        char tableName[50];
        sscanf(createTableStatements[i], "CREATE TABLE %s ", tableName);
        char *parenthesisPos = strchr(tableName, '(');
        if (parenthesisPos) {
            *parenthesisPos = '\0';
        }
        createTableIfNotExists(db, tableName, createTableStatements[i]);
    }
}

int connectDatabase(sqlite3** db, const char* filename) {
    int rc = sqlite3_open(filename, db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "No se pudo abrir la base de datos: %s\n", sqlite3_errmsg(*db));
        sqlite3_close(*db);
        return 0;
    }
    ensureAllTablesExist(*db);
    printf("\033[1;32m%s\033[0m","** Base de datos conectada **\n");
    return 1;
}

static int callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

bool userExists(sqlite3 *db, const char *name) {
    const char *sql = "SELECT 1 FROM Users WHERE Name = ?";
    sqlite3_stmt *stmt;
    bool exists = false;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = true;
        }
        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }

    return exists;
}

void addAdminUser(sqlite3 *db) {
    const char *adminName = "admin";
    const char *adminPassword = "admin";

    if (!userExists(db, adminName)) {
        const char *sql = "INSERT INTO Users (Name, Password, isAdmin) VALUES (?, ?, ?)";
        sqlite3_stmt *stmt;

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, adminName, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, adminPassword, -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 3, 1); // isAdmin is true

            if (sqlite3_step(stmt) != SQLITE_DONE) {
                printf("Error al registrar el usuario admin: %s\n", sqlite3_errmsg(db));
            } else {
                printf("\033[1;32m%s\033[0m\n", "Usuario admin registrado exitosamente.\n");
            }
            sqlite3_finalize(stmt);
        } else {
            fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        }
    } 
}

//-------------------------------------------------------------------------------------



