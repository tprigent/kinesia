/*!
* \file seance.c
* \brief File with functions to allocate, fill from model requests, and free Session structure
*/

#include "seance.h"
#include "model/structures.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

//Ajout d'une seance avec un instance de struct seance
int addSeance(Session *seance){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;

    //Ouverture de la bdd
    rc = sqlite3_open(DB_PATH, &db);

    //Test de l'ouverture
    if( rc ) {
        fprintf(stderr, "Can't open model: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr,"Opened model successfully\n");
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
    sqlite3_bind_int(stmt,1,seance->idFolder);
    sqlite3_bind_int(stmt,2,seance->sessionDate.year);
    sqlite3_bind_int(stmt,3,seance->sessionDate.month);
    sqlite3_bind_int(stmt,4,seance->sessionDate.day);
    sqlite3_bind_int(stmt,5,seance->nextSessionDate.year);
    sqlite3_bind_int(stmt,6,seance->nextSessionDate.month);
    sqlite3_bind_int(stmt,7,seance->nextSessionDate.day);
    sqlite3_bind_text(stmt,8,seance->observations,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,9,seance->sessionName,-1,SQLITE_TRANSIENT);

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
Session * getSeance(int idSeance){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;
    Session *seance;

    //Ouverture de la bdd
    rc = sqlite3_open(DB_PATH, &db);

    //Test de l'ouverture
    if( rc ) {
        fprintf(stderr, "Can't open model: %s\n", sqlite3_errmsg(db));
        return NULL;
    } else {
        fprintf(stderr,"Opened model successfully\n");
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