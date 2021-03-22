//
// Created by salome on 22/03/2021.
//

#include "struct_to_BDD_session.h"
#include <sqlite3.h>
#include <stdio.h>

//Ajout d'une seance avec un instance de struct seance
int addSession(Session *session){

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
        fprintf(stderr,"Opened database successfully\n");
    }

    //Creation de la requête
    sql = "INSERT INTO seance (idDossier,dateSeance_year,dateSeance_month"
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
    sqlite3_bind_int(stmt,1,(int)session->idFolder);
    sqlite3_bind_int(stmt,2,session->sessionDate.year);
    sqlite3_bind_int(stmt,3,session->sessionDate.month);
    sqlite3_bind_int(stmt,4,session->sessionDate.day);
    sqlite3_bind_int(stmt,5,session->nextSessionDate.year);
    sqlite3_bind_int(stmt,6,session->nextSessionDate.month);
    sqlite3_bind_int(stmt,7,session->nextSessionDate.day);
    sqlite3_bind_text(stmt,8,session->observations,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,9,session->sessionName,-1,SQLITE_TRANSIENT);

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

//Ajout d'une seance avec un instance de struct seance
int modifySession(Session *session){

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
        fprintf(stderr,"Opened database successfully\n");
    }

    //Creation de la requête
    sql = "UPDATE seance SET idDossier=?,dateSeance_year=?,dateSeance_month=?"
          ",dateSeance_day=?,dateSeanceSuiv_year=?"
          ",dateSeanceSuiv_month=?,dateSeanceSuiv_day=?,observations=?,nomSeance=? WHERE idSeance=?";

    //Préparation de la requête
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    //Ajout des valeurs dans la requête
    sqlite3_bind_int(stmt,1,(int)session->idFolder);
    sqlite3_bind_int(stmt,2,session->sessionDate.year);
    sqlite3_bind_int(stmt,3,session->sessionDate.month);
    sqlite3_bind_int(stmt,4,session->sessionDate.day);
    sqlite3_bind_int(stmt,5,session->nextSessionDate.year);
    sqlite3_bind_int(stmt,6,session->nextSessionDate.month);
    sqlite3_bind_int(stmt,7,session->nextSessionDate.day);
    sqlite3_bind_text(stmt,8,session->observations,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,9,session->sessionName,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,10,(int)session->idSession);

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