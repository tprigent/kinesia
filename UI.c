/*!
* \file UI.c
* \brief File with function to launch the User Interface
*/

#include <gtk/gtk.h>
#include "UI.h"
#include "session_view.h"


int main_UI(int argc, char **argv) {
    gtk_init(&argc, &argv);

    /* Create the session window */
    GtkWidget *sessionWindow = NULL;
    sessionWindow = setSessionWindow();
    /* Fill the main view */
    setSessionEnvironment(sessionWindow);
    /* Display the session view */
    gtk_widget_show_all(sessionWindow);
    gtk_main();

    return EXIT_SUCCESS;
}