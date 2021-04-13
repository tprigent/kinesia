/*!
* \file file_view.c
* \brief View to display medical attachments and tools
*/

#ifndef LOGICIEL_KINE_FILE_VIEW_H
#define LOGICIEL_KINE_FILE_VIEW_H

#include <gtk/gtk.h>

GtkWidget *setFileWindow(char *filename);
void setFileViewerEnvironment(GtkWidget *window);

#endif //LOGICIEL_KINE_FILE_VIEW_H
