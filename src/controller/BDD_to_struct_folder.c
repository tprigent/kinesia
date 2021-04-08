/*!
* \file BDD_to_struct_folder.c
* \brief Functions with SQL requests to fill Folder structure.
*/

#include "BDD_to_struct_folder.h"
#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include "../model/folder_manager.h"
#include <string.h>

/*!
 * This function makes an SQL request, return a Folder struct from the id of the folder.
 *
 * \param[in] id of the folder
 * \param[out] a struct folder.
*/
Folder* getFolder(int idFolder){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt=NULL;
    Folder *folder=NULL;

    if(allocateFolder(&folder) == -1){
        fprintf(stderr,"Erreur alloc folder\n");
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
    sql = "SELECT * FROM folder WHERE idFolder=?";

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_bind_int(stmt,1,idFolder);

    sqlite3_step(stmt);

    if(setFolder(folder,(char*)sqlite3_column_text(stmt,1),(char*)sqlite3_column_text(stmt,2),
                 (char*)sqlite3_column_text(stmt,3),sqlite3_column_int(stmt,6),
                 sqlite3_column_int(stmt,5),sqlite3_column_int(stmt,4),
                 sqlite3_column_int(stmt,7),sqlite3_column_int(stmt,0),
                 sqlite3_column_int(stmt,8)) == -1){

        fprintf(stderr,"Erreur set folder");
        return NULL;

    }

    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return folder;

}

/*!
 * This function makes an SQL request, return the name of a Folder from its id.
 *
 * \param[in] int, the id of the folder
 * \param[out] char*, the name of the folder.
*/
char* getNameFolder(int idFolder){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt=NULL;
    char* folderName;

    folderName = (char*)malloc(sizeof(char)*LG_MAX_INFO);

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
    sql = "SELECT folderName FROM folder WHERE idFolder=?";

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_bind_int(stmt,1,idFolder);

    sqlite3_step(stmt);

    strcpy(folderName,(char*)sqlite3_column_text(stmt,0));

    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return folderName;

}

/*!
 * This function makes an SQL request, returns every Folder id from a Patient's id.
 *
 * \param[in] int, the id of the patient
 * \param[out] int*, an array of every folder id of the patient.
*/
int* getIdFolder(int idPatient){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt=NULL;
    int* tab_id;

    tab_id = (int*)malloc(sizeof(int)*NB_MAX_SESSION);

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
    sql = "SELECT idFolder FROM folder WHERE idPatient=?";

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_bind_int(stmt,1,idPatient);

    int i;
    i=0;
    while(sqlite3_step(stmt) == SQLITE_ROW){
        tab_id[i] = sqlite3_column_int(stmt,0);
        i++;
    }

    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return tab_id;

}