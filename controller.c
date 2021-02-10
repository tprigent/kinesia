//
// Created by Théo Prigent on 08/02/2021.
//

#include <gtk/gtk.h>
#include "controller.h"

void launchFolderEditor(gpointer *parent){

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
    dialog = gtk_dialog_new_with_buttons ("Édition du dossier",GTK_WINDOW(parent),GTK_DIALOG_MODAL,
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
    gtk_widget_destroy (dialog);

}