/*!
 * \file work_view.h
 * \brief File with functions to initiate the working view
 * (information and tools useful during a session)
*/

#ifndef TEST_GTK_GTK_FUNCTIONS_H
#define TEST_GTK_GTK_FUNCTIONS_H

#include <gtk/gtk.h>
#include "../model/structures.h"
#include "home_view.h"

typedef struct {
    Session *session;
    GtkWidget *dateEntry;
    GtkWidget *hourEntry;
    GtkWidget *stateLabel;
}firstSessionHoursStruct;

/**
 * \brief Structure to add new session
 *
 * Callback structure
*/
typedef struct {
    GtkWidget *notebook;             /**< notebook in which sessions are added */
    GtkWidget *attachmentLabel;      /**< Label to increment number of attachments */
    int folderID;                    /**< ID of the Folder to be edited */
    int patientID;                   /**< ID of the current patient */
}AddNewSessionStruct;



/**
 * \brief Structure to add the first Session to a Folder
 *
 * Callback structure
*/
typedef struct {
    GtkWidget *window;              /**< window to refresh view */
    int folderID;                   /**< ID of the Folder to be edited */
    int patientID;                  /**< ID of the current Patient to refresh view */
}AddFirstSessionStruct;

/**
 * \brief Structure delete a given element
 *
 * Callback structure
*/
typedef struct {
    GtkWidget *window;              /**< window to be refreshed */
    GtkWidget *notebook;            /**< notebook to remove session */
    int patientID;                  /**< ID of the patient to refresh view */
    int folderID;                   /**< ID of the Folder to be deleted */
    int sessionID;                  /**< ID of the Session to be deleted */
    int isFolder;                   /**< Determines if it's a folder */
}DeleteElements;

GtkWidget *setWorkWindow(int fullScreen, int id_patient, int id_folder);
void setWorkEnvironment(Window_id *window_id);

void fillPatientBox(GtkWidget *patientBox, GtkWidget *folderBox, GtkWidget *sessionBox, WorkWindow * workwindow, int id_folder);
void fillFolderBox(GtkWidget *box, GtkWidget *sessionBox, int activeFolder, WorkWindow * workwindow);
void fillSessionBox(GtkWidget *box, GtkWidget *attachmentCounterLabel, WorkWindow * workwindow, int folderID);
void launchWorkView(GtkWidget *but, Window_id *window_id);
void addFirstSessionUI(GtkWidget *button, AddFirstSessionStruct *firstSessionStruct);
void addNewSessionUI(GtkWidget *button, AddNewSessionStruct *newSessionStruct);
void launchDeleteWarning(GtkWidget *button, char *title);
void modifyFirstSessionHours(GtkWidget *entry, firstSessionHoursStruct *fSHS);

void setStartMargin(GtkWidget *widget);
void setTopMargin(GtkWidget *widget);

#endif //TEST_GTK_GTK_FUNCTIONS_H
