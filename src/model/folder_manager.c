/*!
* \file folder_manager.c
* \brief File with functions to allocate, fill from database requests, and free Folder structure
*/

#include "folder_manager.h"
#include "patient_manager.h"
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



