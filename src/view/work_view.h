/*!
* \file work_view.h
* \brief File with functions to initiate the session view
*/

#ifndef TEST_GTK_GTK_FUNCTIONS_H
#define TEST_GTK_GTK_FUNCTIONS_H

#include <gtk/gtk.h>
#include "../model/structures.h"

GtkWidget *setWorkWindow();
void setWorkEnvironment(GtkWidget *window);

void fillPatientBox(GtkWidget *window, GtkWidget *box, Patient *patient);
void fillFolderBox(GtkWidget *box);
void fillSessionBox(GtkWidget *box);
void launchWorkView(GtkWidget *but, GtkWidget *window);

void setStartMargin(GtkWidget *widget);
void setTopMargin(GtkWidget *widget);
void setBottomMargin(GtkWidget *widget);

#endif //TEST_GTK_GTK_FUNCTIONS_H
