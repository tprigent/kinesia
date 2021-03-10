//
// Created by julien on 02/03/2021.
//

#include "patient_view.h"
#include "session_view.h"
#include "session_controller.h"
#include "connect_struct_UI.h"
#include "patient.h"
#include <gtk/gtk.h>

/*!
 * \brief Initiate patient window which shows a list of the patient
 *
 * Focus, position, size, title and destroy callback are set.
 * \todo change the name of the window once the software name found
*/
GtkWidget *setPatientWindow(){
    GtkWidget *window = NULL;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_activate_focus(GTK_WINDOW(window));
    gtk_window_set_title(GTK_WINDOW(window), "Kinesia");
    gtk_window_set_default_size(GTK_WINDOW(window), 1200, 720);
    gtk_window_maximize(GTK_WINDOW(window));
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_destroy_with_parent(GTK_WINDOW(window), FALSE);
    setPatientEnvironment(window);
    gtk_widget_show_all(window);
    gtk_main();

    return window;
}

/*!
 * \brief Split the main window in two spaces and fill them
 *
 * The two spaces are:
 * on the left side a calendar and buttons to archive patients,
 * at the right side a list of patients, an search-entry and a button to create a patient.
 *
 *
 * \param[in] window Patient window to fill
*/
void setPatientEnvironment(GtkWidget *window){

    /* DECLARE VARIABLES */
    GtkWidget *grid = NULL;
    GtkWidget *grid_calendar = NULL;
    GtkWidget *grid_patient = NULL;

    GtkWidget *frame_test = NULL;

    GtkWidget *box_patient = NULL;

    GtkWidget *calendar = NULL;
    GtkWidget *button_new_patient = NULL;
    GtkWidget *entry_research = NULL;
    GtkWidget *button_research = NULL;
    GtkWidget *patient1 = NULL;
    GtkWidget *patient2 = NULL;
    GtkWidget *patient3 = NULL;
    GtkWidget *patient4 = NULL;


    /* ASSIGN VARIABLES */
    grid = gtk_grid_new();
    grid_patient = gtk_grid_new();
    grid_calendar = gtk_grid_new();

    frame_test = gtk_frame_new("CALENDRIER");

    box_patient = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(box_patient), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

    calendar = gtk_calendar_new();
    button_new_patient = gtk_button_new_from_icon_name("list-add", GTK_ICON_SIZE_MENU);
    entry_research = gtk_entry_new();
    button_research = gtk_button_new_from_icon_name("system-search", GTK_ICON_SIZE_MENU);
    patient1 = gtk_button_new_with_label("Claude François");
    patient2 = gtk_button_new_with_label("Deuxième patient");
    patient3 = gtk_button_new_with_label("Troisième patient");
    patient4 = gtk_button_new_with_label("Quatrième patient");


    /* GRID WHICH ORGANIZES THE WINDOW */
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_hexpand(grid, TRUE);
    gtk_widget_set_vexpand(grid, TRUE);

    /* FILL THE GRID */
    /* Left part */
    gtk_grid_attach(GTK_GRID(grid), frame_test, GTK_ALIGN_START, GTK_ALIGN_START, 1, 14);
    gtk_widget_set_hexpand(frame_test, TRUE);
    gtk_widget_set_vexpand(frame_test, TRUE);

    gtk_container_add(GTK_CONTAINER(frame_test), grid_calendar);
    gtk_grid_set_row_spacing(GTK_GRID(grid_calendar), 5);

    gtk_grid_attach(GTK_GRID(grid_calendar), calendar, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(calendar, TRUE);


    /* Search a patient */
    gtk_grid_attach_next_to(GTK_GRID(grid), entry_research, frame_test, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_valign(entry_research, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid), button_research, entry_research, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_halign(button_research, GTK_ALIGN_START);
    gtk_widget_set_valign(button_research, GTK_ALIGN_START);

    /* Add a new patient */
    g_signal_connect(GTK_BUTTON(button_new_patient), "clicked", G_CALLBACK(launchNewPatientEditor), window);
    gtk_grid_attach_next_to(GTK_GRID(grid), button_new_patient, button_research, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_halign(button_new_patient, GTK_ALIGN_END);
    gtk_widget_set_valign(button_new_patient, GTK_ALIGN_START);

    /* Box patient */
    gtk_grid_attach_next_to(GTK_GRID(grid), box_patient, entry_research, GTK_POS_BOTTOM, 3, 13);
    gtk_grid_set_row_spacing(GTK_GRID(grid_patient), 5);
    gtk_container_add(GTK_CONTAINER(box_patient), grid_patient);


    /* ADD PATIENTS */
    gtk_grid_attach(GTK_GRID(grid_patient), patient1, GTK_ALIGN_START, GTK_ALIGN_START, 5, 1);
    gtk_widget_set_hexpand(patient1, TRUE);
    gtk_widget_set_vexpand(patient1, FALSE);
    g_signal_connect(GTK_BUTTON(patient1), "clicked", G_CALLBACK(launchSessionView), window);

    gtk_grid_attach_next_to(GTK_GRID(grid_patient), patient2, patient1, GTK_POS_BOTTOM, 5, 1);
    gtk_widget_set_hexpand(patient1, TRUE);
    gtk_widget_set_vexpand(patient1, FALSE);

    gtk_grid_attach_next_to(GTK_GRID(grid_patient), patient3, patient2, GTK_POS_BOTTOM, 5, 1);
    gtk_widget_set_hexpand(patient1, TRUE);
    gtk_widget_set_vexpand(patient1, FALSE);

    gtk_grid_attach_next_to(GTK_GRID(grid_patient), patient4, patient3, GTK_POS_BOTTOM, 5, 1);
    gtk_widget_set_hexpand(patient1, TRUE);
    gtk_widget_set_vexpand(patient1, FALSE);

    /* JUST TO TEST THE SCROLLBAR */
    /*GtkWidget *patient_photo = NULL;
    GdkPixbuf *patient_photo_pixbuf = NULL;

    patient_photo_pixbuf = gdk_pixbuf_new_from_file("../src/media/claude.jpeg", NULL);
    patient_photo_pixbuf = gdk_pixbuf_scale_simple(patient_photo_pixbuf, 270, 350, GDK_INTERP_BILINEAR);
    patient_photo = gtk_image_new_from_pixbuf(GDK_PIXBUF(patient_photo_pixbuf));

    gtk_grid_attach_next_to(GTK_GRID(grid_patient), patient_photo, patient4, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(patient_photo, FALSE);
    gtk_widget_set_vexpand(patient_photo, FALSE);
    gtk_widget_set_halign(patient_photo, GTK_ALIGN_CENTER);*/

}