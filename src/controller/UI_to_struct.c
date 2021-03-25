/*!
* \file UI_to_struct.c
* \brief File with functions used to parse data from UI entries to structures
*/

#include "UI_to_struct.h"
#include "struct_to_BDD_session.h"
#include "../view/work_view.h"
#include "display_helpers.h"



void saveNewSession(GtkWidget *save_button, NewSessionEntries *new_session){
    printf("\n****** TEST ******\n");
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
    if(new_session->origin == 0){
        printf("\nNew Session\n");
        addSession(new_session->session);
    }
    else{
        printf("\nEdit Session\n");
        modifySession(new_session->session);
    }
}