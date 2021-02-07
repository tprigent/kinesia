//
// Created by julien on 02/02/2021.
//

#include <stdlib.h>
#include "gtk_functions.h"
#include <gtk/gtk.h>


void setMainWindow(GtkWidget *window){
    gtk_window_set_title(GTK_WINDOW(window), "Kinesia");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 600);
    gtk_window_maximize(GTK_WINDOW(window));
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

void createPatientInfoWindow(GtkWidget *box){

}

void createFolderInfoWindow(GtkWidget *box){

}

void createSessionInfoWindow(GtkWidget *box){

}