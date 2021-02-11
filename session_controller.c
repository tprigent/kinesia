//
// Created by Théo Prigent on 08/02/2021.
//

#include <gtk/gtk.h>
#include "session_controller.h"
#include "session_view.h"

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

void launchPatientEditor(){

    /* DECLARE VARIABLES */
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *patient_name;
    GtkWidget *patient_surname;
    GtkWidget *patient_photo;
    GtkWidget *patient_birth;
    GtkWidget *patient_job;
    GtkWidget *patient_ssn;
    GtkWidget *patient_weight;
    GtkWidget *patient_size;
    GtkWidget *important_infos;
    GtkWidget *name_entry;
    GtkWidget *surname_entry;
    GtkWidget *photo_button;
    GtkWidget *birth_entry;
    GtkWidget *job_entry;
    GtkWidget *ssn_entry;
    GtkWidget *weight_entry;
    GtkWidget *size_entry;
    GtkWidget *infos_entry;

    /* CREATE THE DIALOG BOX */
    dialog = gtk_dialog_new_with_buttons ("Édition de la fiche patient",NULL,GTK_DIALOG_MODAL,
                                          "Annuler",GTK_RESPONSE_REJECT,
                                          "Enregistrer", GTK_RESPONSE_ACCEPT,NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    /* DECLARE ELEMENTS OF THE DIALOG BOX */
    patient_name = gtk_label_new("Nom");
    patient_surname = gtk_label_new("Prénom");
    patient_photo = gtk_label_new("Photo");
    patient_birth = gtk_label_new("Date de naissance");
    patient_job = gtk_label_new("Métier");
    patient_ssn = gtk_label_new("N° de sécurité sociale");
    patient_weight = gtk_label_new("Poids");
    patient_size = gtk_label_new("Taille");
    important_infos = gtk_label_new("Informations importantes");

    photo_button = gtk_button_new_from_icon_name("mail-attachment", GTK_ICON_SIZE_LARGE_TOOLBAR);

    name_entry = gtk_entry_new();
    surname_entry = gtk_entry_new();
    birth_entry = gtk_entry_new();
    job_entry = gtk_entry_new();
    ssn_entry = gtk_entry_new();
    weight_entry = gtk_entry_new();
    size_entry = gtk_entry_new();
    infos_entry = gtk_entry_new();

    /* FILL THE DIALOG BOX */
    gtk_container_add(GTK_CONTAINER(content_area), patient_name);
    gtk_container_add(GTK_CONTAINER(content_area), name_entry);
    setBottomMargin(name_entry);
    gtk_container_add(GTK_CONTAINER(content_area), patient_surname);
    gtk_container_add(GTK_CONTAINER(content_area), surname_entry);
    setBottomMargin(surname_entry);
    gtk_container_add(GTK_CONTAINER(content_area), patient_photo);
    gtk_container_add(GTK_CONTAINER(content_area), photo_button);
    setBottomMargin(photo_button);
    gtk_container_add(GTK_CONTAINER(content_area), patient_birth);
    gtk_container_add(GTK_CONTAINER(content_area), birth_entry);
    setBottomMargin(birth_entry);
    gtk_container_add(GTK_CONTAINER(content_area), patient_job);
    gtk_container_add(GTK_CONTAINER(content_area), job_entry);
    setBottomMargin(job_entry);
    gtk_container_add(GTK_CONTAINER(content_area), patient_ssn);
    gtk_container_add(GTK_CONTAINER(content_area), ssn_entry);
    setBottomMargin(ssn_entry);
    gtk_container_add(GTK_CONTAINER(content_area), patient_weight);
    gtk_container_add(GTK_CONTAINER(content_area), weight_entry);
    setBottomMargin(weight_entry);
    gtk_container_add(GTK_CONTAINER(content_area), patient_size);
    gtk_container_add(GTK_CONTAINER(content_area), size_entry);
    setBottomMargin(size_entry);
    gtk_container_add(GTK_CONTAINER(content_area), important_infos);
    gtk_container_add(GTK_CONTAINER(content_area), infos_entry);
    setBottomMargin(infos_entry);


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