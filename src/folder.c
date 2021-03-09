//
// Created by paul on 01/03/2021.
//

#include "folder.h"
#include <sqlite3.h>
#include "structures.h"
#include <stdio.h>

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
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
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