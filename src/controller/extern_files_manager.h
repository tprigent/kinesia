/*!
* \file extern_files_manager.h
* \brief File utilities to load, copy and move attachments to the software
*/

#ifndef LOGICIEL_KINE_EXTERN_FILES_MANAGER_H
#define LOGICIEL_KINE_EXTERN_FILES_MANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "display_helpers.h"
#include "../model/structures.h"

void copyToMedia(char *source_path, Patient *patient, char *type);
char *getExtensionFromPath(char *path);
char *getProfileExtension(Patient *patient);
char *getMediaPath(Patient *patient);
char *getProfilePhotoPath(Patient *patient);
void removeExistingProfilePicture(char *media_path, char *dest_path, char *source_path);
int deleteMediaFolder(Patient *patient);

#endif //LOGICIEL_KINE_EXTERN_FILES_MANAGER_H
