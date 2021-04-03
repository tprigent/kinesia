/*!
* \file folder.c
* \brief File with functions to allocate, fill from database requests, and free Folder structure
*/

#include "folder_manager.h"
#include "patient_manager.h"
#include <sqlite3.h>
#include "structures.h"
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

Folder *createEmptyFolder(int idPatient){
    Folder *folder = (Folder*) malloc(sizeof(Folder));

    folder->folderName = (char*) malloc(LG_MAX_INFO*sizeof(char));
    strcpy(folder->folderName, "Nouveau dossier");
    folder->details = (char*) malloc(LG_MAX_OTHERS*sizeof(char));
    strcpy(folder->details, "Détails");
    folder->pathology = (char*) malloc(LG_MAX_OTHERS*sizeof(char));
    strcpy(folder->pathology, "Pathologie");
    folder->numberOfFiles = 0;
    folder->startOfTreatment.day = 1;
    folder->startOfTreatment.month = 1;
    folder->startOfTreatment.year = 1900;
    folder->idPatient = idPatient;
    folder->ListOfSessions = NULL;

    return folder;

}