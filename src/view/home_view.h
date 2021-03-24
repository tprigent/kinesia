/*!
* \file home_views.h
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
    Session *session;       /**< Session to be edited */
    int session_type;       /**< 0 new session; 1 edit session */
}Window_id;

GtkWidget *setHomeWindow();
void setHomeEnvironment(GtkWidget *window);
void launchHomeView(GtkWidget *but, GtkWidget *window);

Session *createEmptySession();

#endif //LOGICIEL_KINE_PATIENT_VIEW_H
