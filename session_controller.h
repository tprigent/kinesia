/*!
* \file session_controller.h
* \brief File with callback functions of the session view
*/

#ifndef SESSION_CONTROLLER_H
#define SESSION_CONTROLLER_H

#include "structures.h"


void launchFolderEditor();
void launchPatientEditor(GtkWidget *but_edit, Patient *patient);

#endif
