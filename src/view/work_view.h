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

GtkWidget *setWorkWindow(int id_patient, Session *session, int session_type);
void setWorkEnvironment(Window_id *window_id);

void fillPatientBox(GtkWidget *window, GtkWidget *box, Patient *patient, int session_type);
void fillFolderBox(GtkWidget *box);
void fillSessionBox(GtkWidget *window, GtkWidget *box, Session *session, int idPatient, int session_type);
void launchWorkView(GtkWidget *but, Window_id *window_id);
void addNewSessionUI(GtkWidget *button, GtkWidget *notebook);

void setStartMargin(GtkWidget *widget);
void setTopMargin(GtkWidget *widget);

#endif //TEST_GTK_GTK_FUNCTIONS_H
