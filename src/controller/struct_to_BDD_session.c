/*!
* \file struct_to_BDD_session.c
* \brief File to put data in BDD from Session's structures.
*/

#include "struct_to_BDD_session.h"
#include <sqlite3.h>
#include <stdio.h>

/*!
 * \brief This function makes an SQL request, adds a session from a Session struct.
 *
 * \param[in] a Session struct.
 *
 * \param[out] int, 1 if an error occurred, 0 otherwise
*/
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
    sqlite3_bind_text(stmt,10,session->nextSessionHour,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,11,session->isRealFolder);

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

/*!
 * \brief This function makes an SQL request, modify a Session entry in patient table from a Session struct.
 *
 * \param[in] struct Session to be modified
 *
 * \param[out] int, 0 if an error occurred, 1 otherwise.
*/
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
    sqlite3_bind_int(stmt,0,(int)session->idSession);
    sqlite3_bind_text(stmt,10,session->nextSessionHour,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,11,session->isRealFolder);

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

int deleteSession(int id){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc1;
    char *sql1;
    sqlite3_stmt *stmt1;

    //Opening database
    rc1 = sqlite3_open(DB_PATH, &db);

    //Testing the opening
    if( rc1 ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr,"Opened database successfully\n");
    }

//Creating the request
    sql1 = "DELETE FROM seance WHERE idSeance = ?";

    //Préparing the requests
    rc1 = sqlite3_prepare_v2(db,sql1,-1,&stmt1,NULL);
    if( rc1 != SQLITE_OK){
        fprintf(stderr, "Prepare error: %s , rc1 : %d\n", zErrMsg,rc1);
        sqlite3_free(zErrMsg);
        return 0;
    }

    //Adding values to the requests
    sqlite3_bind_int(stmt1,1,id);

    //Executing the request
    sqlite3_step(stmt1);

    sqlite3_finalize(stmt1);

    //Closing database
    sqlite3_close(db);
    return 1;
}