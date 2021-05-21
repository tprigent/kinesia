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
 * \param[in] folder Folder to be added in DB
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
    sqlite3_bind_int(stmt,i,(int)folder->idPatient);

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
 * \param[in] folder Folder to be modified in DB
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
    sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return 1;

}

/*!
 * \brief This function makes an SQL request, delete the folder and its associated session(s).
 *
 * \param[in] id ID of the folder to be deleted
 *
 * \param[out] int, 1 if an error occurred, 0 otherwise
*/
int deleteFolder(int id){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc1,rc2;
    char *sql1;
    char *sql2;
    sqlite3_stmt *stmt1;
    sqlite3_stmt *stmt2;

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
    sql1 = "DELETE FROM seance WHERE idDossier IN (SELECT idFolder FROM folder WHERE idFolder=?)";
    sql2 = "DELETE FROM folder WHERE idFolder=?";

    //Préparing the requests
    rc1 = sqlite3_prepare_v2(db,sql1,-1,&stmt1,NULL);
    rc2 = sqlite3_prepare_v2(db,sql2,-1,&stmt2,NULL);
    if( rc1 != SQLITE_OK || rc2 != SQLITE_OK){
        fprintf(stderr, "Prepare error: %s , rc1 : %d, rc2 %d \n", zErrMsg,rc1,rc2);
        sqlite3_free(zErrMsg);
        return 0;
    }

    //Adding values to the requests
    sqlite3_bind_int(stmt1,1,id);
    sqlite3_bind_int(stmt2,1,id);

    //Executing the request
    sqlite3_step(stmt1);
    sqlite3_step(stmt2);

    sqlite3_finalize(stmt1);
    sqlite3_finalize(stmt2);

    //Closing database
    sqlite3_close(db);
    return 1;
}