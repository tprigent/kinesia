/*!
* \file UI.c
* \brief File with function to launch the User Interface
*/

#include <gtk/gtk.h>
#include "work_view.h"
#include "home_view.h"

/*!
 * \brief Function that launch the User Interface
 *
 * Set all elements and enter the gtk loop
 *
 * \param[in] argc integer from the main
 * \param[in] pointer on the argv integer pointer from the main
*/
int main(int argc, char **argv) {
    gtk_init(&argc, &argv);

    /* Create the session window */
    //GtkWidget *sessionWindow = NULL;
    //sessionWindow = setWorkWindow();
    setHomeWindow();

    //gtk_main();

    return EXIT_SUCCESS;
}