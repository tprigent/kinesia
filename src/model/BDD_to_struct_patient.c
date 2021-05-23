/*!
* \file BDD_to_struct_patient.c
* \brief File with functions to take data from BDD, and put it in Patient structures
*/

#include "BDD_to_struct_patient.h"
#include "../model/patient_manager.h"
#include <string.h>
#include <sqlite3.h>
#include <stdlib.h>

/*!
 * \brief This function makes an SQL request, returns the name and first name of a patient
 * from a patient's id.
 *
 * \param[in] id ID of the Patient concerned
 *
 * \param[out] Name and first name of the patient: "<Name> <Firstname>".
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
 * \brief This function makes an SQL request, fills a Patient struct previously allocated
 * with the results of the request and return the addressof the Patient struct allcated.
 *
 * \param[in] id ID of the Patient
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

    setAddress(&adresse,(char*)sqlite3_column_text(stmt,17),
               (char*)sqlite3_column_text(stmt,18),
               (char*)sqlite3_column_text(stmt,19),
               (char*)sqlite3_column_text(stmt,20));

    if(setPatient(patient,(char*)sqlite3_column_text(stmt,1),(char*)sqlite3_column_text(stmt,2),birthDate,
                  (char*)sqlite3_column_text(stmt,6),sqlite3_column_int(stmt,7),
                  adresse,(char*)sqlite3_column_text(stmt,8),
                  (char*)sqlite3_column_text(stmt,9),(char*)sqlite3_column_text(stmt,21),
                  (char*)sqlite3_column_text(stmt,10),(char*)sqlite3_column_text(stmt,11),
                  (char*)sqlite3_column_text(stmt,12),firstRdDdate,
                  (char*)sqlite3_column_text(stmt,16),(unsigned int)id,sqlite3_column_int(stmt,22)) != 0){
        fprintf(stderr,"Erreur setPatient");
        patient = NULL;}

    sqlite3_finalize(stmt);
    freeAddress(&adresse);

    //Closing database
    sqlite3_close(db);
    return patient;

}

/*!
 * \brief This function makes an SQL request, returns the number of patient in the database.
 *
 * \param[out] a Status of the Patient
*/
int getNbPatient(Archived a){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc,nb;
    char *sql;
    sqlite3_stmt *stmt;

    //Opening database
    rc = sqlite3_open(DB_PATH, &db);

    //Testing opening
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stdout,"Opened database successfully\n");
    }

    //Creating te request
    switch(a) {
        case ACTIVE :
            sql = "SELECT COUNT(*) FROM patient WHERE isArchived=0";
            break;
        case ARCHIVED :
            sql = "SELECT COUNT(*) FROM patient WHERE isArchived=1";
            break;
        case ALL :
            sql = "SELECT COUNT(*) FROM patient";
            break;
        default:
            sqlite3_close(db);
            return 0;
    }
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    sqlite3_step(stmt);

    nb = sqlite3_column_int(stmt,0);

    sqlite3_finalize(stmt);

    //Closing database
    sqlite3_close(db);
    return nb;

}

/*!
 * \brief This function makes an SQL request, returns the patients ids and names
 * sorted by name and archived status
 *
 * \param[in] tabId array where the result ids will be stored
 * \param[in] nom array of string where the names will be stored
 * \param[in] a value of the Enum Archived to sort the result
 * \param[in] s value of the Enum Sort to define how to sort the result
 *
 * \param[out] int, 0 if an error occurred, 1 otherwise
*/
int getNameFirstnameIdPatient(int* tabId, char** nom, Archived a, Sort s){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc,i;
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
    switch(s) {
        case NAME_ASC :
            sql = "SELECT firstname,name,id FROM patient where isArchived=? ORDER BY name ASC";
            break;
        case NAME_DESC :
            sql = "SELECT firstname,name,id FROM patient where isArchived=? ORDER BY name DESC";
            break;
        case FIRSTNAME_ASC :
            sql = "SELECT firstname,name,id FROM patient where isArchived=? ORDER BY firstname ASC";
            break;
        case FIRSTNAME_DESC :
            sql = "SELECT firstname,name,id FROM patient where isArchived=? ORDER BY firstname DESC";
            break;
        default :
            sql = "SELECT firstname,name,id FROM patient where isArchived=? ORDER BY height ASC";
            break;
    }

    //Préparation de la requête
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    sqlite3_bind_int(stmt,1,a);

    //Execution de la requête
    i=0;
    while(sqlite3_step(stmt)== SQLITE_ROW) {

        if (allocateStringPatient(&nom[i], LG_MAX_INFO * 2) == -1) {
            fprintf(stderr, "Erreur allocation getNomPrenom");
            return 0;
        }

        strcpy(nom[i], (char *) sqlite3_column_text(stmt, 0));
        char *space = " ";
        strcat(nom[i], space);
        strcat(nom[i], (char *) sqlite3_column_text(stmt, 1));
        tabId[i] = sqlite3_column_int(stmt,2);
        i++;
    }
    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);

    return 1;
}

/*!
 * \brief This function makes an SQL request, returns the patients names and ids
 * if their name contains the stirng search
 *
 * \param[in] search String of the string to be searched
 * \param[in] result Array of string where the names will be stored
 * \param[in] ids Array where the result ids will be stored
 * \param[in] lenRes Value of the length of ids and result
 *
 * \param[out] int, 0 if an error occurred, 1 otherwise
*/
int searchPatient(char* search,char** result, int* ids, int lenRes){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc1,i;
    char *sql1;
    sqlite3_stmt *stmt1;
    char *searchStr;

    searchStr = malloc(strlen(search)* sizeof(char)+2);

    rc1 = sqlite3_open(DB_PATH, &db);

    if( rc1 ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    } else {
        fprintf(stderr,"Opened database successfully\n");
    }

    sql1 = "SELECT name,firstname,id FROM patient WHERE name LIKE ? OR firstname LIKE ?";

    rc1 = sqlite3_prepare_v2(db,sql1,-1,&stmt1,NULL);
    if( rc1 != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    strcpy(searchStr,"%");
    strcat(searchStr,search);
    strcat(searchStr,"%");

    sqlite3_bind_text(stmt1,1,searchStr,(int)strlen(searchStr),NULL);
    sqlite3_bind_text(stmt1,2,searchStr,(int)strlen(searchStr),NULL);

    i=0;
    while(sqlite3_step(stmt1) == SQLITE_ROW && i<lenRes) {

        if (allocateStringPatient(&result[i], LG_MAX_INFO * 2) == -1) {
            fprintf(stderr, "Erreur allocation getNomPrenom");
            return -1;
        }

        strcpy(result[i], (char *) sqlite3_column_text(stmt1, 1));
        char *space = " ";
        strcat(result[i], space);
        strcat(result[i], (char *) sqlite3_column_text(stmt1, 0));
        ids[i] = sqlite3_column_int(stmt1,2);
        i++;

    }

    free(searchStr);

    sqlite3_close(db);

    return i;
}