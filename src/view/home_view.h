//
// Created by julien on 02/03/2021.
//

#ifndef LOGICIEL_KINE_PATIENT_VIEW_H
#define LOGICIEL_KINE_PATIENT_VIEW_H

#include <gtk/gtk.h>
#include "../model/structures.h"

typedef struct {
    GtkWidget *window;
    int id;
    Session *session;
}Window_id;

GtkWidget *setHomeWindow();
void setHomeEnvironment(GtkWidget *window);
void launchHomeView(GtkWidget *but, GtkWidget *window);

Session *createEmptySession();

#endif //LOGICIEL_KINE_PATIENT_VIEW_H
