//
// Created by Théo Prigent on 08/02/2021.
//

#include <gtk/gtk.h>
#include "session_controller.h"
#include "session_view.h"
#include "connect_struct_UI.h"

void launchFolderEditor(){

    /* DECLARE VARIABLES */
    GtkWidget *dialog;
    GtkWidget *folder_name_label;
    GtkWidget *start_treatment_label;
    GtkWidget *pathology_label;
    GtkWidget *other_infos_label;
    GtkWidget *folder_name_entry;
    GtkWidget *start_treatment_entry;
    GtkWidget *pathology_entry;
    GtkWidget *other_infos_entry;
    GtkWidget *content_area;

    /* CREATE THE DIALOG BOX */
    dialog = gtk_dialog_new_with_buttons ("Édition du dossier",NULL,GTK_DIALOG_MODAL,
                                          "Annuler",GTK_RESPONSE_REJECT,
                                          "Enregistrer", GTK_RESPONSE_ACCEPT,NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    /* DECLARE ELEMENTS OF THE DIALOG BOX */
    folder_name_label = gtk_label_new ("Nom du dossier");
    start_treatment_label = gtk_label_new("Date de début du traitement");
    pathology_label = gtk_label_new("Pathologie");
    other_infos_label = gtk_label_new("Autres informations");

    folder_name_entry = gtk_entry_new();
    start_treatment_entry = gtk_entry_new();
    pathology_entry = gtk_entry_new();
    other_infos_entry = gtk_entry_new();

    /* FILL THE DIALOG BOX */
    gtk_container_add(GTK_CONTAINER(content_area), folder_name_label);
    gtk_container_add(GTK_CONTAINER(content_area), folder_name_entry);
    gtk_widget_set_margin_bottom(folder_name_entry, 5);
    gtk_container_add(GTK_CONTAINER(content_area), start_treatment_label);
    gtk_container_add(GTK_CONTAINER(content_area), start_treatment_entry);
    gtk_widget_set_margin_bottom(start_treatment_entry, 5);
    gtk_container_add(GTK_CONTAINER(content_area), pathology_label);
    gtk_container_add(GTK_CONTAINER(content_area), pathology_entry);
    gtk_widget_set_margin_bottom(pathology_entry, 5);
    gtk_container_add(GTK_CONTAINER(content_area), other_infos_label);
    gtk_container_add(GTK_CONTAINER(content_area), other_infos_entry);
    gtk_widget_set_margin_bottom(other_infos_entry, 10);

    /* SETUP THE VIEW PARAMETERS */
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 5);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(dialog);

    /* MANAGE THE USER ACTION */
    int result = gtk_dialog_run (GTK_DIALOG (dialog));
    switch (result)
    {
        case GTK_RESPONSE_ACCEPT:
            // TODO: enregistrer les nouvelles informations;
            break;
        default:
            break;
    }

    /* DESTROY DIALOG BOX */
    gtk_widget_destroy(dialog);

}

