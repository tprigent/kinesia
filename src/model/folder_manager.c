/*!
* \file folder_manager.c
* \brief File with functions to allocate, fill from database requests, and free Folder structure
*/

#include "folder_manager.h"
#include "patient_manager.h"
#include "../controller/display_helpers.h"
#include <sqlite3.h>
#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
 * \brief This function allows memory for Folder string
 *
 * \param[in] string String to be allocated
 * \param[in] lg Length of the string to be allocated
 * \param[out] 1 if an error occurred, 0 otherwise
*/
int allocateStringFolder(char **string, int lg) {
    *string = malloc(sizeof(char)*lg +1);
    if(*string == NULL) return -1;
    return 0;
}

/*!
 * \brief This function allows memory for a whole Folder structure
 *
 * \param[in] d Folder to be allocated
 * \param[out] 1 if an error occurred, 0 otherwise
*/
int allocateFolder(Folder **d) {
    *d = malloc(sizeof(Folder));
    if(*d == NULL || allocateStringFolder(&((*d)->folderName), LG_MAX_INFO) !=0
    || allocateStringFolder(&((*d)->pathology), LG_MAX_INFO) !=0
    || allocateStringFolder((&(*d)->details), LG_MAX_OTHERS) !=0
    ) return -1;

    return 0;
}

/*!
 * \brief This function stores new data into a given Folder
 *
 * \param[in] d Folder to be updated
 * \param[in] folderName Name of the folder
 * \param[in] pathology Pathology associated to the Folder
 * \param[in] details Details relative to the Folder
 * \param[in] stDay First day of consultation
 * \param[in] stMonth First month of consultation
 * \param[in] stYear First year of consultation
 * \param[in] nbFiles Number of attachments relative to the folder
 * \param[in] idF Unique identifier for the Folder
 * \param[in] idP Unique identifier for the relative Patient
 * \param[out] 1 if an error occurred, 0 otherwise
*/
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

/*!
 * \brief Function used to create empty folder with default values
 *
 * \param[in] idPatient Identifier of the patient to which the folder will be attached
 * \param[out] Empty folder
*/
Folder *createEmptyFolder(int idPatient){
    Folder *folder = (Folder*) malloc(sizeof(Folder));

    folder->folderName = (char*) malloc(LG_MAX_INFO*sizeof(char));
    strcpy(folder->folderName, "Nouveau dossier");
    folder->details = (char*) malloc(LG_MAX_OTHERS*sizeof(char));
    strcpy(folder->details, "Détails");
    folder->pathology = (char*) malloc(LG_MAX_OTHERS*sizeof(char));
    strcpy(folder->pathology, "Pathologie");
    folder->numberOfFiles = 0;
    folder->startOfTreatment = *parseDate(get_current_date());
    folder->idPatient = idPatient;
    folder->ListOfSessions = NULL;

    return folder;

}

/*!
 * \brief Function to predict the next Folder ID
 *
 * \param[out] Future Patient ID
*/
int getFutureFolderId(){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;
    int futureFolderId = 0;

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
    sql = "SELECT seq FROM sqlite_sequence WHERE name = 'folder'";

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error : %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    sqlite3_step(stmt);
    futureFolderId = sqlite3_column_int(stmt,0);

    sqlite3_finalize(stmt);

    //Closing database
    sqlite3_close(db);
    return futureFolderId + 1;
}