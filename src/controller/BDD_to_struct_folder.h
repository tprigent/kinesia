/*!
* \file BDD_to_struct_folder.h
* \brief Functions with SQL requests to fill Folder structure.
*/

#ifndef LOGICIEL_KINE_BDD_TO_STRUCT_FOLDER_H
#define LOGICIEL_KINE_BDD_TO_STRUCT_FOLDER_H

#include "../model/structures.h"

Folder* getFolder(int idFolder);
char* getNameFolder(int idFolder);
int* getIdFolder(int idPatient);

#endif //LOGICIEL_KINE_BDD_TO_STRUCT_FOLDER_H
