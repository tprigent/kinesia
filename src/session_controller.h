/*!
* \file session_controller.h
* \brief File with callback functions of the session view
*/

#ifndef SESSION_CONTROLLER_H
#define SESSION_CONTROLLER_H

#include "structures.h"
#include "patient.h"


void launchFolderEditor(Folder *folder);
void launchPatientEditor(GtkWidget *but_edit, Patient *patient);
void launchNewPatientEditor(GtkWidget *but_new);
void launchSessionView(GtkWidget *but, GtkWidget *window);
void launchPatientView(GtkWidget *but, GtkWidget *window);
void launchFileChooser(GtkWidget *photo_button, char *type);
void copyToMedia(char *from, char *name, char *firstname, char *type);
char *getExtension(char *str);

#endif
