/*!
* \file UI_to_struct.c
* \brief File with functions used to parse data from UI entries to structures
*/

#include "UI_to_struct.h"
#include "struct_to_BDD_session.h"
#include "../view/work_view.h"
#include "display_helpers.h"
#include "struct_to_BDD_patient.h"



void saveNewSession(GtkWidget *save_button, NewSessionEntries *new_session){
    /* SESSION NAME */
    strcpy(new_session->session->sessionName, (char*)gtk_entry_get_text(GTK_ENTRY(new_session->sessionName)));

    /* SESSION DATES */
    new_session->session->sessionDate.day = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(new_session->sessionDate)))->day;
    new_session->session->sessionDate.month = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(new_session->sessionDate)))->month;
    new_session->session->sessionDate.year = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(new_session->sessionDate)))->year;

    new_session->session->nextSessionDate.day = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(new_session->nextSessionDate)))->day;
    new_session->session->nextSessionDate.month = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(new_session->nextSessionDate)))->month;
    new_session->session->nextSessionDate.year = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(new_session->nextSessionDate)))->year;

    /* SESSION OBSERVATIONS */
    GtkTextIter start, end;
    GtkTextBuffer *info_result_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(new_session->observations));
    char *info_text_result;
    gtk_text_buffer_get_bounds(info_result_buffer, &start, &end);
    info_text_result = gtk_text_buffer_get_text (info_result_buffer, &start, &end, FALSE);
    strcpy(new_session->session->observations, info_text_result);

    /* SAVE DATA IN MODEL */
    if(new_session->origin == 1){
        printf("\nEdit Session\n");
        modifySession(new_session->session);
    }
    else{
        printf("\nNew Session\n");
        addSession(new_session->session);
    }
    launchWorkView(NULL, new_session->window_id);
}

void saveFolderEntries(Folder *folder, GtkWidget *folder_name,GtkWidget *pathology,
                       GtkTextBuffer *other_infos_buffer, GtkWidget *start_treatment){

    strcpy(folder->folderName, gtk_entry_get_text(GTK_ENTRY(folder_name)));
    strcpy(folder->pathology, gtk_entry_get_text(GTK_ENTRY(pathology)));
    strcpy(folder->details, gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(other_infos_buffer)));
    folder->startOfTreatment.day = parseDate((char *)gtk_entry_get_text(GTK_ENTRY(start_treatment)))->day;
    folder->startOfTreatment.month = parseDate((char *)gtk_entry_get_text(GTK_ENTRY(start_treatment)))->month;
    folder->startOfTreatment.year = parseDate((char *)gtk_entry_get_text(GTK_ENTRY(start_treatment)))->year;
    //setFolder();

}

void savePatientEntries(Patient *patient, int origin, GtkWidget *surname, GtkWidget *name,
                        GtkWidget *birth, GtkWidget *weight, GtkWidget *height,
                        GtkWidget *first_consult, GtkWidget *ssn, GtkWidget *number,
                        GtkWidget *email, GtkWidget *gender_combo_box, GtkWidget *address,
                        GtkWidget *city, GtkWidget *postcode, GtkWidget *job,
                        GtkWidget *info_text, GtkTextIter end){

    GtkTextIter start;
    /* NAME */
    strcpy(patient->name, (char*)gtk_entry_get_text(GTK_ENTRY(surname)));
    strcpy(patient->firstname, (char*)gtk_entry_get_text(GTK_ENTRY(name)));

    /* BIRTHDAY */
    patient->birthdate.day = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(birth)))->day;
    patient->birthdate.month = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(birth)))->month;
    patient->birthdate.year = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(birth)))->year;

    /* WEIGHT AND HEIGHT */
    strcpy(patient->weight, (char*)gtk_entry_get_text(GTK_ENTRY(weight)));
    strcpy(patient->height, (char*)gtk_entry_get_text(GTK_ENTRY(height)));

    /* FIRST CONSULTATION */
    patient->first_consultation.day = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(first_consult)))->day;
    patient->first_consultation.month = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(first_consult)))->month;
    patient->first_consultation.year = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(first_consult)))->year;

    /* SOCIAL SECURITY NUMBER */
    strcpy(patient->ssn, (char*) gtk_entry_get_text(GTK_ENTRY(ssn)));

    /* CONTACT */
    strcpy(patient->phone_number, (char*) gtk_entry_get_text(GTK_ENTRY(number)));
    strcpy(patient->mail_address, (char*) gtk_entry_get_text(GTK_ENTRY(email)));

    /* GENDER */
    char *genderResult = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(gender_combo_box));
    if(strcmp(genderResult, "Homme") == 0){
        patient->gender = MAN;
    } else if (strcmp(genderResult, "Femme") == 0){
        patient->gender = WOMAN;
    } else {
        patient->gender = OTHER;
    }

    /* ADDRESS */
    strcpy(patient->address.street, (char*) gtk_entry_get_text(GTK_ENTRY(address)));
    strcpy(patient->address.city, (char*) gtk_entry_get_text(GTK_ENTRY(city)));
    strcpy(patient->address.postCode, (char*) gtk_entry_get_text(GTK_ENTRY(postcode)));
    //other infos

    /* JOB */
    strcpy(patient->job, (char*) gtk_entry_get_text(GTK_ENTRY(job)));

    /* ADDITIONAL INFO */
    GtkTextBuffer *info_result_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(info_text));
    char *info_text_result;
    gtk_text_buffer_get_bounds(info_result_buffer, &start, &end);
    info_text_result = gtk_text_buffer_get_text (info_result_buffer, &start, &end, FALSE);
    strcpy(patient->global_pathologies, info_text_result);

    /* Print for debug */
    //printPatient(patient, "saving data from user entries");

    /* Save data in model */
    if(origin == 1){
        modifyPatient(patient);
    } else {
        addPatient(patient);
    }

}