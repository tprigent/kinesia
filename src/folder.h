//
// Created by paul on 01/03/2021.
//

#ifndef LOGICIEL_KINE_FOLDER_H
#define LOGICIEL_KINE_FOLDER_H

#include "model/structures.h"
//#include "session.h"

/*allocation's functions*/
int allocateFolder(Folder **d);
int allocateStringFolder(char **string, int lg);

int setFolder(Folder *d, char * folderName, char * pathology, char * details, int stDay, int stMonth, int stYear, int nbFiles, int idF);

int addFolder(Folder *folder);

#endif //LOGICIEL_KINE_FOLDER_H
