//
// Created by Théo Prigent on 08/02/2021.
//

#include <gtk/gtk.h>
#include "controller.h"

void launchFolderEditor(gpointer *parent){
    GtkWidget *dialog, *label, *content_area;
    dialog = gtk_dialog_new_with_buttons ("Édition du dossier",GTK_WINDOW(parent),GTK_DIALOG_MODAL,
                                          "Annuler",GTK_RESPONSE_REJECT,
                                          "Enregistrer", GTK_RESPONSE_ACCEPT,NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG (dialog));
    label = gtk_label_new ("** TO BE EDITED **");
    gtk_container_add (GTK_CONTAINER (content_area), label);
    gtk_widget_show_all (dialog);
    int result = gtk_dialog_run (GTK_DIALOG (dialog));
    switch (result)
    {
        case GTK_RESPONSE_ACCEPT:
            // enregistrer les nouvelles informations;
            break;
        default:
            break;
    }
    gtk_widget_destroy (dialog);

}