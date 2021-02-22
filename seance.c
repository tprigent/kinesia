/*!
* \file seance.c
* \brief File with functions to allocate, fill from database requests, and free Session structure
*/

#include "seance.h"
#include "Structures.h"
#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>

//Ajout d'une seance avec un instance de struct seance
int addSeance(Seance *seance){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;

    //Ouverture de la bdd
    rc = sqlite3_open("/BaseDeDonnee/Bdd.db", &db);

    //Test de l'ouverture
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr,"Opened database successfully\n");
    }

    //Creation de la requête
    sql = "INSERT INTO patient (idDossier,dateSeance_year,dateSeance_month"
          ",dateSeance_day,dateSeanceSuiv_year"
          ",dateSeanceSuiv_month,dateSeanceSuiv_day,observations,nomSeance) VALUES (?,?,?,?,?,"
          "?,?,?,?)";

    //Préparation de la requête
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    //Ajout des valeurs dans la requête
    sqlite3_bind_int(stmt,1,seance->idDossier);
    sqlite3_bind_int(stmt,2,seance->dateSeance.year);
    sqlite3_bind_int(stmt,3,seance->dateSeance.month);
    sqlite3_bind_int(stmt,4,seance->dateSeance.day);
    sqlite3_bind_int(stmt,5,seance->dateSeanceSuiv.year);
    sqlite3_bind_int(stmt,6,seance->dateSeanceSuiv.month);
    sqlite3_bind_int(stmt,7,seance->dateSeanceSuiv.day);
    sqlite3_bind_text(stmt,8,seance->observations,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,9,seance->nomSeance,-1,SQLITE_TRANSIENT);

    //Execution de la requête
    rc = sqlite3_step(stmt);
    if( rc != SQLITE_DONE ){
        fprintf(stderr, "Step error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }
    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return 1;

}

//Recupération d'une séance
Seance* getSeance(int idSeance){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;
    Seance *seance;

    //Ouverture de la bdd
    rc = sqlite3_open("/BaseDeDonnee/Bdd.db", &db);

    //Test de l'ouverture
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    } else {
        fprintf(stderr,"Opened database successfully\n");
    }

    //Creation de la requête
    sql = "SELECT * FROM seance WHERE idSeance=?";

    sqlite3_bind_int(stmt,-1,idSeance);

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    while(sqlite3_step(stmt) == SQLITE_ROW){

    }
    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return seance;

}