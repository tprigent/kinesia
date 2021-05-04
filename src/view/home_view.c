/*!
* \file home_view.c
* \brief File to initiate the homepage view (calendar, patient list, ...)
*/

#include <gtk/gtk.h>
#include "home_view.h"
#include "work_view.h"
#include "editor_views.h"
#include "../controller/display_helpers.h"
#include "../controller/BDD_to_struct_session.h"
#include "../controller/BDD_to_struct_folder.h"
#include "../model/patient_manager.h"
#include "../model/folder_manager.h"
#include "../model/session_manager.h"

/*!
 * \brief Function that launch css mode to modify application style
 *
 * This function set necessary parameters to load css and use css files
 *
 * \param[in] cssMode : int to tell which mode to display (normal or dark mode)
*/
static void load_css(int cssMode){
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    const gchar *css_style_file = NULL;
    if(cssMode == 0) css_style_file = "../src/view/whiteMode.css";
    else css_style_file = "../src/view/darkMode.css";

    GFile *css_fp = g_file_new_for_path(css_style_file);
    GError *error = 0;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_file(provider, css_fp, &error);

    g_object_unref(provider);
}

/*!
 * \brief Initiate patient window which shows a list of the patient and the meetings
 *
 * Focus, position, size, title and destroy callback are set.
 *
 * \param[in] firstLoad : to tell if css file has to be charged (1) or not (0)
 * \param[in] fullScreen : to tell if the window has to be load fullscreen or not
 * \param[in] cssMode : to tell which mode to display (normal or dark mode)
*/
GtkWidget *setHomeWindow(int firstLoad, int fullScreen, int cssMode){

    if(firstLoad == 1) {
        gtk_init(NULL, NULL);
        load_css(cssMode);
    }

    GtkWidget *window = NULL;
    GdkPixbuf *symbolPixbuf = NULL;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_activate_focus(GTK_WINDOW(window));
    gtk_window_set_title(GTK_WINDOW(window), "Kinesia");

    symbolPixbuf = gdk_pixbuf_new_from_file("../media/graphic-assets/logo.jpg", NULL);
    gtk_window_set_icon(GTK_WINDOW(window), symbolPixbuf);

    if(strcmp(OS, "macOS") == 0){
        gtk_window_set_default_size(GTK_WINDOW(window), 1200, 720);
    } else if(fullScreen) gtk_window_maximize(GTK_WINDOW(window));
    else gtk_window_unmaximize(GTK_WINDOW(window));
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_destroy_with_parent(GTK_WINDOW(window), FALSE);
    setHomeEnvironment(window, cssMode);
    gtk_widget_show_all(window);
    gtk_main();

    return window;
}

