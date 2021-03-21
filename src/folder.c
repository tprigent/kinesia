/*!
* \file folder.c
* \brief File with functions to allocate, fill from database requests, and free Folder structure
*/

#include "folder.h"
#include "patient.h"
#include <sqlite3.h>
#include "model/structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int allocateStringFolder(char **string, int lg) {
    *string = malloc(sizeof(char)*lg +1);
    if(*string == NULL) return -1;
    return 0;
}

int allocateFolder(Folder **d) {
    *d = malloc(sizeof(Folder));
    if(*d == NULL || allocateStringFolder(&((*d)->folderName), LG_MAX_INFO) !=0
    || allocateStringFolder(&((*d)->pathology), LG_MAX_INFO) !=0
    || allocateStringFolder((&(*d)->details), LG_MAX_OTHERS) !=0
    ) return -1;

    return 0;
}

int setFolder(Folder *d, char * folderName, char * pathology, char * details, int stDay, int stMonth, int stYear, int nbFiles, int idF, int idP) {
    strncpy(d->folderName, folderName, LG_MAX_INFO);
    strncpy(d->pathology, pathology, LG_MAX_INFO);
    strncpy(d->details, details, LG_MAX_OTHERS);

    d->folderName[LG_MAX_INFO] = '\0';
    d->pathology[LG_MAX_INFO] = '\0';
    d->details[LG_MAX_OTHERS] = '\0';

    if (setDate(&(d->startOfTreatment), stDay, stMonth, stYear) !=0) return -1;

    d->idFolder = idF;
    d->idPatient = idP;
    d->numberOfFiles=nbFiles;

    return 0;
}



int addFolder(Folder *folder){

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
    sql = "INSERT INTO folder (folderName,pathology,details,startOfTreatment_year"
          ",startOfTreatment_month,startOfTreatment_day"
          ",numberOfFiles) VALUES (?,?,?,?,?,"
          "?,?)";

    //Préparation de la requête
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    //Ajout des valeurs dans la requête
    sqlite3_bind_text(stmt,1,folder->folderName,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,1,folder->pathology,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,1,folder->details,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,2,folder->startOfTreatment.year);
    sqlite3_bind_int(stmt,3,folder->startOfTreatment.month);
    sqlite3_bind_int(stmt,4,folder->startOfTreatment.day);
    sqlite3_bind_int(stmt,5,(int)folder->numberOfFiles);

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