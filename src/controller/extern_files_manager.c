/*!
* \file extern_files_manager.c
* \brief File utilities to load, copy and move attachments to the software
*/

#include <libc.h>
#include <regex.h>
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
    char *pathJPEG = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/")+strlen(patient->firstname)+strlen(patient->name)+strlen("profil")+10));
    char *pathPNG = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/")+strlen(patient->firstname)+strlen(patient->name)+strlen("profil")+10));
    char *pathJPG = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/")+strlen(patient->firstname)+strlen(patient->name)+strlen("profil")+10));
    strcat(path, "../media/patient-data/");
    tostring(stringID, (int) patient->id);
    strcat(path, stringID);
    strcat(path, "/");

    strcat(pathJPEG, path);
    strcat(pathJPEG, "profil.jpeg");
    strcat(pathJPG, path);
    strcat(pathJPG, "profil.jpg");
    strcat(pathPNG, path);
    strcat(pathPNG, "profil.png");

    free((char*) path);
    free((char*) stringID);
    if(access(pathJPEG, F_OK) == 0 ) {
        free((char*) pathJPEG);
        free((char*) pathJPG);
        free((char*) pathPNG);
        return ".jpeg";
    } else if (access(pathJPG, F_OK) == 0){
        free((char*) pathJPEG);
        free((char*) pathJPG);
        free((char*) pathPNG);
        return ".jpg";
    } else if (access(pathPNG, F_OK) == 0){
        free((char*) pathJPEG);
        free((char*) pathJPG);
        free((char*) pathPNG);
        return ".png";
    } else {
        free((char*) pathJPEG);
        free((char*) pathJPG);
        free((char*) pathPNG);
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
    char *photo_path = (char*) malloc(sizeof(char)*(strlen(patient->firstname)+strlen(patient->name)+100));
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