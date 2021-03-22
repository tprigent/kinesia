/*!
* \file home_views.c
* \brief File to initiate the homepage view (calendar, patient list, ...)
*/

#include <gtk/gtk.h>
#include "home_view.h"
#include "work_view.h"
#include "editor_views.h"
#include "../controller/struct_to_UI.h"


/*!
 * \brief Initiate patient window which shows a list of the patient
 *
 * Focus, position, size, title and destroy callback are set.
 * \todo change the name of the window once the software name found
*/
GtkWidget *setHomeWindow(){

    GtkWidget *window = NULL;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_activate_focus(GTK_WINDOW(window));
    gtk_window_set_title(GTK_WINDOW(window), "Kinesia");
    gtk_window_set_default_size(GTK_WINDOW(window), 1200, 720);
    gtk_window_maximize(GTK_WINDOW(window));
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_destroy_with_parent(GTK_WINDOW(window), FALSE);
    setHomeEnvironment(window);
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
 *
 * \param[in] window Patient window to fill
*/
void setHomeEnvironment(GtkWidget *window){

    /* DECLARE VARIABLES */
    GtkWidget *grid = NULL;
    GtkWidget *grid_calendar = NULL;
    GtkWidget *grid_active_patient = NULL;
    GtkWidget *grid_archived_patient = NULL;

    GtkWidget *frame_test = NULL;

    GtkWidget *box_active_patient = NULL;
    GtkWidget *box_archived_patient = NULL;

    GtkWidget *calendar = NULL;
    GtkWidget *button_new_patient = NULL;
    GtkWidget *entry_research = NULL;
    GtkWidget *button_research = NULL;
    GtkWidget *tabs = NULL;


    /* ASSIGN VARIABLES */
    grid = gtk_grid_new();
    grid_active_patient = gtk_grid_new();
    grid_archived_patient = gtk_grid_new();
    grid_calendar = gtk_grid_new();

    frame_test = gtk_frame_new("CALENDRIER");

    box_active_patient = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(box_active_patient), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    box_archived_patient = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(box_archived_patient), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    
    calendar = gtk_calendar_new();
    button_new_patient = gtk_button_new_from_icon_name("list-add", GTK_ICON_SIZE_MENU);
    entry_research = gtk_entry_new();
    button_research = gtk_button_new_from_icon_name("system-search", GTK_ICON_SIZE_MENU);
    tabs = gtk_notebook_new();

    /* GRID WHICH ORGANIZES THE WINDOW */
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_hexpand(grid, TRUE);
    gtk_widget_set_vexpand(grid, TRUE);

    /* FILL THE GRID */
    /* Left part */
    gtk_grid_attach(GTK_GRID(grid), frame_test, GTK_ALIGN_START, GTK_ALIGN_START, 1, 14);
    gtk_widget_set_hexpand(frame_test, TRUE);
    gtk_widget_set_vexpand(frame_test, TRUE);

    gtk_container_add(GTK_CONTAINER(frame_test), grid_calendar);
    gtk_grid_set_row_spacing(GTK_GRID(grid_calendar), 5);

    gtk_grid_attach(GTK_GRID(grid_calendar), calendar, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(calendar, TRUE);


    /* Search a patient */
    gtk_grid_attach_next_to(GTK_GRID(grid), entry_research, frame_test, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_valign(entry_research, GTK_ALIGN_START);
    gtk_widget_set_hexpand(entry_research, TRUE);
    gtk_grid_attach_next_to(GTK_GRID(grid), button_research, entry_research, GTK_POS_RIGHT, 3, 1);
    gtk_widget_set_halign(button_research, GTK_ALIGN_START);
    gtk_widget_set_valign(button_research, GTK_ALIGN_START);
    gtk_widget_set_hexpand(button_research, TRUE);

    /* Add a new patient */
    g_signal_connect(GTK_BUTTON(button_new_patient), "clicked", G_CALLBACK(launchNewPatientEditor), window);
    gtk_grid_attach_next_to(GTK_GRID(grid), button_new_patient, button_research, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_halign(button_new_patient, GTK_ALIGN_END);
    gtk_widget_set_valign(button_new_patient, GTK_ALIGN_START);
    gtk_widget_set_hexpand(button_new_patient, TRUE);

    /* Box patient */
    gtk_grid_attach_next_to(GTK_GRID(grid), tabs, entry_research, GTK_POS_BOTTOM, 6,1);
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
    int nb_patient = getNbPatient();
    char *patient_name;

    /* ACTIVE PATIENTS */
    int *activePatient = getActivePatientID();
    int nbActivePatient = getNbActivePatient();
    GtkWidget *active_patient_button[getNbActivePatient()];
    GtkWidget *active_archive_button[getNbActivePatient()];
    GtkWidget *active_delete_button[getNbActivePatient()];

    /* Initialize first patient */
    patient_name = getNameFirstnamePatient(activePatient[0]);
    active_patient_button[0] = gtk_button_new_with_label(patient_name);
    active_archive_button[0] = gtk_button_new_from_icon_name("user-trash", GTK_ICON_SIZE_MENU);
    active_delete_button[0] = gtk_button_new_from_icon_name("edit-delete", GTK_ICON_SIZE_MENU);

    gtk_grid_attach(GTK_GRID(grid_active_patient), active_patient_button[0], GTK_ALIGN_START, GTK_ALIGN_START, 5, 1);
    gtk_widget_set_margin_top(active_patient_button[0], 5);
    gtk_widget_set_hexpand(active_patient_button[0], TRUE);
    gtk_widget_set_vexpand(active_patient_button[0], FALSE);

    gtk_grid_attach_next_to(GTK_GRID(grid_active_patient), active_archive_button[0], active_patient_button[0], GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_margin_top(active_archive_button[0], 5);
    gtk_grid_attach_next_to(GTK_GRID(grid_active_patient), active_delete_button[0], active_archive_button[0], GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_margin_top(active_delete_button[0], 5);

    WarningType *deleteActiveWarning[nbActivePatient];
    deleteActiveWarning[0] = (WarningType*) malloc(sizeof(WarningType));
    deleteActiveWarning[0]->patientID = activePatient[0];
    deleteActiveWarning[0]->window = window;
    deleteActiveWarning[0]->actionType = 0;

    WarningType *archiveWarning[nbActivePatient];
    archiveWarning[0] = (WarningType*) malloc(sizeof(WarningType));
    archiveWarning[0]->patientID = activePatient[0];
    archiveWarning[0]->window = window;
    archiveWarning[0]->actionType = 1;

    Window_id *window_id_active[nbActivePatient];
    window_id_active[0] = (Window_id*) malloc(sizeof(Window_id));
    window_id_active[0]->window = window;
    window_id_active[0]->id = activePatient[0];
    window_id_active[0]->session = createEmptySession();

    g_signal_connect(GTK_BUTTON(active_patient_button[0]), "clicked", G_CALLBACK(launchWorkView), window_id_active[0]);
    g_signal_connect(GTK_BUTTON(active_archive_button[0]), "clicked", G_CALLBACK(launchPatientWarning), archiveWarning[0]);
    g_signal_connect(GTK_BUTTON(active_delete_button[0]), "clicked", G_CALLBACK(launchPatientWarning), deleteActiveWarning[0]);

    for(i=1; i < nbActivePatient; i++){
        patient_name = getNameFirstnamePatient(activePatient[i]);
        active_patient_button[i] = gtk_button_new_with_label(patient_name);
        active_archive_button[i] = gtk_button_new_from_icon_name("user-trash", GTK_ICON_SIZE_MENU);
        active_delete_button[i] = gtk_button_new_from_icon_name("edit-delete", GTK_ICON_SIZE_MENU);

        gtk_grid_attach_next_to(GTK_GRID(grid_active_patient), active_patient_button[i], active_patient_button[i-1],GTK_POS_BOTTOM, 5, 1);
        gtk_widget_set_hexpand(active_patient_button[i], TRUE);
        gtk_widget_set_vexpand(active_patient_button[i], FALSE);

        gtk_grid_attach_next_to(GTK_GRID(grid_active_patient), active_archive_button[i], active_patient_button[i], GTK_POS_RIGHT, 1, 1);
        gtk_grid_attach_next_to(GTK_GRID(grid_active_patient), active_delete_button[i], active_archive_button[i], GTK_POS_RIGHT, 1, 1);

        deleteActiveWarning[i] = (WarningType*) malloc(sizeof(WarningType));
        deleteActiveWarning[i]->patientID = activePatient[i];
        deleteActiveWarning[i]->window = window;
        deleteActiveWarning[i]->actionType = 0;
        archiveWarning[i] = (WarningType*) malloc(sizeof(WarningType));
        archiveWarning[i]->patientID = activePatient[i];
        archiveWarning[i]->window = window;
        archiveWarning[i]->actionType = 1;
        window_id_active[i] = (Window_id*) malloc(sizeof(Window_id));
        window_id_active[i]->window = window;
        window_id_active[i]->id = activePatient[i];
        window_id_active[i]->session = createEmptySession();
        g_signal_connect(GTK_BUTTON(active_archive_button[i]), "clicked", G_CALLBACK(launchPatientWarning), archiveWarning[i]);
        g_signal_connect(GTK_BUTTON(active_delete_button[i]), "clicked", G_CALLBACK(launchPatientWarning), deleteActiveWarning[i]);
        g_signal_connect(GTK_BUTTON(active_patient_button[i]), "clicked", G_CALLBACK(launchWorkView), window_id_active[i]);
    }

    /* ARCHIVED PATIENTS */
    int *archivedPatient = getArchivedPatientID();
    int nbArchivedPatient = getNbArchivedPatient();
    GtkWidget *archived_patient_button[getNbArchivedPatient()];
    GtkWidget *archived_archive_button[getNbArchivedPatient()];
    GtkWidget *archived_delete_button[getNbArchivedPatient()];

    /* Initialize first patient */
    patient_name = getNameFirstnamePatient(archivedPatient[0]);
    archived_patient_button[0] = gtk_button_new_with_label(patient_name);
    archived_archive_button[0] = gtk_button_new_from_icon_name("user-trash", GTK_ICON_SIZE_MENU);
    archived_delete_button[0] = gtk_button_new_from_icon_name("edit-delete", GTK_ICON_SIZE_MENU);

    gtk_grid_attach(GTK_GRID(grid_archived_patient), archived_patient_button[0], GTK_ALIGN_START, GTK_ALIGN_START, 5, 1);
    gtk_widget_set_margin_top(archived_patient_button[0], 5);
    gtk_widget_set_hexpand(archived_patient_button[0], TRUE);
    gtk_widget_set_vexpand(archived_patient_button[0], FALSE);

    gtk_grid_attach_next_to(GTK_GRID(grid_archived_patient), archived_archive_button[0], archived_patient_button[0], GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_margin_top(archived_archive_button[0], 5);
    gtk_grid_attach_next_to(GTK_GRID(grid_archived_patient), archived_delete_button[0], archived_archive_button[0], GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_margin_top(archived_delete_button[0], 5);

    WarningType *deleteArchivedWarning[nbArchivedPatient];
    deleteActiveWarning[0] = (WarningType*) malloc(sizeof(WarningType));
    deleteActiveWarning[0]->patientID = archivedPatient[0];
    deleteActiveWarning[0]->window = window;
    deleteActiveWarning[0]->actionType = 0;

    WarningType *archivedWarning[nbArchivedPatient];
    archiveWarning[0] = (WarningType*) malloc(sizeof(WarningType));
    archiveWarning[0]->patientID = archivedPatient[0];
    archiveWarning[0]->window = window;
    archiveWarning[0]->actionType = 1;

    Window_id *window_id_archived[nbArchivedPatient];
    window_id_active[0] = (Window_id*) malloc(sizeof(Window_id));
    window_id_active[0]->window = window;
    window_id_active[0]->id = archivedPatient[0];
    window_id_active[0]->session = createEmptySession();

    g_signal_connect(GTK_BUTTON(archived_patient_button[0]), "clicked", G_CALLBACK(launchWorkView), window_id_archived[0]);
    g_signal_connect(GTK_BUTTON(archived_archive_button[0]), "clicked", G_CALLBACK(launchPatientWarning), archivedWarning[0]);
    g_signal_connect(GTK_BUTTON(archived_delete_button[0]), "clicked", G_CALLBACK(launchPatientWarning), deleteArchivedWarning[0]);

    for(i=1; i < nbArchivedPatient; i++){
        patient_name = getNameFirstnamePatient(archivedPatient[i]);
        archived_patient_button[i] = gtk_button_new_with_label(patient_name);
        archived_archive_button[i] = gtk_button_new_from_icon_name("user-trash", GTK_ICON_SIZE_MENU);
        archived_delete_button[i] = gtk_button_new_from_icon_name("edit-delete", GTK_ICON_SIZE_MENU);

        gtk_grid_attach_next_to(GTK_GRID(grid_archived_patient), archived_patient_button[i], archived_patient_button[i-1],GTK_POS_BOTTOM, 5, 1);
        gtk_widget_set_hexpand(archived_patient_button[i], TRUE);
        gtk_widget_set_vexpand(archived_patient_button[i], FALSE);

        gtk_grid_attach_next_to(GTK_GRID(grid_archived_patient), archived_archive_button[i], archived_patient_button[i], GTK_POS_RIGHT, 1, 1);
        gtk_grid_attach_next_to(GTK_GRID(grid_archived_patient), archived_delete_button[i], archived_archive_button[i], GTK_POS_RIGHT, 1, 1);

        deleteActiveWarning[i] = (WarningType*) malloc(sizeof(WarningType));
        deleteActiveWarning[i]->patientID = archivedPatient[i];
        deleteActiveWarning[i]->window = window;
        deleteActiveWarning[i]->actionType = 0;
        archiveWarning[i] = (WarningType*) malloc(sizeof(WarningType));
        archiveWarning[i]->patientID = archivedPatient[i];
        archiveWarning[i]->window = window;
        archiveWarning[i]->actionType = 1;
        window_id_active[i] = (Window_id*) malloc(sizeof(Window_id));
        window_id_active[i]->window = window;
        window_id_active[i]->id = archivedPatient[i];
        window_id_active[i]->session = createEmptySession();
        g_signal_connect(GTK_BUTTON(archived_archive_button[i]), "clicked", G_CALLBACK(launchPatientWarning), archivedWarning[i]);
        g_signal_connect(GTK_BUTTON(archived_delete_button[i]), "clicked", G_CALLBACK(launchPatientWarning), deleteArchivedWarning[i]);
        g_signal_connect(GTK_BUTTON(archived_patient_button[i]), "clicked", G_CALLBACK(launchWorkView), window_id_archived[i]);
    }

    //Have to free window_id tabb (can't be done here)*/

}

/*!
 * \brief Allows to close the session window and open the patient window
 *
 * When the user click on the back button from a session window, this function closes
 * the current session window and open the patient window.
 *
 * \param[in] but Button that launches the view
 * \param[in] window Window dedicated to the patient view
*/
void launchHomeView(GtkWidget *but, GtkWidget *window){
    gtk_widget_destroy(window);
    setHomeWindow();
}

Session *createEmptySession(){
    Session *newSession = (Session*) malloc(sizeof(Session));
    newSession->sessionName = (char*) malloc(LG_MAX_INFO*sizeof(char));
    char *new_session_name = get_new_session_name();
    strcpy(newSession->sessionName, new_session_name);
    free_info_UI(new_session_name);
    newSession->observations = (char*) malloc(LG_MAX_OTHERS*sizeof(char));
    strcpy(newSession->observations, "Remarques");
    newSession->sessionDate.day = 1;
    newSession->sessionDate.month= 1;
    newSession->sessionDate.year= 2000;
    newSession->nextSessionDate.day = 1;
    newSession->nextSessionDate.month= 1;
    newSession->nextSessionDate.year= 2000;
    newSession->idSession = 3; // METTRE ENSUITE LE NOMBRE DE SESSIONS EXISTANTES + 1
    newSession->idFolder = 1; // METTRE ENSUITE L'ID DU DOSSIER LE PLUS RÉCENT POUR LE PATIENT CHOISI

    return newSession;
}