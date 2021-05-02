/*!
* \file BDD_to_struct_session.c
* \brief File to take data from BDD about Sessions and fill Session structures
*/

#include "BDD_to_struct_session.h"
#include "../model/session_manager.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

/*!
 * \brief This function makes an SQL request, returns a Session struct from the sesison's id.
 *
 * \param[in] int, the session's id
 *
 * \param[out] Session*, a pointer to the session's struct
*/
Session * getSession(int idSession){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt=NULL;
    Session *session=NULL;

    session = (Session*)malloc(sizeof(Session));

    //Ouverture de la bdd
    rc = sqlite3_open(DB_PATH, &db);

    //Test de l'ouverture
    if( rc ) {
        fprintf(stderr, "Can't open model: %s\n", sqlite3_errmsg(db));
        return NULL;
    } else {
        fprintf(stderr,"Opened database successfully\n");
    }

    //Creation de la requête
    sql = "SELECT * FROM seance WHERE idSeance=?";

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_bind_int(stmt,1,idSession);

    sqlite3_step(stmt);

    initSession(session,(char*)sqlite3_column_text(stmt,9),(char*)sqlite3_column_text(stmt,8),
                sqlite3_column_int(stmt,4),sqlite3_column_int(stmt,3),sqlite3_column_int(stmt,2),
                sqlite3_column_int(stmt,7),sqlite3_column_int(stmt,6),sqlite3_column_int(stmt,5),
                (char*)sqlite3_column_text(stmt,10), sqlite3_column_int(stmt,11),
                sqlite3_column_int(stmt,0),sqlite3_column_int(stmt,1));

    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return session;

}

/*!
 * \brief This function makes an SQL request, returns the session's id of a folder.
 *
 * \param[in] int, the folder's id
 *
 * \param[out] int*, the session's id of the folder
*/
int * getSessionId(int idFolder){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt=NULL;
    int *tab_id;

    if((tab_id = (int*)malloc(sizeof(int)*NB_MAX_SESSION)) == NULL ){
        return NULL;
    }

    //Ouverture de la bdd
    rc = sqlite3_open(DB_PATH, &db);

    //Test de l'ouverture
    if( rc ) {
        fprintf(stderr, "Can't open model: %s\n", sqlite3_errmsg(db));
        return NULL;
    } else {
        fprintf(stderr,"Opened database successfully\n");
    }

    //Creation de la requête
    sql = "SELECT idSeance FROM seance WHERE idDossier=?";

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_bind_int(stmt,1,idFolder);

    int i;
    int j;
    i=0;
    while(sqlite3_step(stmt) == SQLITE_ROW){
        tab_id[i] = sqlite3_column_int(stmt,0);
        i++;
    }

    for(j=i; j<NB_MAX_SESSION; j++) {
        tab_id[j] = -1;
    }

    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return tab_id;

}

/*!
 * This function makes an SQL request, returns all the sessions associated with a Folder in a list of sessions.
 *
 * \param[in] int, the folder's id
 *
 * \param[out] SessionList *, the list filled with sessions.
*/
SessionList * getSessionList(int idF) {
    SessionList * l = (SessionList *) malloc(sizeof(SessionList));
    initList(l);
    if (l == NULL) return NULL;

    int * tab_id = getSessionId(idF);
    if(tab_id == NULL) return NULL;

    int i = 0;

    while(i<NB_MAX_SESSION && tab_id[i] != -1) {
        Session * s = getSession(tab_id[i]);
        if(insertFirst(l, s->sessionName, s->observations, s->sessionDate.day, s->sessionDate.month, s->sessionDate.year, s->nextSessionDate.day, s->nextSessionDate.month, s->nextSessionDate.year, s->nextSessionHour, s->isRealFolder, (int) s->idSession, (int) s->idFolder) !=0) return NULL;
        freeSession(s);
        free(s);
        i++;
    }
    free(tab_id);
    return l;
}

/*!
 * \brief This function makes an SQL request, returns the number of sessions in a folder.
 *
 * \param[in] int, the folder's id
 *
 * \param[out] int, the number of sessions in the folder
*/
int getNbSession(int idFolder) {
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
    sql = "SELECT * FROM seance where idDossier=?";

    //Préparation de la requête
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    sqlite3_bind_int(stmt,1,idFolder);

    //Execution de la requête
    rc=0;
    while(sqlite3_step(stmt) == SQLITE_ROW) {
        rc++;
    }

    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return rc;
}