void launchPatientEditor(GtkWidget *but_edit, gpointer data){
    Patient *patient = data;

    /* DECLARE VARIABLES */
    GtkWidget *dialog = NULL;
    GtkWidget *content_area = NULL;
    GtkWidget *patient_name = NULL;
    GtkWidget *patient_surname = NULL;
    GtkWidget *patient_photo = NULL;
    GtkWidget *patient_birth = NULL;
    GtkWidget *patient_job = NULL;
    GtkWidget *patient_ssn = NULL;
    GtkWidget *patient_weight = NULL;
    GtkWidget *patient_height = NULL;
    GtkWidget *patient_info = NULL;
    GtkWidget *name_entry = NULL;
    GtkWidget *surname_entry = NULL;
    GtkWidget *photo_button = NULL;
    GtkWidget *birth_entry = NULL;
    GtkWidget *job_entry = NULL;
    GtkWidget *ssn_entry = NULL;
    GtkWidget *weight_entry = NULL;
    GtkWidget *height_entry = NULL;
    GtkWidget *info_entry = NULL;


    /* DECLARE ELEMENTS OF THE DIALOG BOX */
    patient_name = gtk_label_new("Prenom : ");
    patient_surname = gtk_label_new("Nom : ");
    patient_photo = gtk_label_new("Photo : ");
    patient_birth = gtk_label_new("Date de naissance : ");
    patient_job = gtk_label_new("Métier : ");
    patient_ssn = gtk_label_new("N° de sécurité sociale : ");
    patient_weight = gtk_label_new("Poids : ");
    patient_height = gtk_label_new("Taille : ");
    patient_info = gtk_label_new("Informations importantes : ");
    photo_button = gtk_button_new_from_icon_name("mail-attachment", GTK_ICON_SIZE_LARGE_TOOLBAR);

    name_entry = gtk_entry_new();
    surname_entry = gtk_entry_new();
    birth_entry = gtk_entry_new();
    job_entry = gtk_entry_new();
    ssn_entry = gtk_entry_new();
    weight_entry = gtk_entry_new();
    height_entry = gtk_entry_new();
    info_entry = gtk_entry_new();


    /* CREATE THE DIALOG BOX */
    dialog = gtk_dialog_new_with_buttons ("Édition de la fiche patient",NULL,GTK_DIALOG_MODAL,
                                          "Annuler",GTK_RESPONSE_REJECT,
                                          "Enregistrer", GTK_RESPONSE_ACCEPT,NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));


    /* CREATE A GRID IN THE DIALOG BOX */
    GtkWidget *grid_dialog = NULL;
    grid_dialog = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(content_area), grid_dialog);
    gtk_container_set_border_width(GTK_CONTAINER(grid_dialog), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid_dialog), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid_dialog), 5);


    /* FRAME WHICH CONTAINS INDENTITY INFORMATION */
    GtkWidget *frame_etat_civil = NULL;
    frame_etat_civil = gtk_frame_new("Etat civil");
    gtk_frame_set_label_align(GTK_FRAME(frame_etat_civil), 0, 0.5);
    gtk_grid_attach(GTK_GRID(grid_dialog), frame_etat_civil, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(frame_etat_civil, TRUE);
    gtk_widget_set_vexpand(frame_etat_civil, FALSE);

    GtkWidget *grid_etat_civil = NULL;
    grid_etat_civil = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(frame_etat_civil), grid_etat_civil);
    gtk_container_set_border_width(GTK_CONTAINER(grid_etat_civil), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid_etat_civil), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid_etat_civil), 5);


    /* FILL THE IDENTITY INFORMATION */
    // Name
    gtk_grid_attach(GTK_GRID(grid_etat_civil), patient_name, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(patient_name, TRUE);
    gtk_widget_set_vexpand(patient_name, FALSE);
    gtk_widget_set_halign(patient_name, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), name_entry, patient_name, GTK_POS_BOTTOM, 1, 1);

    // Surname
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), patient_surname, patient_name, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_hexpand(patient_surname, TRUE);
    gtk_widget_set_vexpand(patient_surname, FALSE);
    gtk_widget_set_halign(patient_surname, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), surname_entry, patient_surname, GTK_POS_BOTTOM, 1, 1);

    // Birthdate
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), patient_birth, name_entry, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(patient_birth, TRUE);
    gtk_widget_set_vexpand(patient_birth, FALSE);
    gtk_widget_set_halign(patient_birth, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), birth_entry, patient_birth, GTK_POS_BOTTOM, 1, 1);

    // Picture
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), patient_photo, surname_entry, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(patient_photo, TRUE);
    gtk_widget_set_vexpand(patient_photo, FALSE);
    gtk_widget_set_halign(patient_photo, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), photo_button, patient_photo, GTK_POS_BOTTOM, 1, 1);

    // Job
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), patient_job, birth_entry, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(patient_job, TRUE);
    gtk_widget_set_vexpand(patient_job, FALSE);
    gtk_widget_set_halign(patient_job, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), job_entry, patient_job, GTK_POS_BOTTOM, 1, 1);


    /* FRAME WHICH CONTAINS MEDICAL INFORMATION */
    GtkWidget *frame_medical_info = NULL;
    frame_medical_info = gtk_frame_new("Informations médicales");
    gtk_frame_set_label_align(GTK_FRAME(frame_medical_info), 0, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), frame_medical_info, frame_etat_civil, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_hexpand(frame_medical_info, TRUE);
    gtk_widget_set_vexpand(frame_medical_info, FALSE);

    GtkWidget *grid_medical_info = NULL;
    grid_medical_info = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(frame_medical_info), grid_medical_info);
    gtk_container_set_border_width(GTK_CONTAINER(grid_medical_info), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid_medical_info), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid_medical_info), 5);

    /* FILL THE MEDICAL INFORMATION */
    // Height
    gtk_grid_attach(GTK_GRID(grid_medical_info), patient_height, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(patient_height, TRUE);
    gtk_widget_set_vexpand(patient_height, FALSE);
    gtk_widget_set_halign(patient_height, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), height_entry, patient_height, GTK_POS_BOTTOM, 1, 1);

    // Weight
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), patient_weight, patient_height, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_hexpand(patient_weight, TRUE);
    gtk_widget_set_vexpand(patient_weight, FALSE);
    gtk_widget_set_halign(patient_weight, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), weight_entry, patient_weight, GTK_POS_BOTTOM, 1, 1);

    // SSn
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), patient_ssn, height_entry, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(patient_ssn, TRUE);
    gtk_widget_set_vexpand(patient_ssn, FALSE);
    gtk_widget_set_halign(patient_ssn, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), ssn_entry, patient_ssn, GTK_POS_BOTTOM, 1, 1);

    // Important informations
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), patient_info, weight_entry, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(patient_info, TRUE);
    gtk_widget_set_vexpand(patient_info, FALSE);
    gtk_widget_set_halign(patient_info, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), info_entry, patient_info, GTK_POS_BOTTOM, 1, 1);


    /* SETUP THE VIEW PARAMETERS */
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 5);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(dialog);

    /* MANAGE THE USER ACTION */
    int result = gtk_dialog_run (GTK_DIALOG (dialog));
    switch (result)
    {
        case GTK_RESPONSE_ACCEPT:
            // TODO: enregistrer les nouvelles informations;
            break;
        default:
            break;
    }

    /* DESTROY DIALOG BOX */
    gtk_widget_destroy(dialog);

}