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
    /* Create a grid to organize the session section ******************************** */
    GtkWidget *grid_part3 = NULL;
    grid_part3 = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid_part3), 10);
    gtk_box_pack_start(GTK_BOX(box), grid_part3, TRUE, TRUE, 0);
    /* ****************************************************************************** */

    /* First part : section to add a new session *********************************** */
    /* Creation of the frame to add a session */
    GtkWidget *add_session = NULL;
    add_session = gtk_frame_new("Séance en cours");
    gtk_frame_set_label_align(GTK_FRAME(add_session), 0.5, 0.5);
    gtk_grid_attach(GTK_GRID(grid_part3), add_session, GTK_ALIGN_START, GTK_ALIGN_CENTER, 1, 1);
    gtk_widget_set_hexpand(add_session, TRUE);
    gtk_widget_set_vexpand(add_session, TRUE);
    gtk_widget_set_halign(add_session, GTK_ALIGN_FILL);

    /* Creation of a grid to fill the add_session frame */
    GtkWidget *add_session_grid = NULL;
    add_session_grid = gtk_grid_new();
    gtk_container_set_border_width(GTK_CONTAINER(add_session_grid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(add_session_grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(add_session_grid), 5);
    gtk_container_add(GTK_CONTAINER(add_session), add_session_grid);

    /* Creation of an entry for the title */
    GtkWidget *title_label = NULL;
    title_label = gtk_label_new("Titre :");
    gtk_grid_attach(GTK_GRID(add_session_grid), title_label, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(title_label, FALSE);
    gtk_widget_set_vexpand(title_label, FALSE);
    gtk_widget_set_halign(title_label, GTK_ALIGN_START);

    GtkWidget *title_entry = NULL;
    title_entry = gtk_entry_new();
    gtk_grid_attach_next_to(GTK_GRID(add_session_grid), title_entry, title_label, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(title_entry, FALSE);
    gtk_widget_set_vexpand(title_entry, FALSE);
    gtk_widget_set_halign(title_entry, GTK_ALIGN_START);

    /* Creation of label to display the next appointment */
    GtkWidget *next_session_label = NULL;
    next_session_label = gtk_label_new("Prochain rendez-vous : 13/02/2020");
    gtk_grid_attach_next_to(GTK_GRID(add_session_grid), next_session_label, title_entry, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_hexpand(next_session_label, FALSE);
    gtk_widget_set_vexpand(next_session_label, FALSE);
    gtk_widget_set_halign(next_session_label, GTK_ALIGN_END);

    /* Creation of a button to attach items */
    GtkWidget *attach_button = NULL;
    attach_button = gtk_button_new_from_icon_name("mail-attachment", GTK_ICON_SIZE_MENU);
    gtk_grid_attach_next_to(GTK_GRID(add_session_grid), attach_button, title_entry, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(attach_button, FALSE);
    gtk_widget_set_vexpand(attach_button, FALSE);
    gtk_widget_set_halign(title_entry, GTK_ALIGN_START);

    /* Creation of a frame to add informations about the session */
    GtkWidget *session_note_frame = NULL;
    session_note_frame = gtk_frame_new("Observations");
    gtk_frame_set_label_align(GTK_FRAME(session_note_frame), 0, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(add_session_grid), session_note_frame, attach_button, GTK_POS_RIGHT, 1, 4);
    gtk_widget_set_hexpand(session_note_frame, TRUE);
    gtk_widget_set_vexpand(session_note_frame, TRUE);

    GtkWidget *session_note_entry = NULL;
    session_note_entry = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(session_note_frame), session_note_entry);
    gtk_widget_set_hexpand(session_note_entry, TRUE);
    gtk_widget_set_vexpand(session_note_entry, TRUE);
    /* ****************************************************************************** */


    /* Second part : section to search old sessions ********************************* */
    // 2ème séance
    GtkWidget *session2 = NULL; //Pour l'instant modélisé par bouton avant d'apprend a faire des menus déroulant
    session2 = gtk_button_new_with_label("Séance du 27/01/2021");
    gtk_grid_attach_next_to(GTK_GRID(grid_part3), session2, add_session, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(session2, TRUE);
    gtk_widget_set_vexpand(session2, FALSE);
    gtk_widget_set_halign(session2, GTK_ALIGN_FILL);

    // 1ère séance
    GtkWidget *session1 = NULL; //Pour l'instant modélisé par bouton avant d'apprend a faire des menus déroulant
    session1 = gtk_button_new_with_label("Séance du 12/01/2021");
    gtk_grid_attach_next_to(GTK_GRID(grid_part3), session1, session2, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(session1, TRUE);
    gtk_widget_set_vexpand(session1, FALSE);
    gtk_widget_set_halign(session1, GTK_ALIGN_FILL);

    /* ****************************************************************************** */

}