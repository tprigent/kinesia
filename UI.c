#include <gtk/gtk.h>
#include "UI.h"
#include "main_view.h"


int main_UI(int argc, char **argv) {
    gtk_init(&argc, &argv);

    /* Create the main window */
    GtkWidget *mainWindow = NULL;
    mainWindow = setMainWindow();
    /* Fill the main view */
    setMainEnvironment(mainWindow);
    /* Display the main view */
    gtk_widget_show_all(mainWindow);
    gtk_main();

    return EXIT_SUCCESS;
}