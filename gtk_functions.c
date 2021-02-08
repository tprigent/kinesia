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
    /* Create a grid to organize the information section **************************** */
    GtkWidget *grid_part1 = NULL;
    grid_part1 = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid_part1), 5);
    gtk_box_pack_start(GTK_BOX(box), grid_part1, TRUE, TRUE, 0);
    /* ****************************************************************************** */

    /* first part : button "revenir liste patient" ********************************** */
    GtkWidget *but_back = NULL;
    but_back = gtk_button_new_with_label("< Revenir à la liste");
    gtk_grid_attach(GTK_GRID(grid_part1), but_back, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(but_back, FALSE);
    gtk_widget_set_vexpand(but_back, FALSE);
    gtk_widget_set_halign(but_back, GTK_ALIGN_START);
    /* ****************************************************************************** */


    /* Second part : section which contains patient informations ******************** */
    /* Creation of the frame */
    GtkWidget *cadre_info = NULL;
    cadre_info = gtk_frame_new("Informations patient");
    gtk_frame_set_label_align(GTK_FRAME(cadre_info), 0.5, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_part1), cadre_info, but_back, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(cadre_info, TRUE);
    gtk_widget_set_vexpand(cadre_info, TRUE);

    /* Creation of a grid to fill the frame ****************/
    GtkWidget *grid_info = NULL;
    grid_info = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(cadre_info), grid_info);
    gtk_container_set_border_width(GTK_CONTAINER(grid_info), 5);
    /* ************************************************** */

    /* Creation of a button to change information *********/
    GtkWidget *but_edit = NULL;
    but_edit = gtk_button_new_from_icon_name("text-editor", GTK_ICON_SIZE_LARGE_TOOLBAR);
    gtk_grid_attach(GTK_GRID(grid_info), but_edit, GTK_ALIGN_END, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(but_edit, TRUE);
    gtk_widget_set_vexpand(but_edit, FALSE);
    gtk_widget_set_halign(but_edit, GTK_ALIGN_END);
    /* ************************************************** */

    /* Include the picture of the patient *****************/
    GtkWidget *photo = NULL;
    GdkPixbuf *photo2 = NULL;
    photo2 = gdk_pixbuf_new_from_file("./photo_patients/claude.jpeg", NULL);
    photo2 = gdk_pixbuf_scale_simple(photo2, 170, 250, GDK_INTERP_BILINEAR);
    photo = gtk_image_new_from_pixbuf(GDK_PIXBUF(photo2));
    gtk_grid_attach_next_to(GTK_GRID(grid_info), photo, but_edit, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(photo, FALSE);
    gtk_widget_set_vexpand(photo, FALSE);
    gtk_widget_set_halign(photo, GTK_ALIGN_CENTER);
    /* ************************************************** */

    /* Frame which contains identity informations *********/
    GtkWidget *frame_etat_civil = NULL;
    frame_etat_civil = gtk_frame_new("Etat civil");
    gtk_frame_set_label_align(GTK_FRAME(frame_etat_civil), 0, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_info), frame_etat_civil, photo, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(frame_etat_civil, TRUE);
    gtk_widget_set_vexpand(frame_etat_civil, FALSE);

    GtkWidget *grid_etat_civil = NULL;
    grid_etat_civil = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(frame_etat_civil), grid_etat_civil);
    /* ************************************************** */

    /* Section which fills the identity informations ******/
    // Name
    GtkWidget *nom = NULL;
    nom = gtk_label_new("Claude François");
    gtk_grid_attach(GTK_GRID(grid_etat_civil), nom, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(nom, TRUE);
    gtk_widget_set_vexpand(nom, FALSE);
    gtk_widget_set_halign(nom, GTK_ALIGN_CENTER);

    // Birthdate
    GtkWidget *dateN = NULL;
    dateN = gtk_label_new("1 février 1939");
    gtk_label_set_use_markup(GTK_LABEL(dateN), TRUE);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), dateN, nom, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(dateN, TRUE);
    gtk_widget_set_vexpand(dateN, FALSE);
    gtk_widget_set_halign(dateN, GTK_ALIGN_CENTER);

    // Profession
    GtkWidget *profession = NULL;
    profession = gtk_label_new("Chanteur");
    gtk_label_set_use_markup(GTK_LABEL(profession), TRUE);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), profession, dateN, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(profession, TRUE);
    gtk_widget_set_vexpand(profession, FALSE);
    gtk_widget_set_halign(profession, GTK_ALIGN_CENTER);
    /* ************************************************** */

    /* Frame which contains medical informations *********/
    GtkWidget *frame_medical_info = NULL;
    frame_medical_info = gtk_frame_new("Informations médicales");
    gtk_frame_set_label_align(GTK_FRAME(frame_medical_info), 0, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_info), frame_medical_info, frame_etat_civil, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(frame_medical_info, TRUE);
    gtk_widget_set_vexpand(frame_medical_info, FALSE);

    GtkWidget *grid_medical_info = NULL;
    grid_medical_info = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(frame_medical_info), grid_medical_info);
    /* ************************************************** */

    /* Section which fills the identity informations ******/
    // Weight and height
    GtkWidget *poids_taille = NULL;
    poids_taille = gtk_label_new("59 kg    ;   1.70m");
    gtk_grid_attach(GTK_GRID(grid_medical_info), poids_taille, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(poids_taille, TRUE);
    gtk_widget_set_vexpand(poids_taille, FALSE);
    gtk_widget_set_halign(poids_taille, GTK_ALIGN_CENTER);

    // num de secu
    GtkWidget *num_secu = NULL;
    num_secu = gtk_label_new("N° de sécurité sociale");
    gtk_label_set_use_markup(GTK_LABEL(num_secu), TRUE);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), num_secu, poids_taille, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(num_secu, TRUE);
    gtk_widget_set_vexpand(num_secu, FALSE);
    gtk_widget_set_halign(num_secu, GTK_ALIGN_CENTER);
    /* ************************************************** */

    /* Frame which contains important informations ********/
    GtkWidget *frame_important_info = NULL;
    frame_important_info = gtk_frame_new("Informations importantes");
    gtk_frame_set_label_align(GTK_FRAME(frame_important_info), 0, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_info), frame_important_info, frame_medical_info, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(frame_important_info, TRUE);
    gtk_widget_set_vexpand(frame_important_info, FALSE);

    GtkWidget *label_imp_info = NULL;
    label_imp_info = gtk_label_new("Informations médicales particulières \nPar exemple maladie cardiaue/diabète...");
    gtk_container_add(GTK_CONTAINER(frame_important_info), label_imp_info);
    /* ************************************************** */

    /* ****************************************************************************** */


    /* Third part : section which contains the folders ***************************** */
    GtkWidget *vbox_folder = NULL;
    vbox_folder = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_part1), vbox_folder, cadre_info, GTK_POS_BOTTOM, 3, 1);
    gtk_widget_set_hexpand(vbox_folder, TRUE);
    gtk_widget_set_vexpand(vbox_folder, FALSE);

    int nb_folders = 3; // sere récupéré par une fonction
    int i = 0;
    GtkWidget *button_folder[nb_folders];
    char *name_folder[nb_folders];
    char name_folder1[] = "#Dossier1"; // sera récupéré parne fonction
    char name_folder2[] = "#Dossier2";
    char name_folder3[] = "#Dossier3";
    name_folder[0] = name_folder1;
    name_folder[1] = name_folder2;
    name_folder[2] = name_folder3;

    for(i =0; i < nb_folders; i++){
        button_folder[i] = gtk_button_new_with_label(name_folder[i]);
        gtk_box_pack_start(GTK_BOX(vbox_folder), button_folder[i], FALSE, FALSE, 0);
    }
    /* ****************************************************************************** */
}

void createFolderInfoWindow(GtkWidget *box){

}

void createSessionInfoWindow(GtkWidget *box){

}