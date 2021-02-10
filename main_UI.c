#include <gtk/gtk.h>
#include "main_UI.h"
#include "gtk_functions.h"


int main_UI(int argc, char **argv) {
    gtk_init(&argc, &argv);

    GtkWidget *window = NULL;
    GtkWidget *grid = NULL;

    /* create a new window, and set its attributes */

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    setMainWindow(window);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_activate_focus(GTK_WINDOW(window));

    /* Create a new table a place it in the window*/
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Add 3 boxes to separate space */
    GtkWidget *boxPart[3];

    boxPart[0] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_grid_attach(GTK_GRID(grid), boxPart[0], GTK_ALIGN_START, GTK_ALIGN_START, 1, 6);
    gtk_widget_set_hexpand(boxPart[0], TRUE);
    gtk_widget_set_vexpand(boxPart[0], TRUE);

    boxPart[1] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    setStartMargin(boxPart[1]);
    gtk_grid_attach_next_to(GTK_GRID(grid), boxPart[1],boxPart[0], GTK_POS_RIGHT, 4, 5);
    gtk_widget_set_hexpand(boxPart[1], TRUE);
    gtk_widget_set_vexpand(boxPart[1], TRUE);

    boxPart[2] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    setStartMargin(boxPart[2]);
    setTopMargin(boxPart[2]);
    gtk_grid_attach_next_to(GTK_GRID(grid), boxPart[2],boxPart[1], GTK_POS_BOTTOM, 4, 1);
    gtk_widget_set_hexpand(boxPart[2], TRUE);
    gtk_widget_set_vexpand(boxPart[2], TRUE);


    /* Call the functions which create the different parts of the window */
    createPatientInfoWindow(boxPart[0]);
    createFolderInfoWindow(boxPart[1]);
    createSessionInfoWindow(boxPart[2]);

    /* Display the window and begin the loop */
    gtk_widget_show_all(window);
    gtk_main();

    return EXIT_SUCCESS;
}