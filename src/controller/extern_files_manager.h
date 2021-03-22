//
// Created by Théo Prigent on 12/03/2021.
//

#ifndef LOGICIEL_KINE_EXTERN_FILES_MANAGER_H
#define LOGICIEL_KINE_EXTERN_FILES_MANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../model/structures.h"

void copyToMedia(char *from, Patient *patient, char *type);
char *getExtensionFromPath(char *path);
char *getProfileExtension(Patient *patient);
char *getProfilePhotoPath(Patient *patient);

#endif //LOGICIEL_KINE_EXTERN_FILES_MANAGER_H
