/*!
* \file editor_views.h
* \brief File with callback functions of the session view
*/

#ifndef SESSION_CONTROLLER_H
#define SESSION_CONTROLLER_H

#include "../model/structures.h"
#include "../patient.h"
#include "../controler/extern_files_manager.h"

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

typedef struct {
    int patientID;
    int actionType;
    GtkWidget *window;
}WarningType;


void launchFolderEditor(Folder *folder);
void launchPatientEditor(GtkWidget *but_edit, Patient_window *patient_window);
void launchNewPatientEditor(GtkWidget *but_new, GtkWidget *window);
void launchFileChooser(GtkWidget *photo_button, char *type);
void launchPatientWarning(GtkWidget *button, WarningType *warning);

#endif