/*!
 * \brief Split the main window in two spaces and fill them
 *
 * The two spaces are:
 * on the left side a calendar and buttons to archive patients,
 * at the right side a list of patients, an search-entry and a button to create a patient.
 *
 * \param[in] window : Home window to fill
 * \patam[in] cssMode : to tell which mode to display (normal or dark mode)
*/
void setHomeEnvironment(GtkWidget *window, int cssMode){

    /* DECLARE VARIABLES */
    GtkWidget *grid = NULL;
    GtkWidget *grid_calendar = NULL;
    GtkWidget *grid_active_patient = NULL;
    GtkWidget *grid_archived_patient = NULL;

    GtkWidget *frame_calendar = NULL;

    GtkWidget *box_active_patient = NULL;
    GtkWidget *box_archived_patient = NULL;
    GtkWidget *box_meetings = NULL;

    GtkWidget *button_parameters = NULL;
    GtkWidget *calendar = NULL;
    GtkWidget *button_new_patient = NULL;
    GtkWidget *entry_search = NULL;
    GtkWidget *tabs = NULL;

    GtkWidget *upcoming_title = NULL;


    /* ASSIGN VARIABLES */
    grid = gtk_grid_new();
    grid_active_patient = gtk_grid_new();
    grid_archived_patient = gtk_grid_new();
    grid_calendar = gtk_grid_new();

    frame_calendar = gtk_frame_new("AGENDA");

    box_active_patient = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(box_active_patient), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    box_archived_patient = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(box_archived_patient), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

    button_parameters = gtk_button_new_from_icon_name("emblem-system", GTK_ICON_SIZE_MENU);
    calendar = gtk_calendar_new();
    button_new_patient = gtk_button_new_from_icon_name("list-add", GTK_ICON_SIZE_MENU);
    entry_search = gtk_search_entry_new();
    tabs = gtk_notebook_new();

    upcoming_title = gtk_label_new("<u>Rendez-vous prévus</u>:");
    gtk_label_set_use_markup(GTK_LABEL(upcoming_title), TRUE);

    /* GRID WHICH ORGANIZES THE WINDOW */
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_hexpand(grid, TRUE);
    gtk_widget_set_vexpand(grid, TRUE);

    /* FILL THE GRID */
    /* Left part */
    gtk_grid_attach(GTK_GRID(grid), frame_calendar, GTK_ALIGN_START, GTK_ALIGN_START, 1, 14);
    gtk_widget_set_hexpand(frame_calendar, TRUE);
    gtk_widget_set_vexpand(frame_calendar, TRUE);

    gtk_container_add(GTK_CONTAINER(frame_calendar), grid_calendar);
    gtk_grid_set_row_spacing(GTK_GRID(grid_calendar), 5);

    // Parameters button
    gtk_grid_attach(GTK_GRID(grid_calendar), button_parameters, GTK_ALIGN_END, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(button_parameters, FALSE);
    gtk_widget_set_halign(button_parameters, GTK_ALIGN_END);
    gtk_widget_set_tooltip_text(button_parameters, "Réglages");
    SoftwareSettings *settings = (SoftwareSettings*) malloc(sizeof(SoftwareSettings));
    settings->window = window;
    settings->cssMode = cssMode;
    g_signal_connect(GTK_BUTTON(button_parameters), "clicked", G_CALLBACK(launchSettingsEditor), settings);

    // Calendar
    gtk_grid_attach_next_to(GTK_GRID(grid_calendar), calendar, button_parameters, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(calendar, TRUE);

    // Upcoming meetings
    gtk_grid_attach_next_to(GTK_GRID(grid_calendar), upcoming_title, calendar, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_margin_top(upcoming_title, 10);

    CalendarView *params = (CalendarView*) malloc(sizeof(CalendarView));
    params->vbox = box_meetings;
    params->title = upcoming_title;
    params->window = window;
    params->grid = grid_calendar;

    // For first launch: d-day
    params->atLoad = 1;
    seeAppointmentsAtDate(GTK_CALENDAR(calendar), params);

    // For user choice: x-day
    params->atLoad = 0;
    g_signal_connect(GTK_CALENDAR(calendar), "day-selected", G_CALLBACK(seeAppointmentsAtDate), params);


    /* Search a patient */
    gtk_grid_attach_next_to(GTK_GRID(grid), entry_search, frame_calendar, GTK_POS_RIGHT, 2, 1);
    gtk_widget_set_valign(entry_search, GTK_ALIGN_START);
    gtk_widget_set_hexpand(entry_search, TRUE);
    gtk_widget_set_tooltip_text(entry_search, "Rechercher un patient");
    SearchParam *patientSearchParam = (SearchParam *) malloc(sizeof(SearchParam));
    patientSearchParam->entry = entry_search;
    patientSearchParam->notebook = tabs;
    patientSearchParam->window = window;
    g_signal_connect(entry_search, "search-changed", G_CALLBACK(processSearch), patientSearchParam);

    /* Add a new patient */
    g_signal_connect(GTK_BUTTON(button_new_patient), "clicked", G_CALLBACK(launchNewPatientEditor), window);
    gtk_grid_attach_next_to(GTK_GRID(grid), button_new_patient, entry_search, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_halign(button_new_patient, GTK_ALIGN_END);
    gtk_widget_set_valign(button_new_patient, GTK_ALIGN_START);
    gtk_widget_set_hexpand(button_new_patient, TRUE);
    gtk_widget_set_tooltip_text(button_new_patient, "Ajouter un patient");

    /* Box patient */
    gtk_grid_attach_next_to(GTK_GRID(grid), tabs, entry_search, GTK_POS_BOTTOM, 6,1);
    gtk_widget_set_hexpand(tabs, TRUE);
    gtk_widget_set_vexpand(tabs, TRUE);
    gtk_widget_set_margin_top(tabs, 15);
    gtk_grid_set_row_spacing(GTK_GRID(grid_active_patient), 5);
    gtk_container_add(GTK_CONTAINER(box_active_patient), grid_active_patient);
    gtk_grid_set_row_spacing(GTK_GRID(grid_archived_patient), 5);
    gtk_container_add(GTK_CONTAINER(box_archived_patient), grid_archived_patient);

    /* Add tabs */
    gtk_notebook_append_page(GTK_NOTEBOOK(tabs), box_active_patient, gtk_label_new("Patients actifs"));
    gtk_notebook_append_page(GTK_NOTEBOOK(tabs), box_archived_patient, gtk_label_new("Archives"));

    /* ADD PATIENTS */
    int i;
    char** nameActivePatient;
    int* idActivePatient;

    /* ACTIVE PATIENTS */
    int nbActivePatient = getNbPatient(ACTIVE);
    GtkWidget *active_patient_button[nbActivePatient];
    GtkWidget *archive_button[nbActivePatient];
    GtkWidget *active_delete_button[nbActivePatient];

    idActivePatient = (int*)calloc(nbActivePatient,sizeof(int));
    nameActivePatient = (char**)calloc(nbActivePatient,sizeof(void *));

    getNameFirstnameIdPatient(idActivePatient,nameActivePatient,ACTIVE,NAME_DESC);

    for(i=0; i < nbActivePatient; i++){
        active_patient_button[i] = gtk_button_new_with_label(nameActivePatient[i]);
        archive_button[i] = gtk_button_new_from_icon_name("user-trash", GTK_ICON_SIZE_MENU);
        active_delete_button[i] = gtk_button_new_from_icon_name("edit-delete", GTK_ICON_SIZE_MENU);
        gtk_widget_set_tooltip_text(archive_button[i], "Archiver");
        gtk_widget_set_tooltip_text(active_delete_button[i], "Supprimer");

        if (i == 0){
            gtk_grid_attach(GTK_GRID(grid_active_patient), active_patient_button[0], GTK_ALIGN_START, GTK_ALIGN_START, 5, 1);
            gtk_widget_set_margin_top(active_patient_button[0], 5);
        } else {
            gtk_grid_attach_next_to(GTK_GRID(grid_active_patient), active_patient_button[i], active_patient_button[i-1],GTK_POS_BOTTOM, 5, 1);
        }
        gtk_widget_set_hexpand(active_patient_button[i], TRUE);
        gtk_widget_set_vexpand(active_patient_button[i], FALSE);

        gtk_grid_attach_next_to(GTK_GRID(grid_active_patient), archive_button[i], active_patient_button[i], GTK_POS_RIGHT, 1, 1);
        gtk_grid_attach_next_to(GTK_GRID(grid_active_patient), active_delete_button[i], archive_button[i], GTK_POS_RIGHT, 1, 1);
        if (i == 0){
            gtk_widget_set_margin_top(archive_button[i], 5);
            gtk_widget_set_margin_top(active_delete_button[i], 5);
        }

        WarningType *deleteActiveWarning[nbActivePatient];
        deleteActiveWarning[i] = (WarningType*) malloc(sizeof(WarningType));
        deleteActiveWarning[i]->patientID = idActivePatient[i];
        deleteActiveWarning[i]->window = window;
        deleteActiveWarning[i]->actionType = 0;

        WarningType *archiveWarning[nbActivePatient];
        archiveWarning[i] = (WarningType*) malloc(sizeof(WarningType));
        archiveWarning[i]->patientID = idActivePatient[i];
        archiveWarning[i]->window = window;
        archiveWarning[i]->actionType = 1;

        Window_id *window_id_active[nbActivePatient];
        window_id_active[i] = (Window_id*) malloc(sizeof(Window_id));
        window_id_active[i]->window = window;
        window_id_active[i]->patientID = idActivePatient[i];
        window_id_active[i]->folderID = 0;
        g_signal_connect(GTK_BUTTON(archive_button[i]), "clicked", G_CALLBACK(launchPatientWarning), archiveWarning[i]);
        g_signal_connect(GTK_BUTTON(active_delete_button[i]), "clicked", G_CALLBACK(launchPatientWarning), deleteActiveWarning[i]);
        g_signal_connect(GTK_BUTTON(active_patient_button[i]), "clicked", G_CALLBACK(launchWorkView), window_id_active[i]);
    }

    free(idActivePatient);

    for(i=0;i<nbActivePatient;i++)
        free(nameActivePatient[i]);

    free(nameActivePatient);

    /* ARCHIVED PATIENTS */
    int nbArchivedPatient = getNbPatient(ARCHIVED);
    int* idArchivePatient = NULL;
    char** nomArchivePatient = NULL;

    GtkWidget *archived_patient_button[nbArchivedPatient];
    GtkWidget *unarchive_button[nbArchivedPatient];
    GtkWidget *archived_delete_button[nbArchivedPatient];

    idArchivePatient = (int*)calloc(nbArchivedPatient,sizeof(int));
    nomArchivePatient = (char**)calloc(nbArchivedPatient,sizeof(void *));

    getNameFirstnameIdPatient(idArchivePatient,nomArchivePatient,ARCHIVED,NAME_ASC);

    for(i=0; i < nbArchivedPatient; i++){
        archived_patient_button[i] = gtk_button_new_with_label(nomArchivePatient[i]);
        unarchive_button[i] = gtk_button_new_from_icon_name("edit-undo", GTK_ICON_SIZE_MENU);
        archived_delete_button[i] = gtk_button_new_from_icon_name("edit-delete", GTK_ICON_SIZE_MENU);
        gtk_widget_set_tooltip_text(unarchive_button[i], "Réactiver");
        gtk_widget_set_tooltip_text(archived_delete_button[i], "Supprimer");

        if(i == 0){
            gtk_grid_attach(GTK_GRID(grid_archived_patient), archived_patient_button[i], GTK_ALIGN_START, GTK_ALIGN_START, 5, 1);
            gtk_widget_set_margin_top(archived_patient_button[i], 5);
        } else {
            gtk_grid_attach_next_to(GTK_GRID(grid_archived_patient), archived_patient_button[i], archived_patient_button[i-1],GTK_POS_BOTTOM, 5, 1);
        }
        gtk_widget_set_hexpand(archived_patient_button[i], TRUE);
        gtk_widget_set_vexpand(archived_patient_button[i], FALSE);

        gtk_grid_attach_next_to(GTK_GRID(grid_archived_patient), unarchive_button[i], archived_patient_button[i], GTK_POS_RIGHT, 1, 1);
        gtk_grid_attach_next_to(GTK_GRID(grid_archived_patient), archived_delete_button[i], unarchive_button[i], GTK_POS_RIGHT, 1, 1);

        if (i == 0){
            gtk_widget_set_margin_top(unarchive_button[i], 5);
            gtk_widget_set_margin_top(archived_delete_button[i], 5);
        }

        WarningType *deleteArchivedWarning[nbArchivedPatient];
        deleteArchivedWarning[i] = (WarningType*) malloc(sizeof(WarningType));
        deleteArchivedWarning[i]->patientID = idArchivePatient[i];
        deleteArchivedWarning[i]->window = window;
        deleteArchivedWarning[i]->actionType = 0;

        WarningType *unarchiveWarning[nbArchivedPatient];
        unarchiveWarning[i] = (WarningType*) malloc(sizeof(WarningType));
        unarchiveWarning[i]->patientID = idArchivePatient[i];
        unarchiveWarning[i]->window = window;
        unarchiveWarning[i]->actionType = 1;

        Window_id *window_id_archived[nbArchivedPatient];
        window_id_archived[i] = (Window_id*) malloc(sizeof(Window_id));
        window_id_archived[i]->window = window;
        window_id_archived[i]->patientID = idArchivePatient[i];
        window_id_archived[i]->folderID = 0;
        g_signal_connect(GTK_BUTTON(unarchive_button[i]), "clicked", G_CALLBACK(launchPatientWarning), unarchiveWarning[i]);
        g_signal_connect(GTK_BUTTON(archived_delete_button[i]), "clicked", G_CALLBACK(launchPatientWarning), deleteArchivedWarning[i]);
        g_signal_connect(GTK_BUTTON(archived_patient_button[i]), "clicked", G_CALLBACK(launchWorkView), window_id_archived[i]);
    }

    free(idArchivePatient);

    for(i=0;i<nbArchivedPatient;i++)
        free(nomArchivePatient[i]);

    free(nomArchivePatient);

    //Have to free window_id tabb (can't be done here)*/

}

/*!
 * \brief Allows to close the Work window and open the Home window
 *
 * When the user click on the back button from a session window, this function closes
 * the current Work window and open the Home window.
 *
 * \param[in] but : Button clicked to call this function
 * \param[in] window : Current window that have to be closed
*/
void launchHomeView(GtkWidget *but, GtkWidget *window){
    int fullScreen = 0;
    if(gtk_window_is_maximized(GTK_WINDOW(window))==TRUE) fullScreen = 1;
    gtk_widget_destroy(window);
    setHomeWindow(0, fullScreen, 0);
}

/*!
 * \brief show on screen the result of the patient research
 *
 * This function add a page in the notebook with the result of the research
 *
 * \param[in] button : Button clicked to call this function
 * \param[in] search : structure containing widgets to update window (notebook & search entry)
*/
void processSearch(GtkWidget *button, SearchParam *search){

    /* Check if entry is null */
    char *searchEntry = (char*) gtk_entry_get_text(GTK_ENTRY(search->entry));
    if(strcmp(searchEntry, "") == 0) return;

    /* Initialise variables */
    GtkWidget *grid_searched_patient;
    GtkWidget *box_searched_patient;
    GtkWidget *no_patient_found_label;

    char *tabTitle = (char*) malloc(sizeof(char)*(strlen(searchEntry)+strlen("Recherche: \" \"")));

    char **searchResult = (char**) malloc(sizeof(char)*1000);
    int *idResult = (int*) malloc(sizeof(int));

    int nbOfResults = searchPatient(searchEntry, searchResult, idResult, 500);

    /* Define containers */
    grid_searched_patient = gtk_grid_new();
    box_searched_patient = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(box_searched_patient), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);


    gtk_grid_set_row_spacing(GTK_GRID(grid_searched_patient), 5);
    gtk_container_add(GTK_CONTAINER(box_searched_patient), grid_searched_patient);

    /* Set tab content */
    int i;
    GtkWidget *searched_patient_button[nbOfResults];

    if(nbOfResults == 0){
        no_patient_found_label = gtk_label_new("<big><i>Aucun patient correspondant à la recherche...</i></big>");
        gtk_label_set_use_markup(GTK_LABEL(no_patient_found_label), TRUE);
        gtk_grid_attach(GTK_GRID(grid_searched_patient), no_patient_found_label, GTK_ALIGN_CENTER, GTK_ALIGN_CENTER, 1, 1);
        gtk_widget_set_hexpand(no_patient_found_label, TRUE);
        gtk_widget_set_vexpand(no_patient_found_label, TRUE);
    }

    for(i=0; i < nbOfResults ; i++) {
        searched_patient_button[i] = gtk_button_new_with_label(searchResult[i]);

        if (i == 0) {
            gtk_grid_attach(GTK_GRID(grid_searched_patient), searched_patient_button[0], GTK_ALIGN_START, GTK_ALIGN_START, 5, 1);
            gtk_widget_set_margin_top(searched_patient_button[0], 5);
        } else {
            gtk_grid_attach_next_to(GTK_GRID(grid_searched_patient), searched_patient_button[i], searched_patient_button[i - 1],
                                    GTK_POS_BOTTOM, 5, 1);
        }
        gtk_widget_set_hexpand(searched_patient_button[i], TRUE);
        gtk_widget_set_vexpand(searched_patient_button[i], FALSE);

        Window_id *window_id_searched[nbOfResults];
        window_id_searched[i] = (Window_id*) malloc(sizeof(Window_id));
        window_id_searched[i]->window = search->window;
        window_id_searched[i]->patientID = idResult[i];
        window_id_searched[i]->folderID = 0;
        g_signal_connect(GTK_BUTTON(searched_patient_button[i]), "clicked", G_CALLBACK(launchWorkView), window_id_searched[i]);


    }

    /* Refresh the notebook */
    strcpy(tabTitle, "Recherche: \"");
    strcat(tabTitle, searchEntry);
    strcat(tabTitle, "\"");
    if(gtk_notebook_get_n_pages(GTK_NOTEBOOK(search->notebook))) {
        gtk_notebook_remove_page(GTK_NOTEBOOK(search->notebook), 2);
    }
    gtk_notebook_insert_page(GTK_NOTEBOOK(search->notebook), box_searched_patient, gtk_label_new(tabTitle), -1);

    gtk_widget_show_all(search->notebook);
    gtk_notebook_set_current_page(GTK_NOTEBOOK(search->notebook), -1);
    gtk_widget_show_all(search->notebook);

    free(searchResult);
    free(idResult);
}

/*!
 * \brief Display appointments scheduled for the selected day
 *
 * \param[in] calendar Calendar mastering the view
 * \param[in] params Structure of parameters needed
*/
void seeAppointmentsAtDate(GtkCalendar *calendar, CalendarView *params){
    Date *date = (Date *) malloc(sizeof(Date));
    unsigned int year, month, day;

    if(params->atLoad){
        date = parseDate(get_current_date());
    } else {
        gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);
        date->year = (int) year;
        date->month = (int) month + 1;
        date->day = (int) day;
    }

    /* Remove old items */
    gtk_grid_remove_row(GTK_GRID(params->grid), 4);
    params->vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_grid_attach_next_to(GTK_GRID(params->grid), params->vbox, params->title, GTK_POS_BOTTOM, 1, 1);

    /* Add new items */
    int *sessionAtDateID = (int *) malloc(sizeof(int));
    int *folderAtDateID = (int *) malloc(sizeof(int));
    int nbSessionsAtDate = getSessionsAtDate(date, sessionAtDateID, folderAtDateID);

    int k;
    if(nbSessionsAtDate > 0){
        GtkWidget *upcoming_patient[nbSessionsAtDate];
        GtkWidget *upcoming_meeting[nbSessionsAtDate];
        GtkWidget *upcoming_button[nbSessionsAtDate];
        GtkWidget *meeting_box[nbSessionsAtDate];
        GtkWidget *meeting_grid[nbSessionsAtDate];

        for(k = 0; k<nbSessionsAtDate; k++){

            /* Define elements */
            int patientID = getPatientIDFromFolder(folderAtDateID[k]);
            char *patientName = getNameFirstnamePatient(patientID);
            char *hour = getSession(sessionAtDateID[k])->nextSessionHour;
            upcoming_patient[k] = gtk_label_new(patientName);
            upcoming_meeting[k] = gtk_label_new(hour);
            upcoming_button[k] = gtk_button_new_from_icon_name("mail-replied-symbolic", GTK_ICON_SIZE_MENU);
            meeting_box[k] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
            meeting_grid[k] = gtk_grid_new();
            gtk_widget_set_tooltip_text(upcoming_button[k], "Accéder au dossier");

            /* Fill the view */
            gtk_box_pack_start(GTK_BOX(meeting_box[k]), meeting_grid[k], TRUE, TRUE, 0);
            gtk_grid_attach(GTK_GRID(meeting_grid[k]), upcoming_patient[k], GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
            gtk_grid_attach_next_to(GTK_GRID(meeting_grid[k]), upcoming_meeting[k], upcoming_patient[k], GTK_POS_RIGHT, 1, 1);
            gtk_grid_attach_next_to(GTK_GRID(meeting_grid[k]), upcoming_button[k], upcoming_meeting[k], GTK_POS_RIGHT, 1, 1);

            gtk_grid_set_column_spacing(GTK_GRID(meeting_grid[k]), 10);
            gtk_widget_set_hexpand(upcoming_patient[k], TRUE);
            gtk_widget_set_margin_start(upcoming_patient[k], 18);
            gtk_widget_set_halign(upcoming_patient[k], GTK_ALIGN_START);
            gtk_widget_set_hexpand(upcoming_meeting[k], FALSE);
            gtk_widget_set_halign(upcoming_meeting[k], GTK_ALIGN_END);
            gtk_widget_set_hexpand(upcoming_button[k], FALSE);
            gtk_widget_set_halign(upcoming_button[k], GTK_ALIGN_END);

            gtk_box_pack_start(GTK_BOX(params->vbox), meeting_box[k], TRUE, TRUE, 0);

            /* Manage the quick access button */
            Window_id *work_param[nbSessionsAtDate];
            work_param[k] = (Window_id*) malloc(sizeof(Window_id));
            work_param[k]->window = params->window;
            work_param[k]->patientID = patientID;
            work_param[k]->folderID = folderAtDateID[k];
            g_signal_connect(GTK_BUTTON(upcoming_button[k]), "clicked", G_CALLBACK(launchWorkView), work_param[k]);
        }
    } else {        // if noting is scheduled for this day
        GtkWidget *noAppointmentToday = NULL;
        noAppointmentToday = gtk_label_new("<i>Rien de programmé</i>");
        gtk_label_set_use_markup(GTK_LABEL(noAppointmentToday), TRUE);
        gtk_box_pack_start(GTK_BOX(params->vbox), noAppointmentToday, TRUE, TRUE, 0);
        //gtk_grid_attach_next_to(GTK_GRID(params->grid), noAppointmentToday, params->title, GTK_POS_BOTTOM, 6, 1);
        gtk_widget_set_margin_top(noAppointmentToday, 15);
        gtk_widget_set_halign(noAppointmentToday, GTK_ALIGN_CENTER);
        gtk_widget_set_hexpand(noAppointmentToday, FALSE);
    }

    gtk_widget_show_all(params->grid);
    free(date);
}
