/*!
* \file editor_views.h
* \brief File with callback functions to launch dialog boxes across the software
*/

#ifndef SESSION_CONTROLLER_H
#define SESSION_CONTROLLER_H

#include "file_view.h"
#include "../model/structures.h"
#include "../model/patient_manager.h"
#include "../controller/BDD_to_struct_patient.h"
#include "../controller/extern_files_manager.h"

/**
 * \brief Structure to pass a patient and a window in a callback function
 *
 * This structure is used to pass many arguments in a callback function which has only
 * one argument.
*/
typedef struct {
    Patient *patient;       /**< Patient to be edited */
    GtkWidget *window;      /**< Parent window to be reload after changes */
    int origin;             /**< 0 if new patient, 1 if edition of existing Patient */
}Patient_window;

/**
 * \brief Structure to choose the warning
 *
 * This structure enables the callback to act on the patient, choose the action to be done
 * and reload the parent window after changes.
*/
typedef struct {
    int patientID;         /**< ID of the Patient to be deleted or archived */
    int actionType;        /**< Type of warning: 0 = "delete" or 1 = "archive" */
    GtkWidget *window;     /**< Parent window to be reload after changes */
}WarningType;

typedef struct{
    Folder *folder;
    int edit_new;
    GtkWidget *window;
}FolderEditorStruct;

typedef struct{
    int idPatient;
    GtkWidget *window;
}IdPatientCallback;

/**
 * \brief Structure to choose the type of media to open
 *
 * This structure enables the callback to know what type of media to process
 * and which Patient it is to store it in the right place
*/
typedef struct {
    Patient *patient;             /**< Patient concerned */
    int folderID;                 /**< Identifier of the concerned Folder */
    int mediaType;                /**< Type of media to be stored in the software: 0 = "profile" 1 = other */
    GtkWidget *counterLabel;      /**< Label containing the number of files */
}MediaType;

void launchFolderEditor(GtkWidget *button, FolderEditorStruct *foldEditStruct);
void launchNewFolderEditor(GtkWidget *button, IdPatientCallback *idPatientCall);
void launchPatientEditor(GtkWidget *but_edit, Patient_window *patient_window);
void launchNewPatientEditor(GtkWidget *but_new, GtkWidget *window);
void launchFileChooser(GtkWidget *photo_button, MediaType *mediaChooser);
void launchCalendar(GtkWidget *button, GtkWidget *entry);
void launchPatientWarning(GtkWidget *button, WarningType *warning);
void launchSettingsEditor(GtkWidget *button, GtkWidget *window);
void launchAttachmentListViewer(GtkWidget *button, MediaType *attachmentProperties);

#endif
