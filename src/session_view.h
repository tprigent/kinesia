/*!
* \file session_view.h
* \brief File with functions to initiate the session view
*/

#ifndef TEST_GTK_GTK_FUNCTIONS_H
#define TEST_GTK_GTK_FUNCTIONS_H

#include <gtk/gtk.h>
#include "structures.h"

GtkWidget *setPatientWindow();
void setPatientEnvironment(GtkWidget *window);

GtkWidget *setSessionWindow();
void setSessionEnvironment(GtkWidget *window);

void createPatientInfoWindow(GtkWidget *box, Patient *patient);
void createFolderInfoWindow(GtkWidget *box);
void createSessionInfoWindow(GtkWidget *box);

void setStartMargin(GtkWidget *widget);
void setTopMargin(GtkWidget *widget);
void setBottomMargin(GtkWidget *widget);

#endif //TEST_GTK_GTK_FUNCTIONS_H
