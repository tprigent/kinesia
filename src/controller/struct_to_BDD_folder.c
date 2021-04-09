/*!
* \file struct_to_BDD_folder.c
* \brief File to put data in BDD from Folder's structures.
*/

#include "struct_to_BDD_folder.h"
#include <sqlite3.h>
#include <stdio.h>

/*!
 * \brief This function makes an SQL request, adds a folder in the database from a Folder struct.
 *
 * \param[in] a Folder struct.
 *
 * \param[out] int, 1 if an error occurred, 0 otherwise
*/
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
          ",numberOfFiles,idPatient) VALUES (?,?,?,?,?,"
          "?,?,?)";

    //Préparation de la requête
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    //Ajout des valeurs dans la requête
    int i;
    i=1;
    sqlite3_bind_text(stmt,i++,folder->folderName,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,folder->pathology,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,folder->details,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i++,folder->startOfTreatment.year);
    sqlite3_bind_int(stmt,i++,folder->startOfTreatment.month);
    sqlite3_bind_int(stmt,i++,folder->startOfTreatment.day);
    sqlite3_bind_int(stmt,i++,(int)folder->numberOfFiles);
    sqlite3_bind_int(stmt,i++,(int)folder->idPatient);

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
 * \brief This function makes an SQL request, changed the folder's entries in the database.
 *
 * \param[in] a Folder struct.
 *
 * \param[out] int, 1 if an error occurred, 0 otherwise
*/
int modifyFolder(Folder *folder){

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
    sql = "UPDATE folder SET folderName=?,pathology=?,details=?,startOfTreatment_year=?"
          ",startOfTreatment_month=?,startOfTreatment_day=?"
          ",numberOfFiles=?,idPatient=? WHERE idFolder=?";

    //Préparation de la requête
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    int i;
    i=1;
    //Ajout des valeurs dans la requête
    sqlite3_bind_text(stmt,i++,folder->folderName,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,folder->pathology,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,folder->details,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i++,folder->startOfTreatment.year);
    sqlite3_bind_int(stmt,i++,folder->startOfTreatment.month);
    sqlite3_bind_int(stmt,i++,folder->startOfTreatment.day);
    sqlite3_bind_int(stmt,i++,(int)folder->numberOfFiles);
    sqlite3_bind_int(stmt,i++,(int)folder->idPatient);
    sqlite3_bind_int(stmt,i,(int)folder->idFolder);

    //Execution de la requête
    rc = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return 1;

}