/*!
* \file main_UI.c
* \brief File with function to launch the User Interface
*/

#include <gtk/gtk.h>
#include "home_view.h"

/*!
 * \brief Function that launch style.css to modify application style
 *
 * This function set necessary parameters to load css and use css file
 *
*/
static void load_css(){
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    const gchar *css_style_file = "../src/view/style.css";
    GFile *css_fp = g_file_new_for_path(css_style_file);
    GError *error = 0;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_file(provider, css_fp, &error);

    g_object_unref(provider);
}

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

    gtk_init(NULL, NULL);
    load_css();

    /* Launch the home window */
    setHomeWindow();

    return EXIT_SUCCESS;
}