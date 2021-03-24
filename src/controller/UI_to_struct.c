/*!
* \file UI_to_struct.c
* \brief File with functions used to parse data from UI entries to structures
*/

#include "UI_to_struct.h"
#include "struct_to_BDD_session.h"

/*!
 * \brief Parse string date to Date format
 *
 * \param[in] stringDate source string date
 * \param[out] destination Date structure
*/
Date *parseDate(char *stringDate){
    Date *date = (Date *) malloc(sizeof(Date));
    int yyyy;
    int mm;
    int dd;
    sscanf(stringDate, "%d/%d/%d", &dd, &mm, &yyyy);
    date->year = yyyy;
    date->month = mm;
    date->day = dd;
    return date;
}

void saveNewSession(GtkWidget *save_button, NewSessionEntries *new_session){
    /* SESSION NAME */
    printf("\n********* TEST1 ***********\n");
    strcpy(new_session->session->sessionName, (char*)gtk_entry_get_text(GTK_ENTRY(new_session->sessionName)));

    /* SESSION DATES */
    printf("\n********* TEST2 ***********\n");
    new_session->session->sessionDate.day = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(new_session->sessionDate)))->day;
    new_session->session->sessionDate.month = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(new_session->sessionDate)))->month;
    new_session->session->sessionDate.year = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(new_session->sessionDate)))->year;

    new_session->session->nextSessionDate.day = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(new_session->nextSessionDate)))->day;
    new_session->session->nextSessionDate.month = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(new_session->nextSessionDate)))->month;
    new_session->session->nextSessionDate.year = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(new_session->nextSessionDate)))->year;

    /* SESSION OBSERVATIONS */
    printf("\n********* TEST3 ***********\n");
    GtkTextIter start, end;
    GtkTextBuffer *info_result_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(new_session->observations));
    char *info_text_result;
    gtk_text_buffer_get_bounds(info_result_buffer, &start, &end);
    info_text_result = gtk_text_buffer_get_text (info_result_buffer, &start, &end, FALSE);
    strcpy(new_session->session->observations, info_text_result);

    printf("\n********* TEST4 ***********\n");
    /* SAVE DATA IN MODEL */
    if(new_session->origin == 1){
        printf("\nEdit Session\n");
    }
    else{
        addSession(new_session->session);
    }

}