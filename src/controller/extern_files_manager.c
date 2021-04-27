/*!
* \file extern_files_manager.c
* \brief File utilities to load, copy and move attachments to the software
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <dirent.h>
#include <libgen.h>
#include <ctype.h>
#include "extern_files_manager.h"

/*!
 * \brief Copy a given file to the media folder of the software.
 *
 * The copied file automatically goes into media/patient-data/patientID/folderID/
 *
 * \param[in] source_path : Path of the source file
 * \param[in] patientID : To which Patient the file concerns
 * \param[in] folderID : To which Folder the file concerns
 * \param[in] type : Type of the media : profile or attachment
*/
int copyToMedia(char *source_path, int patientID, int folderID, char *type){

    FILE *source_stream = NULL, *dest_stream = NULL;
    int c;
    char *patientMediaPath = getPatientMediaPath(patientID);
    char *folderMediaPath = getFolderMediaPath(patientID, folderID);
    char *stringID = (char*) malloc(sizeof(char)*10);
    char *dest_path = (char*) malloc(sizeof(char)*(strlen(patientMediaPath)+100));

    if(strcmp(type, "profil") == 0){
        strcpy(dest_path, patientMediaPath);
        strcat(dest_path, "profil.");
        removeExistingProfilePicture(dest_path);
        strcat(dest_path, getExtensionFromPath(source_path));
    } else {
        strcpy(dest_path, folderMediaPath);
        strcat(dest_path, replaceWhitespaces(basename(source_path)));
    }

    /* Open source file for reading */
    source_stream = fopen(source_path, "rb");
    if (source_stream == NULL)
    {
        printf("Cannot open source file %s\n", source_path);
        return 0;
    }


    /* Open dest file for writing */
    dest_stream = fopen(dest_path, "wb");
    if (dest_stream == NULL)
    {
        printf("Cannot open dest file %s\n", dest_path);
        return 0;
    }


    /* Copy file */
    while(1)
    {
        c=fgetc(source_stream);
        if(c==EOF) break;
        fputc(c,dest_stream);
    }

    printf("Contents copied to %s\n", dest_path);

    /* Close files */
    fclose(source_stream);
    fclose(dest_stream);


    /* Free chars */
    free((char*) stringID);
    free((char*) dest_path);

    return 1;
}

/*!
 * \brief Get a file extension from a given path
 * Without the separating dot
 *
 * \param[in] path : Where the file is located
 * \param[out] File extension, "error" if problem encountered
*/
char *getExtensionFromPath(char *path){
    char *result;
    char *last = strrchr(path, '.');
    result = (char*) malloc(sizeof(char)*strlen(path));
    snprintf(result, sizeof result, "%s", last + 1);
    return result;
}

/*!
 * \brief Get a profile photo extension from a given Patient
 * With the final dot.
 *
 * \param[in] patientID Identifier of the Patient concerned
 * \param[out] Profile photo extension, returns ".error" if format not supported
*/
char *getProfileExtension(int patientID){
    char *stringID = (char*) malloc(sizeof(char)*strlen("000000"));

    char *path = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/")+10+strlen("profil")+10));
    char *path_jpeg = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/")+10+strlen("profil")+10));
    char *path_JPEG = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/")+10+strlen("profil")+10));
    char *path_png = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/")+10+strlen("profil")+10));
    char *path_jpg = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/")+10+strlen("profil")+10));
    strcpy(path, "../media/patient-data/");
    tostring(stringID, patientID);
    strcat(path, stringID);
    strcat(path, "/");

    strcpy(path_jpeg, path);
    strcat(path_jpeg, "profil.jpeg");
    strcpy(path_JPEG, path);
    strcat(path_JPEG, "profil.JPEG");
    strcpy(path_jpg, path);
    strcat(path_jpg, "profil.jpg");
    strcpy(path_png, path);
    strcat(path_png, "profil.png");

    free((char*) path);
    free((char*) stringID);
    if(access(path_jpeg, F_OK) == 0 || access(path_JPEG, F_OK) == 0 ) {
        free((char*) path_jpeg);
        free((char*) path_JPEG);
        free((char*) path_jpg);
        free((char*) path_png);
        return ".jpeg";
    } else if (access(path_jpg, F_OK) == 0){
        free((char*) path_jpeg);
        free((char*) path_JPEG);
        free((char*) path_jpg);
        free((char*) path_png);
        return ".jpg";
    } else if (access(path_png, F_OK) == 0){
        free((char*) path_jpeg);
        free((char*) path_JPEG);
        free((char*) path_jpg);
        free((char*) path_png);
        return ".png";
    } else {
        free((char*) path_jpeg);
        free((char*) path_JPEG);
        free((char*) path_jpg);
        free((char*) path_png);
        return ".error";
    }

}

/*!
 * \brief Get the path of the profile photo from a given Patient
 *
 * \param[in] patientID : Identifier of the concerned Patient
 * \param[out] Profile photo path
*/
char *getProfilePhotoPath(int patientID){
    char *photo_path = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/0000/profil.jpeg")+40));
    strcpy(photo_path, getPatientMediaPath(patientID));
    strcat(photo_path, "profil");
    strcat(photo_path, getProfileExtension(patientID));

    return photo_path;
}

