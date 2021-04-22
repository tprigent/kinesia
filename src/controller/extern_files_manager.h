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
#include "../controller/extern_files_manager.h"
#include "../model/structures.h"

void copyToMedia(char *source_path, int patientID, int folderID, char *type);
char *getExtensionFromPath(char *path);
char *getProfileExtension(int patientID);
char *getPatientMediaPath(int patientID);
char *getFolderMediaPath(int patientID, int folderID);
char *getProfilePhotoPath(int patientID, int folder);
void removeExistingProfilePicture(char *media_path, char *dest_path, char *source_path);
char **getMediaDirectoryContent(int patientID, int folderID);
int getNbOfAttachments(int patientID, int folderID);
void deleteMediaFolder(int patientID);
char *replaceWhitespaces(char *filename);

#endif //LOGICIEL_KINE_EXTERN_FILES_MANAGER_H
