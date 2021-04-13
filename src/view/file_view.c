/*!
* \file file_view.c
* \brief View to display medical attachments and tools
*/

#include "file_view.h"

GtkWidget *setFileWindow(char *filename){
    GtkWidget *window = NULL;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_activate_focus(GTK_WINDOW(window));
    gtk_window_set_title(GTK_WINDOW(window), filename);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_destroy_with_parent(GTK_WINDOW(window), TRUE);
    setFileViewerEnvironment(window);
    gtk_widget_show_all(window);
    gtk_main();

    return window;
}


void setFileViewerEnvironment(GtkWidget *window){
    GtkWidget *grid = NULL;
    grid = gtk_grid_new();

    GtkWidget *button = gtk_button_new_with_label("test");

    /* GRID WHICH ORGANIZES THE WINDOW */
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_hexpand(grid, TRUE);
    gtk_widget_set_vexpand(grid, TRUE);

    gtk_grid_attach(GTK_GRID(grid), button, GTK_ALIGN_START, GTK_ALIGN_START, 1, 14);
    gtk_widget_set_hexpand(button, TRUE);
    gtk_widget_set_vexpand(button, TRUE);
}
