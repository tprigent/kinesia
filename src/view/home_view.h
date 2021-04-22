/*!
* \file home_view.h
* \brief File to initiate the homepage view (calendar, patient list, ...)
*/

#ifndef LOGICIEL_KINE_PATIENT_VIEW_H
#define LOGICIEL_KINE_PATIENT_VIEW_H

#include <gtk/gtk.h>
#include "../model/structures.h"

/**
 * \brief Structure to pass a Session and a Patient to the callback
 *
 * This structure is used to pass many arguments in a callback function which has only
 * one argument.
*/
typedef struct {
    GtkWidget *window;      /**< Parent window to be reload after changes */
    int patientID;          /**< ID of the Patient to be edited */
    int folderID;           /**< ID of the Folder to be edited */
}Window_id;

typedef struct {
    GtkWidget *notebook;
    GtkWidget *entry;
    GtkWidget *window;
}SearchParam;

GtkWidget *setHomeWindow(int firstLoad, int fullScreen, int cssMode);
void setHomeEnvironment(GtkWidget *window, int cssMode);
void launchHomeView(GtkWidget *but, GtkWidget *window);

Session *createEmptySession(int idFolder);
void processSearch(GtkWidget *button, SearchParam *search);

#endif //LOGICIEL_KINE_PATIENT_VIEW_H
