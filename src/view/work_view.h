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

GtkWidget *setWorkWindow(int id_patient);
void setWorkEnvironment(Window_id *window_id);

void fillPatientBox(GtkWidget *window, GtkWidget *patientBox, GtkWidget *folderBox, GtkWidget *sessionBox, Patient *patient);
void fillFolderBox(GtkWidget *box, int activeFolder, Patient *patient);
void fillSessionBox(GtkWidget *window, GtkWidget *box, int idPatient);
void launchWorkView(GtkWidget *but, Window_id *window_id);
void addNewSessionUI(GtkWidget *button, GtkWidget *notebook);

void setStartMargin(GtkWidget *widget);
void setTopMargin(GtkWidget *widget);

#endif //TEST_GTK_GTK_FUNCTIONS_H
