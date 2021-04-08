/*!
* \file folder_manager.h
* \brief File with functions to allocate, fill from database requests, and free Folder structure
*/

#ifndef LOGICIEL_KINE_FOLDER_H
#define LOGICIEL_KINE_FOLDER_H

#include "structures.h"

/*allocation's functions*/
int allocateFolder(Folder **d);
int allocateStringFolder(char **string, int lg);

int setFolder(Folder *d, char * folderName, char * pathology, char * details, int stDay, int stMonth, int stYear, int nbFiles, int idF, int idP);
Folder *createEmptyFolder(int idPatient);

#endif //LOGICIEL_KINE_FOLDER_H
