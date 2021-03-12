//
// Created by julien on 02/03/2021.
//

#ifndef LOGICIEL_KINE_PATIENT_VIEW_H
#define LOGICIEL_KINE_PATIENT_VIEW_H

#include <gtk/gtk.h>
#include "structures.h"

GtkWidget *setPatientWindow();
void setPatientEnvironment(GtkWidget *window);
void launchPatientView(GtkWidget *but, GtkWidget *window);

#endif //LOGICIEL_KINE_PATIENT_VIEW_H
