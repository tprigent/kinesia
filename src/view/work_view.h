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
    GtkWidget *notebook;      /**< notebook in which sessions are added */
    int folderID;           /**< ID of the Folder to be edited */
}AddNewSessionStruct;

typedef struct {
    GtkWidget *window;      /**< window to refresh view */
    int folderID;           /**< ID of the Folder to be edited */
    int patientID;          /**< ID of the current Patient to refresh view */
}AddFirstSessionStruct;

GtkWidget *setWorkWindow(int id_patient, int id_folder);
void setWorkEnvironment(Window_id *window_id);

void fillPatientBox(GtkWidget *window, GtkWidget *patientBox, GtkWidget *folderBox, GtkWidget *sessionBox, Patient *patient, int id_folder);
void fillFolderBox(GtkWidget *window, GtkWidget *box, GtkWidget *sessionBox, int activeFolder, Patient *patient);
void fillSessionBox(GtkWidget *window, GtkWidget *box, Patient *patient, int folderID);
void launchWorkView(GtkWidget *but, Window_id *window_id);
void addFirstSessionUI(GtkWidget *button, AddFirstSessionStruct *firstSessionStruct);
void addNewSessionUI(GtkWidget *button, AddNewSessionStruct *newSessionStruct, Patient *patient);

void setStartMargin(GtkWidget *widget);
void setTopMargin(GtkWidget *widget);

#endif //TEST_GTK_GTK_FUNCTIONS_H
