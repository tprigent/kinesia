/*!
* \file session_controller.h
* \brief File with callback functions of the session view
*/

#ifndef SESSION_CONTROLLER_H
#define SESSION_CONTROLLER_H

#include "structures.h"
#include "patient.h"

/**
 * \brief Structure to pass a patient and a window in a callback function
 *
 * This structure is used to pass many arguments in a callback function which only
 * have one argument.
*/
typedef struct {
    Patient *patient;
    GtkWidget *window;
    int origin;         // 0 if new patient, 1 if edition of patient
}Patient_window;


void launchFolderEditor(Folder *folder);
void launchPatientEditor(GtkWidget *but_edit, Patient_window *patient_window);
void launchNewPatientEditor(GtkWidget *but_new, GtkWidget *window);
void launchSessionView(GtkWidget *but, GtkWidget *window);
void launchPatientView(GtkWidget *but, GtkWidget *window);
void launchFileChooser(GtkWidget *photo_button, char *type);
void copyToMedia(char *from, Patient *patient, char *type);
char *getExtensionFromPath(char *path);
char *getProfileExtension(Patient *patient);

#endif