/*!
 * \brief Get the path the media path of a given Patient
 *
 * \param[in] patientID Identifier of the concerned Patient
 * \param[out] Media path of the Patient
*/
char *getPatientMediaPath(int patientID){
    char *charID = (char*) malloc(sizeof(char)*10);
    char *media_path = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/0000/")+40));
    strcpy(media_path, "../media/patient-data/");
    tostring(charID, (int) patientID);
    strcat(media_path, charID);
    strcat(media_path, "/");

    #if defined(_WIN32)
        mkdir(media_path);
    #else
        mkdir(media_path, 0700);
    #endif

    free((char*) charID);
    return(media_path);
}

/*!
 * \brief Get the path to the media of a given Patient for a given Folder
 *
 * \param[in] patientID : Identifier of the concerned Patient
 * \param[in] folderID : Identifier of the concerned Folder
 * \param[out] Folder media path
*/
char *getFolderMediaPath(int patientID, int folderID){
    char *charID = (char*) malloc(sizeof(char)*10);
    char *patientMediaPath = getPatientMediaPath(patientID);

    char *folderMediaPath = (char*) malloc(sizeof(char)*(strlen(patientMediaPath)+100));

    strcpy(folderMediaPath, patientMediaPath);
    tostring(charID, folderID);
    strcat(folderMediaPath, charID);
    strcat(folderMediaPath, "/");

    #if defined(_WIN32)
        mkdir(folderMediaPath);
    #else
        mkdir(folderMediaPath, 0700);
    #endif

    return folderMediaPath;
}

/*!
 * \brief Remove old profile picture if exists
 *
 * \param[in] photo_path Path of the profile picture ending with "/profil."
*/
void removeExistingProfilePicture(char *dest_path){
    char *dest_path_png = (char *) malloc(sizeof(char)*(strlen(dest_path)+strlen("/")+strlen("profile")+strlen(".xxxx")+10)+sizeof(int)*10);
    char *dest_path_jpg = (char *) malloc(sizeof(char)*(strlen(dest_path)+strlen("/")+strlen("profile")+strlen(".xxxx")+10)+sizeof(int)*10);
    char *dest_path_jpeg = (char *) malloc(sizeof(char)*(strlen(dest_path)+strlen("/")+strlen("profile")+strlen(".xxxx")+10)+sizeof(int)*10);
    char *dest_path_JPEG = (char *) malloc(sizeof(char)*(strlen(dest_path)+strlen("/")+strlen("profile")+strlen(".xxxx")+10)+sizeof(int)*10);
    strcpy(dest_path_png, dest_path);
    strcat(dest_path_png, "png");
    strcpy(dest_path_jpg, dest_path);
    strcat(dest_path_jpg, "jpg");
    strcpy(dest_path_jpeg, dest_path);
    strcat(dest_path_jpeg, "jpeg");
    strcpy(dest_path_JPEG, dest_path);
    strcat(dest_path_JPEG, "JPEG");

    remove(dest_path_jpg);
    remove(dest_path_png);
    remove(dest_path_jpeg);
    remove(dest_path_JPEG);

    free((char*) dest_path_jpeg);
    free((char*) dest_path_JPEG);
    free((char*) dest_path_jpg);
    free((char*) dest_path_png);
}

/*!
 * \brief Get the content of a media directory
 *
 * Returns an array of the file list excluding "." and ".." files.
 *
 * \param[in] patientID : Identifier of the concerned Patient
 * \param[in] folderID : Identifier of the concerned Folder
 * \param[out] List of files related to the Folder and the Patient
*/
char **getMediaDirectoryContent(int patientID, int folderID){
    DIR *d;
    struct dirent *dir;
    char **fileList;
    fileList = (char**) malloc(sizeof(char*)*getNbOfAttachments(patientID, folderID));
    int i = 0;
    d = opendir(getFolderMediaPath(patientID, folderID));
    if (d){
        while ((dir = readdir(d)) != NULL){
            if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
                fileList[i] = (char*) malloc(sizeof(char)*100);
                strcpy(fileList[i], dir->d_name);
                i++;
            }
        }
    }
    rewinddir(d);
    return fileList;
}

/*!
 * \brief Get the number of attachments for a given Folder
 *
 * Counts the number of files of a specific directory
 *
 * \param[in] patientID : Identifier of the concerned Patient
 * \param[in] folderID : Identifier of the concerned Folder
 * \param[out] Number of attachment relative to the Folder
*/
int getNbOfAttachments(int patientID, int folderID){
    DIR *d;
    struct dirent *dir;
    int number = 0;
    d = opendir(getFolderMediaPath(patientID, folderID));
    int i = 0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            number++;
        }
        closedir(d);
    }
    number -=2;     // Don't want to count . and .. files
    return number;
}

/*!
 * \brief Delete recursively all the content of the Patient media directory
 *
 * \param[in] patientID Identifier of the concerned Patient
 * \todo: support deletion on Window
*/
void deleteMediaFolder(int patientID) {
    char *path = getPatientMediaPath(patientID);

    if(strcmp(OS, "linux") == 0 || strcmp(OS, "macOS") == 0) {
        char *cmd = (char*) malloc(50*sizeof(char));
        strcpy(cmd, "rm -R ");
        strcat(cmd, path);
        system(cmd);
    }
    else if(strcmp(OS, "Windows") == 0){}

}

/*!
 * \brief Replace whitespaces in a given char with underscores
 *
 * \param[in] filename : Input char with whitespaces
 * \param[out] Output char with underscores
*/
char *replaceWhitespaces(char *filename){
    int i=0;
    while(filename[i])
    {
        if (isspace(filename[i]))
            filename[i]='_';
        i++;
    }
    return filename;
}
