//
// Created by Théo Prigent on 12/03/2021.
//

#include "extern_files_manager.h"

/*!
 * \brief Copy a given file to the media/ folder of the software.
 *
 * \param[in] from Path of the source file
 * \param[in] patient To which Patient the file concerns
 * \param[in] type Type of the media : profil or attachment
*/
void copyToMedia(char *from, Patient *patient, char *type){

    /* Build the destination path: media/name-firstname/ */
    char *media_path = " ../media/";
    char *dest = (char *) malloc(sizeof(char)*(strlen(patient->firstname)+strlen(patient->name)+strlen(type)+2*strlen("-")+strlen("/")));
    strcpy(dest, media_path);
    strcat(dest, patient->firstname);
    strcat(dest, "-");
    strcat(dest, patient-> firstname);
    strcat(dest, "/");

    /* Create directory media/name-firstname/ */
    char *mkdir = "mkdir -p ";
    char *mkdir_command = (char*) malloc(sizeof(char)*(strlen(dest)+strlen(mkdir)));
    strcpy(mkdir_command, mkdir);   // command = <mkdir -p >
    strcat(mkdir_command, dest);    // command = <mkdir -p media/name-firstname/>
    system(mkdir_command);

    /* Build the copy command: cp source_path/file media/name-firstname/ */
    char *cp = "cp ";
    char *cp_command = (char*) malloc(sizeof(char)*(strlen(cp)+strlen(dest)+strlen(from)+strlen(type)+strlen(getExtensionFromPath(from))+1));
    strcpy(cp_command, cp);                             // command = <cp >
    strcat(cp_command, "\"");                           // command = <cp ">
    strcat(cp_command, from);                           // command = <cp "source_path/file>
    strcat(cp_command, "\"");                           // command = <cp "source_path/file">
    strcat(cp_command, dest);                           // command = <cp "source_path/file" media/name-firstname/>
    strcat(cp_command, type);                           // command = <cp "source_path/file" media/name-firstname/type>
    strcat(cp_command, ".");                            // command = <cp "source_path/file" media/name-firstname/type.>
    strcat(cp_command, getExtensionFromPath(from));     // command = <cp "source_path/file" media/name-firstname/type.ext>
    system(cp_command);

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
    char *path = (char*) malloc(sizeof(char)*(strlen("../media/")+strlen(patient->firstname)+strlen(patient->name)+strlen("profil")+10));
    char *pathJPEG = (char*) malloc(sizeof(char)*(strlen("../media/")+strlen(patient->firstname)+strlen(patient->name)+strlen("profil")+10));
    char *pathPNG = (char*) malloc(sizeof(char)*(strlen("../media/")+strlen(patient->firstname)+strlen(patient->name)+strlen("profil")+10));
    char *pathJPG = (char*) malloc(sizeof(char)*(strlen("../media/")+strlen(patient->firstname)+strlen(patient->name)+strlen("profil")+10));
    strcpy(path, "cat ");
    strcat(path, "../media/");
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
    strcpy(photo_path, "../media/");
    strcat(photo_path, patient->firstname);
    strcat(photo_path, "-");
    strcat(photo_path, patient->name);
    strcat(photo_path, "/");
    strcat(photo_path, "profil.jpeg");
    //strcat(photo_path, getProfileExtension(patient));
    printf("%s\n", photo_path);
    return(photo_path);
}