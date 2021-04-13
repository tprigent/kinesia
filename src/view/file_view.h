/*!
* \file file_view.c
* \brief View to display medical attachments and tools
*/

#ifndef LOGICIEL_KINE_FILE_VIEW_H
#define LOGICIEL_KINE_FILE_VIEW_H

#include <gtk/gtk.h>
#include "../model/structures.h"
#include "../controller/extern_files_manager.h"

GtkWidget *setFileWindow(GtkWidget *parentDialog, char *filename, Patient *patient);
void setFileViewerEnvironment(GtkWidget *window, char *filename, Patient *patient);

#endif //LOGICIEL_KINE_FILE_VIEW_H
