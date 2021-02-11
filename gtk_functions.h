//
// Created by julien on 02/02/2021.
//

#ifndef TEST_GTK_GTK_FUNCTIONS_H
#define TEST_GTK_GTK_FUNCTIONS_H

#include <gtk/gtk.h>
#include "Structures.h"

void setMainWindow(GtkWidget *window);

void createPatientInfoWindow(GtkWidget *box, Patient *patient);
void createFolderInfoWindow(GtkWidget *box);
void createSessionInfoWindow(GtkWidget *box);

void setStartMargin(GtkWidget *widget);

#endif //TEST_GTK_GTK_FUNCTIONS_H
