/*!
* \file extern_files_manager.c
* \brief File utilities to load, copy and move attachments to the software
*/

#include <libc.h>
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

    /* Build the destination path: media/name-firstname/ */
    char *media_path = "../media/patient-data/";
    char *dest_path = (char *) malloc(sizeof(char)*(strlen(media_path)+strlen("/")+strlen(type)+strlen(".xxxx")+10)+sizeof(int)*10);
    strcpy(dest_path, media_path);
    tostring(stringID, (int) patient->id);
    strcat(dest_path, stringID);
    strcat(dest_path, "/");
    mkdir(dest_path, 0700);         // create folder if doesn't exist
    strcat(dest_path, type);
    strcat(dest_path, ".");
    strcat(dest_path, getExtensionFromPath(source_path));

    /* Open source file for reading */
    source_stream = fopen(source_path, "rb");
    if (source_stream == NULL)
    {
        printf("Cannot open file %s\n", source_path);
    }

    /* Open dest file for writing */
    dest_stream = fopen(dest_path, "wb");
    if (dest_stream == NULL)
    {
        printf("Cannot open file %s\n", dest_path);
    }

    /* Copy file */
    c = fgetc(source_stream);
    while (c != EOF)
    {
        fputc(c, dest_stream);
        c = fgetc(dest_stream);
    }

    printf("Contents copied to %s\n", dest_path);

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
    char *path = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/")+strlen(patient->firstname)+strlen(patient->name)+strlen("profil")+10));
    char *pathJPEG = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/")+strlen(patient->firstname)+strlen(patient->name)+strlen("profil")+10));
    char *pathPNG = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/")+strlen(patient->firstname)+strlen(patient->name)+strlen("profil")+10));
    char *pathJPG = (char*) malloc(sizeof(char)*(strlen("../media/patient-data/")+strlen(patient->firstname)+strlen(patient->name)+strlen("profil")+10));
    strcpy(path, "cat ");
    strcat(path, "../media/patient-data/");
    strcat(path, patient->firstname);
    strcat(path, "-");
    strcat(path, patient->name);
    strcat(path, "/");

    strcat(pathJPEG, path);
    strcat(pathJPEG, "profil.jpeg");
    strcat(pathJPG, path);
    strcat(pathJPG, "profil.jpg");
    strcat(pathPNG, path);
    strcat(pathPNG, "profil.png");

    if(system(pathJPEG) == 0) return ".jpeg";
    else if(system(pathJPG) == 0) return ".jpg";
    else if(system(pathPNG) == 0) return ".png";
    else return ".error";

}

char *getProfilePhotoPath(Patient *patient){
    char *photo_path = (char*) malloc(sizeof(char)*(strlen(patient->firstname)+strlen(patient->name)+100));
    strcpy(photo_path, "../media/patient-data/");
    strcat(photo_path, patient->firstname);
    strcat(photo_path, "-");
    strcat(photo_path, patient->name);
    strcat(photo_path, "/");
    strcat(photo_path, "profil.jpeg");
    //strcat(photo_path, getProfileExtension(patient));
    printf("%s\n", photo_path);
    return(photo_path);
}