/*!
* \file home_views.c
* \brief File to initiate the homepage view (calendar, patient list, ...)
*/

#include <gtk/gtk.h>
#include "home_view.h"
#include "work_view.h"
#include "editor_views.h"
#include "../controller/display_helpers.h"

/*!
 * \brief Function that launch style.css to modify application style
 *
 * This function set necessary parameters to load css and use css file
 *
*/
static void load_css(){
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    const gchar *css_style_file = "../src/view/style.css";
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
 * \brief Initiate patient window which shows a list of the patient
 *
 * Focus, position, size, title and destroy callback are set.
 * \todo change the name of the window once the software name found
*/
GtkWidget *setHomeWindow(){

    gtk_init(NULL, NULL);
    load_css();

    GtkWidget *window = NULL;
    GdkPixbuf *symbolPixbuf = NULL;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_activate_focus(GTK_WINDOW(window));
    gtk_window_set_title(GTK_WINDOW(window), "Kinesia");

    symbolPixbuf = gdk_pixbuf_new_from_file("../media/graphic-assets/logo.jpg", NULL);
    gtk_window_set_icon(GTK_WINDOW(window), symbolPixbuf);

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
    char *patient_name;

    /* ACTIVE PATIENTS */
    int *activePatient = getActivePatientID();
    int nbActivePatient = getNbActivePatient();
    GtkWidget *active_patient_button[getNbActivePatient()];
    GtkWidget *archive_button[getNbActivePatient()];
    GtkWidget *active_delete_button[getNbActivePatient()];

    for(i=0; i < nbActivePatient; i++){
        patient_name = getNameFirstnamePatient(activePatient[i]);
        active_patient_button[i] = gtk_button_new_with_label(patient_name);
        archive_button[i] = gtk_button_new_from_icon_name("user-trash", GTK_ICON_SIZE_MENU);
        active_delete_button[i] = gtk_button_new_from_icon_name("edit-delete", GTK_ICON_SIZE_MENU);

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
        deleteActiveWarning[i]->patientID = activePatient[i];
        deleteActiveWarning[i]->window = window;
        deleteActiveWarning[i]->actionType = 0;

        WarningType *archiveWarning[nbActivePatient];
        archiveWarning[i] = (WarningType*) malloc(sizeof(WarningType));
        archiveWarning[i]->patientID = activePatient[i];
        archiveWarning[i]->window = window;
        archiveWarning[i]->actionType = 1;

        Window_id *window_id_active[nbActivePatient];
        window_id_active[i] = (Window_id*) malloc(sizeof(Window_id));
        window_id_active[i]->window = window;
        window_id_active[i]->patientID = activePatient[i];
        g_signal_connect(GTK_BUTTON(archive_button[i]), "clicked", G_CALLBACK(launchPatientWarning), archiveWarning[i]);
        g_signal_connect(GTK_BUTTON(active_delete_button[i]), "clicked", G_CALLBACK(launchPatientWarning), deleteActiveWarning[i]);
        g_signal_connect(GTK_BUTTON(active_patient_button[i]), "clicked", G_CALLBACK(launchWorkView), window_id_active[i]);
    }

    /* ARCHIVED PATIENTS */
    int *archivedPatient = getArchivedPatientID();
    int nbArchivedPatient = getNbArchivedPatient();
    GtkWidget *archived_patient_button[getNbArchivedPatient()];
    GtkWidget *unarchive_button[getNbArchivedPatient()];
    GtkWidget *archived_delete_button[getNbArchivedPatient()];

    for(i=0; i < nbArchivedPatient; i++){
        patient_name = getNameFirstnamePatient(archivedPatient[i]);
        archived_patient_button[i] = gtk_button_new_with_label(patient_name);
        unarchive_button[i] = gtk_button_new_from_icon_name("edit-undo", GTK_ICON_SIZE_MENU);
        archived_delete_button[i] = gtk_button_new_from_icon_name("edit-delete", GTK_ICON_SIZE_MENU);

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
        deleteArchivedWarning[i]->patientID = archivedPatient[i];
        deleteArchivedWarning[i]->window = window;
        deleteArchivedWarning[i]->actionType = 0;

        WarningType *unarchiveWarning[nbArchivedPatient];
        unarchiveWarning[i] = (WarningType*) malloc(sizeof(WarningType));
        unarchiveWarning[i]->patientID = archivedPatient[i];
        unarchiveWarning[i]->window = window;
        unarchiveWarning[i]->actionType = 1;

        Window_id *window_id_archived[nbArchivedPatient];
        window_id_archived[i] = (Window_id*) malloc(sizeof(Window_id));
        window_id_archived[i]->window = window;
        window_id_archived[i]->patientID = archivedPatient[i];
        g_signal_connect(GTK_BUTTON(unarchive_button[i]), "clicked", G_CALLBACK(launchPatientWarning), unarchiveWarning[i]);
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
 * \param[in] window Window dedicated to the patient view
*/
void launchHomeView(GtkWidget *but, GtkWidget *window){
    gtk_widget_destroy(window);
    setHomeWindow();
}

/*!
 * \brief Create and allocate an empty session
 *
 * When a new session is created, this function allocates it
 * and fills it with the current date
 *
 * \param[out] Empty session
*/
Session *createEmptySession(){
    Session *newSession = (Session*) malloc(sizeof(Session));
    newSession->sessionName = (char*) malloc(LG_MAX_INFO*sizeof(char));
    char *new_session_name = get_new_session_name();
    strcpy(newSession->sessionName, new_session_name);
    free_info_UI(new_session_name);
    newSession->observations = (char*) malloc(LG_MAX_OTHERS*sizeof(char));
    strcpy(newSession->observations, "Remarques");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    newSession->sessionDate.day = tm.tm_mday;
    newSession->sessionDate.month = tm.tm_mon + 1;
    newSession->sessionDate.year = tm.tm_year + 1900;

    newSession->nextSessionDate.day = tm.tm_mday;
    newSession->nextSessionDate.month = tm.tm_mon + 1;
    newSession->nextSessionDate.year = tm.tm_year + 1900;

    newSession->idSession = 0; // METTRE ENSUITE LE NOMBRE DE SESSIONS EXISTANTES + 1
    newSession->idFolder = 1; // METTRE ENSUITE L'ID DU DOSSIER LE PLUS RÉCENT POUR LE PATIENT CHOISI

    return newSession;
}