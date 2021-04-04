/*!
* \file UI_to_struct.h
* \brief File with functions used to parse data from UI entries to structures
*/

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../model/structures.h"
#include "../view/home_view.h"


#ifndef LOGICIEL_KINE_CONNECT_UI_STRUCT_H
#define LOGICIEL_KINE_CONNECT_UI_STRUCT_H

/**
 * \brief Structure to pass all of the entries needed to modify or add a session
*/
typedef struct{
    Session *session;               /**< Session to be edited */
    GtkWidget *sessionName;         /**< Entry for the name of the session */
    GtkWidget *sessionDate;         /**< Session date entry */
    GtkWidget *nextSessionDate;     /**< Next session date entry */
    GtkWidget *observations;        /**< Observations entry */
    int origin;                     /**< Boolean: 0 for new session, 1 to edit session */     /**< Parameters to refresh the view */
}SessionEntries;


void saveSessionEntries(GtkWidget *save_button, SessionEntries *new_session);

void saveFolderEntries(Folder *folder, GtkWidget *folder_name_entry,GtkWidget *pathology_entry,
                       GtkWidget *other_infos_buffer, GtkWidget *start_treatment_entry, int origin);

void savePatientEntries(Patient *patient, int origin, GtkWidget *surname_entry, GtkWidget *name_entry,
                        GtkWidget *birth_entry, GtkWidget *weight_entry, GtkWidget *height_entry,
                        GtkWidget *first_consult_entry, GtkWidget *ssn_entry, GtkWidget *number_entry,
                        GtkWidget *email_entry, GtkWidget *gender_combo_box, GtkWidget *address_entry,
                        GtkWidget *city_entry, GtkWidget *postcode_entry, GtkWidget *job_entry,
                        GtkWidget *info_text, GtkTextIter end);

#endif //LOGICIEL_KINE_CONNECT_UI_STRUCT_H
