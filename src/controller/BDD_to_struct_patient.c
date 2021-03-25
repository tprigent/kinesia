//
// Created by salome on 22/03/2021.
//

#include "BDD_to_struct_patient.h"
#include "../model/patient_manager.h"
#include <string.h>
#include <sqlite3.h>
#include <stdlib.h>

/*!
 * This function makes an SQL request, returns the number of patient in the database.
 *
 * \param[out] int, the number of patient.
*/
int getNbPatient(){
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
    sql = "SELECT * FROM patient";

    //Préparation de la requête
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

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

/*!
 * This function makes an SQL request, returns the name and first name of a patient
 * from a patient's id.
 *
 * \param[in] int, the patient's id
 *
 * \param[out] char*, the name and first name of the patient: "<Name> <Firstname>".
*/
char* getNameFirstnamePatient(int id){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;
    char* nom;

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
    sql = "SELECT firstname,name FROM patient WHERE id=?";

    //Préparation de la requête
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return NULL;
    }

    sqlite3_bind_int(stmt,1,id);

    //Execution de la requête
    sqlite3_step(stmt);

    if(allocateStringPatient(&nom,LG_MAX_INFO*2)==-1){
        fprintf(stderr,"Erreur allocation getNomPrenom");
        return NULL;
    }

    strcpy(nom,(char*)sqlite3_column_text(stmt,0));
    char* space=" ";
    strcat(nom,space);
    strcat(nom,(char*)sqlite3_column_text(stmt,1));

    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return nom;

}



/*!
 * This function makes an SQL request, fills a Patient struct previously allocated
 * with the results of the request and return the addressof the Patient struct allcated.
 *
 * \param[in] int id of the Patient
 *
 * \param[out] Patient struct of the corresponding id
*/
Patient* getPatient(int id){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;
    Patient *patient;
    Address adresse;
    Date birthDate;
    Date firstRdDdate;

    if(allocatePatient(&patient) == -1 || allocateAddress(&adresse) == -1 ){
        fprintf(stderr,"Erreur d'allocation\n");
    }

    //Opening database
    rc = sqlite3_open(DB_PATH, &db);

    //Testing opening
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    } else {
        fprintf(stdout,"Opened database successfully\n");
    }

    //Creating te request
    sql = "SELECT * FROM patient WHERE id=?";

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return NULL;
    }

    sqlite3_bind_int(stmt,1,id);

    sqlite3_step(stmt);

    if(setDate(&birthDate,
               sqlite3_column_int(stmt,5),
               sqlite3_column_int(stmt,4),
               sqlite3_column_int(stmt,3)) == -1 ){
        fprintf(stderr,"Erreur setDate birthdate\n");
    }
    if(setDate(&firstRdDdate,
               sqlite3_column_int(stmt,15),
               sqlite3_column_int(stmt,14),
               sqlite3_column_int(stmt,13)) == -1 ){
        fprintf(stderr,"Erreur setDate first RDV\n");
    }

    setAddress(&adresse,(char*)sqlite3_column_text(stmt,18),
               (char*)sqlite3_column_text(stmt,19),
               (char*)sqlite3_column_text(stmt,20),
               (char*)sqlite3_column_text(stmt,21));

    if(setPatient(patient,(char*)sqlite3_column_text(stmt,1),(char*)sqlite3_column_text(stmt,2),birthDate,
                  (char*)sqlite3_column_text(stmt,6),sqlite3_column_int(stmt,7),
                  adresse,(char*)sqlite3_column_text(stmt,8),
                  (char*)sqlite3_column_text(stmt,9),(char*)sqlite3_column_text(stmt,22),
                  (char*)sqlite3_column_text(stmt,10),(char*)sqlite3_column_text(stmt,11),
                  (char*)sqlite3_column_text(stmt,12),firstRdDdate,
                  (char*)sqlite3_column_text(stmt,16),(unsigned int)id,sqlite3_column_int(stmt,23)) != 0){
        fprintf(stderr,"Erreur setPatient");
        patient = NULL;}

    sqlite3_finalize(stmt);
    freeAddress(&adresse);

    //Closing database
    sqlite3_close(db);
    return patient;

}

/*!
 * This function makes an SQL request, returns the patients archived's id sorted by name.
 *
 * \param[out] int*, an array of the id's, ending with the value -1.
*/
int* getArchivedPatientID(){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;
    int *tab_id;

    if((tab_id = (int*)malloc(sizeof(int)*NB_MAX_SESSION)) == NULL ){
        return NULL;
    }

    //Opening database
    rc = sqlite3_open(DB_PATH, &db);

    //Testing opening
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    } else {
        fprintf(stdout,"Opened database successfully\n");
    }

    //Creating te request
    sql = "SELECT id FROM patient WHERE isArchived=1 ORDER BY name DESC";

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return NULL;
    }

    int nbArchivedPatient;
    nbArchivedPatient=0;
    while(sqlite3_step(stmt) == SQLITE_ROW){
        tab_id[nbArchivedPatient] = sqlite3_column_int(stmt,0);
        nbArchivedPatient++;
    }

    tab_id[nbArchivedPatient] = -1;

    sqlite3_finalize(stmt);

    //Closing database
    sqlite3_close(db);
    return tab_id;

}

/*!
 * This function makes an SQL request, returns the patients active's id sorted by name.
 *
 * \param[out] int*, an array of the id's, ending with the value -1.
*/
int* getActivePatientID(){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;
    int *tab_id;

    if((tab_id = (int*)malloc(sizeof(int)*NB_MAX_SESSION)) == NULL ){
        return NULL;
    }

    //Opening database
    rc = sqlite3_open(DB_PATH, &db);

    //Testing opening
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    } else {
        fprintf(stdout,"Opened database successfully\n");
    }

    //Creating te request
    sql = "SELECT id FROM patient WHERE isArchived=0 ORDER BY name DESC";

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return NULL;
    }

    int nbArchivedPatient;
    nbArchivedPatient=0;
    while(sqlite3_step(stmt) == SQLITE_ROW){
        tab_id[nbArchivedPatient] = sqlite3_column_int(stmt,0);
        nbArchivedPatient++;
    }

    tab_id[nbArchivedPatient] = -1;

    sqlite3_finalize(stmt);

    //Closing database
    sqlite3_close(db);
    return tab_id;

}

/*!
 * This function returns the number of archived patients.
 *
 * \param[out] int, the number of archived patients.
*/
int getNbActivePatient(){

    int* nb;
    int i = 0;
    nb = getActivePatientID();
    while(nb[i] != -1){
        i++;
    }
    return i;

}

/*!
 * This function returns the number of archived patients.
 *
 * \param[out] int, the number of archived patients.
*/
int getNbArchivedPatient(){
    return (getNbPatient()-getNbActivePatient());
}
