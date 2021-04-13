/*!
* \file file_view.c
* \brief View to display medical attachments and tools
*/

#include "file_view.h"

GtkWidget *setFileWindow(GtkWidget *parentDialog, char *filename, Patient *patient){
    GtkWidget *window = NULL;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_activate_focus(GTK_WINDOW(window));
    gtk_window_set_title(GTK_WINDOW(window), filename);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_destroy(GTK_WIDGET(parentDialog));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_destroy_with_parent(GTK_WINDOW(window), TRUE);
    setFileViewerEnvironment(window, filename, patient);
    gtk_widget_show_all(window);
    gtk_main();

    return window;
}


void setFileViewerEnvironment(GtkWidget *window, char *filename, Patient *patient){
    GtkWidget *grid = NULL;
    GtkWidget *file = NULL;
    GdkPixbuf *file_pixbuf = NULL;
    char *mediaPath = getMediaPath(patient);
    char *filePath = (char*) malloc(sizeof(char)*(strlen(filename)+strlen(mediaPath)));

    /* Rebuild file path */
    strcpy(filePath, mediaPath);
    strcat(filePath, filename);

    grid = gtk_grid_new();
    file_pixbuf = gdk_pixbuf_new_from_file(filePath, NULL);
    while(gdk_pixbuf_get_height(file_pixbuf) > 700 || gdk_pixbuf_get_width(file_pixbuf) > 2600){
        file_pixbuf = gdk_pixbuf_new_from_file_at_scale(filePath,
                                                        gdk_pixbuf_get_height(file_pixbuf)/2,
                                                        gdk_pixbuf_get_width(file_pixbuf)/2,
                                                        TRUE, NULL);
    }
    file = gtk_image_new_from_pixbuf(GDK_PIXBUF(file_pixbuf));


    /* GRID WHICH ORGANIZES THE WINDOW */
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_hexpand(grid, TRUE);
    gtk_widget_set_vexpand(grid, TRUE);

    gtk_grid_attach(GTK_GRID(grid), file, GTK_ALIGN_START, GTK_ALIGN_START, 1, 14);
    gtk_widget_set_hexpand(file, TRUE);
    gtk_widget_set_vexpand(file, TRUE);
}
