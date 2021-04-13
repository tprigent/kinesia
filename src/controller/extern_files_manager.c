/*!
* \file extern_files_manager.c
* \brief File utilities to load, copy and move attachments to the software
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <dirent.h>
#include "extern_files_manager.h"

/*!
 * \brief Copy a given file to the media/ folder of the software.
 *
 * \param[in] from Path of the source file
 * \param[in] patient To which Patient the file concerns
 * \param[in] type Type of the media : profil or attachment
*/
void copyToMedia(char *source_path, Patient *patient, char *type){

    char *stringID;
    FILE *source_stream, *dest_stream;
    int c;
    stringID = (char*) malloc(sizeof(char)*10);

    /* Build the destination path: media/patient-data/{patient_id}/ */
    char *media_path = "../media/patient-data/";
    char *dest_path = (char *) malloc(sizeof(char)*(strlen(media_path)+strlen("/")+strlen(type)+strlen(".xxxx")+10)+sizeof(int)*10);
    strcpy(dest_path, media_path);
    tostring(stringID, (int) patient->id);
    strcat(dest_path, stringID);
    strcat(dest_path, "/");
    mkdir(dest_path, 0700);         // create folder if doesn't exist
    strcat(dest_path, type);
    strcat(dest_path, ".");

    /* Check if old profile picture already exists */
    if(strcmp(type, "profil") == 0){
        removeExistingProfilePicture(media_path, dest_path, source_path);
    }

    /* Add original extension */
    strcat(dest_path, getExtensionFromPath(source_path));

    /* Open source file for reading */
    source_stream = fopen(source_path, "rb");
    if (source_stream == NULL)
    {
        printf("Cannot open source file %s\n", source_path);
    }


    /* Open dest file for writing */
    dest_stream = fopen(dest_path, "wb");
    if (dest_stream == NULL)
    {
        printf("Cannot open dest file %s\n", dest_path);
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
}

/*!
 * \brief Get a file extension from a given path
 *
 * \param[in] path Where the file is located
 * \param[out] File extension
*/
char *getExtensionFromPath(char *path){
    char *result;
    char *last;
    if ((last = strrchr(path, '.')) != NULL) {
        if ((*last == '.') && (last == path))
            return "";
        else {
            result = (char*) malloc(sizeof(char)*strlen(path));
            snprintf(result, sizeof result, "%s", last + 1);
            return result;
        }
    } else {
        return "error";
    }
}

/*!
 * \brief Get a profile photo extension from a given Patient
 *
 * \param[in] patient Patient concerned
 * \param[out] Profile photo extension
*/
char *getProfileExtension(Patient *patient){
    char *stringID = (char*) malloc(sizeof(char)*strlen("000000"));

    char *path = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/")+strlen(patient->firstname)+strlen(patient->name)+strlen("profil")+10));
    char *path_jpeg = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/")+strlen(patient->firstname)+strlen(patient->name)+strlen("profil")+10));
    char *path_JPEG = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/")+strlen(patient->firstname)+strlen(patient->name)+strlen("profil")+10));
    char *path_png = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/")+strlen(patient->firstname)+strlen(patient->name)+strlen("profil")+10));
    char *path_jpg = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/")+strlen(patient->firstname)+strlen(patient->name)+strlen("profil")+10));
    strcpy(path, "../media/patient-data/");
    tostring(stringID, (int) patient->id);
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
    } else if (access(path_jpeg, F_OK) == 0){
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
 * \param[in] patient Patient concerned
 * \param[out] Profile photo path
*/
char *getProfilePhotoPath(Patient *patient){
    char *charID = (char*) malloc(sizeof(char)*10);
    char *photo_path = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/0000/profil.jpeg")+40));
    strcpy(photo_path, "../media/patient-data/");
    tostring(charID, (int) patient->id);
    strcat(photo_path, charID);
    strcat(photo_path, "/");
    strcat(photo_path, "profil");
    strcat(photo_path, getProfileExtension(patient));
    printf("%s\n", photo_path);

    free((char*) charID);
    return(photo_path);
}

char *getMediaPath(Patient *patient){
    char *charID = (char*) malloc(sizeof(char)*10);
    char *media_path = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/0000/")+40));
    strcpy(media_path, "../media/patient-data/");
    tostring(charID, (int) patient->id);
    strcat(media_path, charID);
    strcat(media_path, "/");

    free((char*) charID);
    return(media_path);
}

/*!
 * \brief Remove old profile picture if exists
 *
 * This function remove profile pictures with a different extension
 * than the new one to avoid conflicts.
 *
 * \param[in] media_path Path of the media/ folder
 * \param[in] dest_path Destination path of the profile picture
 * \param[in] source_path Path of the source file (useful to know the extension of the new profile picture)
*/
void removeExistingProfilePicture(char *media_path, char *dest_path, char *source_path){
    char *dest_path_png = (char *) malloc(sizeof(char)*(strlen(media_path)+strlen("/")+strlen("profile")+strlen(".xxxx")+10)+sizeof(int)*10);
    char *dest_path_jpg = (char *) malloc(sizeof(char)*(strlen(media_path)+strlen("/")+strlen("profile")+strlen(".xxxx")+10)+sizeof(int)*10);
    char *dest_path_jpeg = (char *) malloc(sizeof(char)*(strlen(media_path)+strlen("/")+strlen("profile")+strlen(".xxxx")+10)+sizeof(int)*10);

    strcpy(dest_path_png, dest_path);
    strcat(dest_path_png, "png");
    strcpy(dest_path_jpg, dest_path);
    strcat(dest_path_jpg, "jpg");
    strcpy(dest_path_jpeg, dest_path);
    strcat(dest_path_jpeg, "jpeg");

    if(strcmp(getExtensionFromPath(source_path), "jpeg") == 0){
        remove(dest_path_jpg);
        remove(dest_path_png);
    } else if(strcmp(getExtensionFromPath(source_path), "jpg") == 0){
        remove(dest_path_jpeg);
        remove(dest_path_png);
    } else if(strcmp(getExtensionFromPath(source_path), "png") == 0){
        remove(dest_path_jpeg);
        remove(dest_path_jpg);
    }

    free((char*) dest_path_jpeg);
    free((char*) dest_path_jpg);
    free((char*) dest_path_png);
}

char **getMediaDirectoryContent(Patient *patient){
    DIR *d;
    struct dirent *dir;
    char **fileList;
    fileList = (char**) malloc(sizeof(char*)*getNbOfAttachments(patient));
    int i = 0;
    d = opendir(getMediaPath(patient));
    if (d){
        while ((dir = readdir(d)) != NULL){
            if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
                fileList[i] = (char*) malloc(sizeof(char)*100);
                strcpy(fileList[i], dir->d_name);
                printf("%s\n", fileList[i]);
                i++;
            }
        }
    }
    rewinddir(d);
    return fileList;
}

int getNbOfAttachments(Patient *patient){
    DIR *d;
    struct dirent *dir;
    int number = 0;
    d = opendir(getMediaPath(patient));
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

int deleteMediaFolder(Patient *patient) {
    char *path = getMediaPath(patient);
    DIR *d = opendir(path);
    size_t path_len = strlen(path);
    int r = -1;

    if (d) {
        struct dirent *p;

        r = 0;
        while (!r && (p=readdir(d))) {
            int r2 = -1;
            char *buf;
            size_t len;

            /* Skip the names "." and ".." as we don't want to recurse on them. */
            if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
                continue;

            len = path_len + strlen(p->d_name) + 2;
            buf = malloc(len);

            if (buf) {
                struct stat statbuf;

                snprintf(buf, len, "%s/%s", path, p->d_name);
                if (!stat(buf, &statbuf)) {
                    if (S_ISDIR(statbuf.st_mode))
                        r2 = deleteMediaFolder(patient);
                    else
                        r2 = unlink(buf);
                }
                free(buf);
            }
            r = r2;
        }
        closedir(d);
    }

    if (!r)
        r = rmdir(path);

    return r;
}