/*!
 * \file work_view.c
 * \brief File with functions to initiate the working view
 * (information and tools useful during a session)
*/

#include <gtk/gtk.h>
#include "work_view.h"
#include "home_view.h"
#include "editor_views.h"
#include "../controller/UI_to_struct.h"
#include "../controller/display_helpers.h"
#include "../controller/BDD_to_struct_folder.h"
#include "../controller/BDD_to_struct_session.h"
#include "../controller/struct_to_BDD_session.h"
#include "../model/session_manager.h"


/*!
 * \brief Initiate session window with some default parameters
 *
 * Focus, position, size, title and destroy callback are set.
 *
 * \param[in] fullScreen : to tell if the window have to be set fullScreen
 * \param[in] id_patient : ID of the patient file opened
 * \param[in] id_folder : ID of the current folder
*/
GtkWidget *setWorkWindow(int fullScreen, int id_patient, int id_folder){

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

    Window_id *window_id = (Window_id*) malloc(sizeof(Window_id));
    window_id->window = window;
    window_id->patientID = id_patient;
    window_id->folderID = id_folder;
    setWorkEnvironment(window_id);

    gtk_widget_show_all(window);
    gtk_main();

    return window;
}

/*!
* \brief Split the Work window in three spaces and fill them
 *
 * The three spaces are:
 * on the left side the patient,
 * at the top right the current folder,
 * and at the bottom right the list of all the sessions.
 *
 * The three boxes are filled by external functions.
 *
 * \param[in] window_id  : structure containing info to launch the view
*/
void setWorkEnvironment(Window_id *window_id){

    /* GET PATIENT STRUCTURE FROM BDD */

    WorkWindow * workwindow = malloc(sizeof(WorkWindow));
    if(workwindow == NULL) printf("Allocation error on workwindow.\n");
    workwindow->patient = NULL;
    workwindow->window = NULL;
    workwindow->folder = NULL;
    workwindow->sessionList = NULL;

    /*Patient *patient = getPatient(window_id->patientID);*/
    workwindow->patient = getPatient(window_id->patientID);

    /*GtkWidget *window = window_id->window;*/
    workwindow->window = window_id->window;

    GtkWidget *grid = NULL;
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(workwindow->window), grid);

    /* Set the 3 main spaces of the window */
    GtkWidget *boxPart[3];

    boxPart[0] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_grid_attach(GTK_GRID(grid), boxPart[0], GTK_ALIGN_START, GTK_ALIGN_START, 1, 6);
    gtk_widget_set_hexpand(boxPart[0], TRUE);
    gtk_widget_set_vexpand(boxPart[0], TRUE);

    boxPart[1] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    setStartMargin(boxPart[1]);
    gtk_grid_attach_next_to(GTK_GRID(grid), boxPart[1],boxPart[0], GTK_POS_RIGHT, 4, 5);
    gtk_widget_set_hexpand(boxPart[1], TRUE);
    gtk_widget_set_vexpand(boxPart[1], FALSE);

    boxPart[2] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    setStartMargin(boxPart[2]);
    setTopMargin(boxPart[2]);
    gtk_grid_attach_next_to(GTK_GRID(grid), boxPart[2],boxPart[1], GTK_POS_BOTTOM, 4, 1);
    gtk_widget_set_hexpand(boxPart[2], TRUE);
    gtk_widget_set_vexpand(boxPart[2], TRUE);

    /* Fill in the 3 spaces */
    fillPatientBox(boxPart[0], boxPart[1], boxPart[2], workwindow, window_id->folderID);
    free(window_id);
}

/*!
* \brief Fill the Patient box
 *
 * The box is made up of the main infos (anamnesis) and a photo from the Patient.
 * At the top a button to go back to the Home view is set up.
 * At the bottom a folder chooser is displayed.
 *
 * \param[in] window : Current window to enable refresh
 * \param[in] patientBox : patient box that has to be filled
 * \param[in] folderBox : folder box that has to be filled
 * \param[in] sessionBox : session box that has to be filled
 * \param[in] patient : current patient
 * \param[in] id_folder : the current folder to display
*/
void fillPatientBox(GtkWidget *patientBox, GtkWidget *folderBox, GtkWidget *sessionBox, WorkWindow *workwindow, int id_folder){

    /* CREATE STRUCT TO PASS ARGUMENTS TO DIALOG BOX */
    Patient_window *patient_window = (Patient_window*) malloc(sizeof(Patient_window));
    patient_window->patient = workwindow->patient;
    patient_window->window = workwindow->window;
    patient_window->origin = 1;


    /* DECLARE VARIABLES */
    GtkWidget *frame_info = NULL;
    GtkWidget *frame_etat_civil = NULL;
    GtkWidget *frame_medical_info = NULL;
    GtkWidget *frame_other_info = NULL;

    GtkWidget *grid_left_section = NULL;
    GtkWidget *grid_info = NULL;
    GtkWidget *grid_etat_civil = NULL;
    GtkWidget *grid_medical_info = NULL;
    GtkWidget *grid_other_info = NULL;

    GtkWidget *back_button = NULL;
    GtkWidget *edit_button = NULL;
    GtkWidget *patient_photo = NULL;
    GdkPixbuf *patient_photo_pixbuf = NULL;
    GtkWidget *patient_name = NULL;
    GtkWidget *patient_birth = NULL;
    GtkWidget *patient_job = NULL;
    GtkWidget *patient_height_weight = NULL;
    GtkWidget *patient_first_consultation = NULL;
    GtkWidget *patient_other_info = NULL;
    GtkWidget *patient_mail_link = NULL;

    char *patient_name_char = get_name_UI(workwindow->patient);
    char *patient_birth_char = get_age_and_birthdate(workwindow->patient);
    char *patient_height_weight_char = get_height_weight_UI(workwindow->patient);
    char *patient_first_consultation_char = get_first_consultation_UI(workwindow->patient);
    char *contact_link = (char*) malloc(sizeof(char)*(strlen("mailto:")+strlen(workwindow->patient->mail_address)));

    /* ASSIGN VARIABLES */
    frame_info = gtk_frame_new("Informations patient");
    frame_etat_civil = gtk_frame_new("Etat civil");
    frame_medical_info = gtk_frame_new("Informations médicales");
    frame_other_info = gtk_frame_new("Informations importantes");

    grid_left_section = gtk_grid_new();
    grid_info = gtk_grid_new();
    grid_etat_civil = gtk_grid_new();
    grid_medical_info = gtk_grid_new();
    grid_other_info = gtk_grid_new();

    back_button = gtk_button_new_with_label("< Revenir à la liste");
    edit_button = gtk_button_new_from_icon_name("text-editor", GTK_ICON_SIZE_MENU);
    patient_photo_pixbuf = gdk_pixbuf_new_from_file(getProfilePhotoPath((int) workwindow->patient->id), NULL);
    patient_photo_pixbuf = gdk_pixbuf_scale_simple(patient_photo_pixbuf, 145, 193, GDK_INTERP_BILINEAR);
    patient_photo = gtk_image_new_from_pixbuf(GDK_PIXBUF(patient_photo_pixbuf));
    patient_name = gtk_label_new(patient_name_char);
    free_info_UI(patient_name_char);
    patient_birth = gtk_label_new(patient_birth_char);
    free_info_UI(patient_birth_char);
    patient_job = gtk_label_new(workwindow->patient->job);
    patient_height_weight = gtk_label_new(patient_height_weight_char);
    free_info_UI(patient_height_weight_char);
    patient_first_consultation = gtk_label_new(patient_first_consultation_char);
    free_info_UI(patient_first_consultation_char);
    patient_other_info = gtk_label_new(workwindow->patient->global_pathologies);
    strcpy(contact_link, "mailto:");
    strcat(contact_link, workwindow->patient->mail_address);
    patient_mail_link = gtk_link_button_new_with_label(contact_link, "Contacter");



    /************ LEFT PART : PATIENT INFORMATION BOX  ************/
    gtk_grid_set_row_spacing(GTK_GRID(grid_left_section), 5);
    gtk_box_pack_start(GTK_BOX(patientBox), grid_left_section, TRUE, TRUE, 0);


    /* BUTTON "REVENIR A LA LISTE PATIENT" */
    gtk_grid_attach(GTK_GRID(grid_left_section), back_button, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(back_button, FALSE);
    gtk_widget_set_vexpand(back_button, FALSE);
    gtk_widget_set_halign(back_button, GTK_ALIGN_START);
    g_signal_connect(GTK_BUTTON(back_button), "clicked", G_CALLBACK(launchHomeView), workwindow);



    /* FRAME WHICH CONTAINS PATIENT INFORMATION */
    gtk_frame_set_label_align(GTK_FRAME(frame_info), (float)0.5, (float)0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_left_section), frame_info, back_button, GTK_POS_BOTTOM, 1, 3);
    gtk_widget_set_hexpand(frame_info, TRUE);
    gtk_widget_set_vexpand(frame_info, TRUE);

    gtk_container_add(GTK_CONTAINER(frame_info), grid_info);
    gtk_container_set_border_width(GTK_CONTAINER(grid_info), 0);

    /* Button to edit information */
    g_signal_connect(GTK_BUTTON(edit_button), "clicked", G_CALLBACK(launchPatientEditor), patient_window);
    gtk_grid_attach(GTK_GRID(grid_info), edit_button, GTK_ALIGN_END, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(edit_button, TRUE);
    gtk_widget_set_vexpand(edit_button, FALSE);
    gtk_widget_set_halign(edit_button, GTK_ALIGN_END);
    gtk_widget_set_tooltip_text(edit_button, "Modifier la fiche");

    /* Include the picture of the patient */
    gtk_grid_attach_next_to(GTK_GRID(grid_info), patient_photo, edit_button, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(patient_photo, FALSE);
    gtk_widget_set_vexpand(patient_photo, FALSE);
    gtk_widget_set_halign(patient_photo, GTK_ALIGN_CENTER);

    /* Manage the frame which contains identity informations and its grid */
    gtk_frame_set_label_align(GTK_FRAME(frame_etat_civil), 0, (float)0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_info), frame_etat_civil, patient_photo, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(frame_etat_civil, TRUE);
    gtk_widget_set_vexpand(frame_etat_civil, FALSE);

    gtk_container_add(GTK_CONTAINER(frame_etat_civil), grid_etat_civil);


    /* Section which fills the information grid */
    // Name
    gtk_grid_attach(GTK_GRID(grid_etat_civil), patient_name, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_label_set_use_markup(GTK_LABEL(patient_name), TRUE);
    gtk_widget_set_hexpand(patient_name, TRUE);
    gtk_widget_set_vexpand(patient_name, FALSE);
    gtk_widget_set_margin_top(patient_name, 5);
    gtk_widget_set_margin_bottom(patient_name, 5);
    gtk_widget_set_halign(patient_name, GTK_ALIGN_CENTER);

    // Birthdate
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), patient_birth, patient_name, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(patient_birth, TRUE);
    gtk_widget_set_vexpand(patient_birth, FALSE);
    gtk_widget_set_halign(patient_birth, GTK_ALIGN_CENTER);

    // Job
    gtk_label_set_use_markup(GTK_LABEL(patient_job), TRUE);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), patient_job, patient_birth, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(patient_job, TRUE);
    gtk_widget_set_vexpand(patient_job, FALSE);
    gtk_widget_set_margin_bottom(patient_job, 5);
    gtk_widget_set_halign(patient_job, GTK_ALIGN_CENTER);

    /* Manage the frame which contains medical informations and its grid */
    gtk_frame_set_label_align(GTK_FRAME(frame_medical_info), 0, (float)0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_info), frame_medical_info, frame_etat_civil, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(frame_medical_info, TRUE);
    gtk_widget_set_vexpand(frame_medical_info, FALSE);

    gtk_container_add(GTK_CONTAINER(frame_medical_info), grid_medical_info);

    /* Section which fills the medical grid */
    // Height and weight
    gtk_grid_attach(GTK_GRID(grid_medical_info), patient_height_weight, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(patient_height_weight, TRUE);
    gtk_widget_set_vexpand(patient_height_weight, FALSE);
    gtk_widget_set_margin_top(patient_height_weight, 5);
    gtk_widget_set_halign(patient_height_weight, GTK_ALIGN_CENTER);

    // First consultation
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), patient_first_consultation, patient_height_weight, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(patient_first_consultation, TRUE);
    gtk_widget_set_vexpand(patient_first_consultation, FALSE);
    gtk_widget_set_margin_bottom(patient_first_consultation, 5);
    gtk_widget_set_halign(patient_first_consultation, GTK_ALIGN_CENTER);

    /* Manage the frame which contains other informations */
    gtk_frame_set_label_align(GTK_FRAME(frame_other_info), 0, (float)0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_info), frame_other_info, frame_medical_info, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(frame_other_info, TRUE);
    gtk_widget_set_vexpand(frame_other_info, FALSE);

    /* Section which fills other information */
    gtk_container_add(GTK_CONTAINER(frame_other_info), grid_other_info);
    gtk_widget_set_hexpand(grid_other_info, TRUE);
    gtk_grid_attach(GTK_GRID(grid_other_info), patient_other_info, GTK_ALIGN_CENTER, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(patient_other_info, TRUE);
    gtk_widget_set_margin_top(patient_other_info, 5);
    gtk_widget_set_margin_bottom(patient_other_info, 5);
    if(strcmp(workwindow->patient->mail_address, "") != 0) gtk_grid_attach_next_to(GTK_GRID(grid_other_info), patient_mail_link, patient_other_info, GTK_POS_BOTTOM, 1, 1);



    /* SECTION WHICH CONTAINS THE PATIENT FOLDERS */

    /* DECLARE VARIABLES */
    GtkWidget *folder_box = NULL;
    folder_box = gtk_scrolled_window_new(NULL, NULL);
    gtk_grid_attach_next_to(GTK_GRID(grid_left_section), folder_box, frame_info, GTK_POS_BOTTOM, 3, 1);
    gtk_widget_set_hexpand(folder_box, TRUE);
    gtk_widget_set_vexpand(folder_box, TRUE);

    GtkWidget *folder_grid = NULL;
    folder_grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(folder_box), folder_grid);

    int *folderIDTab = getIdFolder((int) workwindow->patient->id);
    int folder_cursor;

    int nb_folders = getNbFolder((int) workwindow->patient->id);
    GtkWidget *folder_button[nb_folders];
    char *name_folder[nb_folders];

    /* ASSIGN VARIABLES */
    for(folder_cursor = 0; folder_cursor < nb_folders; folder_cursor++){

        name_folder[folder_cursor] = getNameFolder(folderIDTab[folder_cursor]);
        folder_button[folder_cursor] = gtk_button_new_with_label(name_folder[folder_cursor]);
        free(name_folder[folder_cursor]);
    }

    /* MANAGE TO DISPLAY BUTTONS */
    if(nb_folders > 0){
        gtk_grid_attach(GTK_GRID(folder_grid), folder_button[nb_folders - 1], GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
        gtk_widget_set_hexpand(folder_button[nb_folders - 1], TRUE);
        Window_id *window_id[nb_folders];
        window_id[nb_folders - 1] = (Window_id*) malloc(sizeof(Window_id));
        window_id[nb_folders - 1]->window = workwindow->window;
        window_id[nb_folders - 1]->patientID = (int) workwindow->patient->id;
        window_id[nb_folders - 1]->folderID = folderIDTab[nb_folders - 1];
        g_signal_connect(GTK_BUTTON(folder_button[nb_folders - 1]), "clicked", G_CALLBACK(launchWorkView), window_id[nb_folders - 1]);

        for(folder_cursor = nb_folders - 2; folder_cursor >= 0; folder_cursor--){
            gtk_grid_attach_next_to(GTK_GRID(folder_grid), folder_button[folder_cursor], folder_button[folder_cursor+1], GTK_POS_BOTTOM, 1, 1);
            gtk_widget_set_hexpand(folder_button[folder_cursor], TRUE);
            window_id[folder_cursor] = (Window_id*) malloc(sizeof(Window_id));
            window_id[folder_cursor]->window = workwindow->window;
            window_id[folder_cursor]->patientID = (int) workwindow->patient->id;
            window_id[folder_cursor]->folderID = folderIDTab[folder_cursor];
            g_signal_connect(GTK_BUTTON(folder_button[folder_cursor]), "clicked", G_CALLBACK(launchWorkView), window_id[folder_cursor]);
        }
    }

    if(nb_folders>0 && id_folder == 0){
        fillFolderBox(folderBox, sessionBox, folderIDTab[nb_folders - 1], workwindow);
    }
    else if(nb_folders>0 && id_folder != 0){
        fillFolderBox(folderBox, sessionBox, id_folder, workwindow);
    }
    else{
        fillFolderBox(folderBox, sessionBox, 0, workwindow);
    }


    free(contact_link);
}

/*!
* \brief Fill the Folder box
 *
 * The box is made up of the current Folder infos.
 * A button is displayed to see the attached media related to this Folder.
 * Folders can also be created, modified or deleted in this box.
 *
 * \param[in] window : Current window to enable refresh
 * \param[in] box : folder box that has to be filled
 * \param[in] sessionBox : session box that has to be filled
 * \param[in] activeFolder : the folder that has to be displayed
 * \param[in] patient : current patient
*/
void fillFolderBox(GtkWidget *box, GtkWidget *sessionBox, int activeFolder, WorkWindow * workwindow){

    /* GETTING FOLDER (SPECIAL VIEW IF NO FOLDER) */
    /*Folder *folder = NULL;*/
    if(activeFolder != 0){
        workwindow->folder = getFolder(activeFolder);
    }
    else{
        GtkWidget *frame = gtk_frame_new("");
        GtkWidget *label = gtk_label_new("Créer un premier dossier");
        GtkWidget *grid = gtk_grid_new();
        GtkWidget *button = gtk_button_new_from_icon_name("list-add", GTK_ICON_SIZE_MENU);
        gtk_container_add(GTK_CONTAINER(box), frame);
        gtk_container_add(GTK_CONTAINER(frame), grid);
        gtk_grid_attach(GTK_GRID(grid), label, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
        gtk_grid_attach_next_to(GTK_GRID(grid), button, label, GTK_POS_BOTTOM, 1, 1);
        gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
        gtk_container_set_border_width(GTK_CONTAINER(frame), 5);
        gtk_widget_set_hexpand(frame, TRUE);
        gtk_widget_set_hexpand(label, TRUE);
        gtk_widget_set_hexpand(button, TRUE);
        gtk_widget_set_tooltip_text(button, "Ajouter le premier dossier");

        IdPatientCallback *idPatient = (IdPatientCallback*) malloc(sizeof(IdPatientCallback));
        idPatient->idPatient = (int) workwindow->patient->id;
        idPatient->window = workwindow->window;
        g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(launchNewFolderEditor), idPatient);

        fillSessionBox(sessionBox, NULL, workwindow, 0);
        return ;
    }

    /* DECLARE VARIABLES */
    GtkWidget *frame_folder = NULL;

    GtkWidget *grid_folder = NULL;

    GtkWidget *hbox_folder = NULL;
    GtkWidget *hbox_treatment = NULL;
    GtkWidget *hbox_pathology = NULL;
    GtkWidget *vbox_infos = NULL;
    GtkWidget *vbox_infos_content = NULL;
    GtkWidget *hbox_attachments = NULL;
    GtkWidget *hbox_edit_folder = NULL;

    GtkWidget *folder_title = NULL;
    GtkWidget *folder_start_treatment = NULL;
    GtkWidget *folder_date = NULL;
    GtkWidget *folder_pathology = NULL;
    GtkWidget *folder_pathology_name = NULL;
    GtkWidget *folder_infos = NULL;
    GtkWidget *folder_infos_content = NULL;
    GtkWidget *attachments_label = NULL;
    GtkWidget *attachments_count = NULL;

    GtkWidget *attachments_button = NULL;
    GtkWidget *new_button = NULL;
    GtkWidget *edit_folder_button = NULL;
    GtkWidget *delete_folder_button = NULL;

    /* ASSIGN VARIABLES */
    frame_folder = gtk_frame_new("Dossier");

    grid_folder = gtk_grid_new();

    hbox_folder = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    hbox_treatment = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    hbox_pathology = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    vbox_infos = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    vbox_infos_content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    hbox_attachments = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    hbox_edit_folder = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    char *formatted_folder_title_UI = get_formatted_folder_title_UI(workwindow->folder);
    folder_title = gtk_label_new(formatted_folder_title_UI);
    free_info_UI(formatted_folder_title_UI);
    char *start_of_treatment = get_date_UI(&workwindow->folder->startOfTreatment);
    folder_start_treatment = gtk_label_new("Début de traitement: ");
    folder_date = gtk_label_new(start_of_treatment);
    free_info_UI(start_of_treatment);
    folder_pathology = gtk_label_new("Pathologie: ");
    folder_pathology_name = gtk_label_new(workwindow->folder->pathology);
    folder_infos = gtk_label_new("<u>Autres informations</u> : ");
    folder_infos_content = gtk_label_new(workwindow->folder->details);
    char *indicator = get_indicator_files_UI((int) workwindow->patient->id, activeFolder);
    attachments_label = gtk_label_new("Pièces jointes:    ");
    attachments_count = gtk_label_new(indicator);
    free_info_UI(indicator);

    attachments_button = gtk_button_new_from_icon_name("folder-documents", GTK_ICON_SIZE_MENU);
    new_button = gtk_button_new_from_icon_name("list-add", GTK_ICON_SIZE_MENU);
    edit_folder_button = gtk_button_new_from_icon_name("text-editor", GTK_ICON_SIZE_MENU);
    delete_folder_button = gtk_button_new_from_icon_name("edit-delete", GTK_ICON_SIZE_MENU);


    /* FRAME WHICH HOLDS OTHER WIDGETS */
    gtk_frame_set_label_align(GTK_FRAME(frame_folder), (float)0.5, (float) 0.5);
    gtk_box_pack_start(GTK_BOX(box), frame_folder, TRUE, TRUE, 0);
    gtk_widget_set_hexpand(frame_folder, TRUE);
    gtk_widget_set_vexpand(frame_folder, TRUE);

    /* GRID USED TO FILL THE FOLDER FRAME */
    gtk_container_add(GTK_CONTAINER(frame_folder), grid_folder);
    gtk_container_set_border_width(GTK_CONTAINER(grid_folder), 0);


    /* FOLDER TITLE */
    // Box
    gtk_grid_attach(GTK_GRID(grid_folder), hbox_folder, GTK_ALIGN_CENTER, GTK_ALIGN_START, 3, 1);
    gtk_widget_set_hexpand(hbox_folder, TRUE);
    gtk_widget_set_vexpand(hbox_folder, FALSE);
    gtk_widget_set_halign(hbox_folder, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(hbox_folder, 10);
    gtk_widget_set_margin_bottom(hbox_folder, 40);

    // Label
    gtk_label_set_use_markup(GTK_LABEL(folder_title), TRUE);
    gtk_widget_set_halign(folder_title, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(hbox_folder), folder_title, FALSE, FALSE, 0);

    /* START OF TREATMENT */
    // Box
    gtk_grid_attach_next_to(GTK_GRID(grid_folder), hbox_treatment, hbox_folder, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(hbox_treatment, TRUE);
    gtk_widget_set_vexpand(hbox_treatment, FALSE);
    gtk_widget_set_halign(hbox_treatment, GTK_ALIGN_START);
    setStartMargin(hbox_treatment);

    // Label
    gtk_box_pack_start(GTK_BOX(hbox_treatment), folder_start_treatment, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_treatment), folder_date, FALSE, FALSE, 0);

    /* PATHOLOGIE */
    // Box
    gtk_grid_attach_next_to(GTK_GRID(grid_folder), hbox_pathology, hbox_treatment, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_hexpand(hbox_pathology, TRUE);
    gtk_widget_set_vexpand(hbox_pathology, FALSE);
    gtk_widget_set_halign(hbox_pathology, GTK_ALIGN_START);

    // Label
    gtk_box_pack_start(GTK_BOX(hbox_pathology), folder_pathology, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_pathology), folder_pathology_name, FALSE, FALSE, 0);

    /* OTHER INFORMATION */
    // Boxes
    gtk_grid_attach_next_to(GTK_GRID(grid_folder), vbox_infos, hbox_treatment, GTK_POS_BOTTOM, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid_folder), vbox_infos_content, vbox_infos, GTK_POS_BOTTOM, 1, 1);

    gtk_widget_set_hexpand(vbox_infos, FALSE);
    gtk_widget_set_vexpand(vbox_infos, FALSE);
    gtk_widget_set_halign(vbox_infos, GTK_ALIGN_START);
    gtk_widget_set_hexpand(vbox_infos_content, FALSE);
    gtk_widget_set_vexpand(vbox_infos_content, FALSE);
    gtk_widget_set_halign(vbox_infos_content, GTK_ALIGN_START);
    gtk_widget_set_margin_top(vbox_infos, 20);
    gtk_widget_set_margin_top(vbox_infos_content, 5);
    setStartMargin(vbox_infos);
    setStartMargin(vbox_infos_content);

    // Labels
    gtk_label_set_use_markup(GTK_LABEL(folder_infos), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox_infos), folder_infos, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_infos_content), folder_infos_content, FALSE, FALSE, 0);


    /* ATTACHMENTS */
    // Box
    gtk_grid_attach_next_to(GTK_GRID(grid_folder), hbox_attachments, hbox_pathology, GTK_POS_BOTTOM,1,2);

    gtk_widget_set_hexpand(hbox_attachments, FALSE);
    gtk_widget_set_vexpand(hbox_attachments, FALSE);
    gtk_widget_set_halign(hbox_attachments, GTK_ALIGN_START);
    gtk_widget_set_margin_top(hbox_attachments, 20);

    // Label
    gtk_box_pack_start(GTK_BOX(hbox_attachments), attachments_label, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(hbox_attachments), attachments_count, FALSE, FALSE, 0);

    // Button
    gtk_box_pack_start(GTK_BOX(hbox_attachments), attachments_button, FALSE, FALSE, 0);
    gtk_widget_set_tooltip_text(attachments_button, "Pièces-jointes");
    gtk_widget_set_hexpand(attachments_button, FALSE);
    gtk_widget_set_vexpand(attachments_button, FALSE);

    MediaType *attachment_properties = (MediaType*) malloc(sizeof(Patient)+sizeof(char)*10+sizeof(int));
    attachment_properties->patientID = (int) workwindow->patient->id;
    attachment_properties->folderID = (int) workwindow->folder->idFolder;
    attachment_properties->mediaType = 1;
    attachment_properties->counterLabel = attachments_count;
    g_signal_connect(GTK_BUTTON(attachments_button), "clicked", G_CALLBACK(launchAttachmentListViewer), attachment_properties);


    /* BOX WITH FOLDER EDITION BUTTONS */
    gtk_grid_attach_next_to(GTK_GRID(grid_folder), hbox_edit_folder, hbox_folder, GTK_POS_RIGHT, 1, 1);

    gtk_widget_set_hexpand(hbox_edit_folder, FALSE);
    gtk_widget_set_vexpand(hbox_edit_folder, FALSE);
    gtk_widget_set_halign(hbox_edit_folder, GTK_ALIGN_END);
    gtk_widget_set_valign(hbox_edit_folder, GTK_ALIGN_END);

    /* NEW FOLDER BUTTON */
    gtk_box_pack_start(GTK_BOX(hbox_edit_folder), new_button, FALSE, FALSE, 0);
    gtk_widget_set_tooltip_text(new_button, "Créer un nouveau dossier");

    gtk_widget_set_hexpand(new_button, FALSE);
    gtk_widget_set_vexpand(new_button, FALSE);
    gtk_widget_set_margin_end(new_button, 17);

    IdPatientCallback *idPatient = (IdPatientCallback*) malloc(sizeof(IdPatientCallback));
    idPatient->idPatient = (int) workwindow->patient->id;
    idPatient->window = workwindow->window;
    g_signal_connect(GTK_BUTTON(new_button), "clicked", G_CALLBACK(launchNewFolderEditor), idPatient);


    /* EDIT FOLDER BUTTON */
    gtk_box_pack_start(GTK_BOX(hbox_edit_folder), edit_folder_button, FALSE, FALSE, 0);
    gtk_widget_set_tooltip_text(edit_folder_button, "Modifier le dossier");
    gtk_widget_set_hexpand(edit_folder_button, FALSE);
    gtk_widget_set_vexpand(edit_folder_button, FALSE);

    FolderEditorStruct *foldEditStruct = (FolderEditorStruct*) malloc(sizeof(FolderEditorStruct));
    foldEditStruct->folder = workwindow->folder;
    foldEditStruct->edit_new = 1;
    foldEditStruct->window = workwindow->window;
    g_signal_connect(GTK_BUTTON(edit_folder_button), "clicked", G_CALLBACK(launchFolderEditor), foldEditStruct);


    /* DELETE FOLDER BUTTON */
    gtk_box_pack_start(GTK_BOX(hbox_edit_folder), delete_folder_button, FALSE, FALSE, 0);
    gtk_widget_set_tooltip_text(delete_folder_button, "Supprimer le dossier");
    gtk_widget_set_hexpand(delete_folder_button, FALSE);
    gtk_widget_set_vexpand(delete_folder_button, FALSE);

    DeleteElements *folderDelete = (DeleteElements *) malloc(sizeof(DeleteElements));
    folderDelete->window = workwindow->window;
    folderDelete->isFolder = 1;
    folderDelete->folderID = activeFolder;
    folderDelete->notebook = NULL;
    folderDelete->patientID = (int) workwindow->patient->id;
    g_signal_connect(GTK_BUTTON(delete_folder_button), "clicked", G_CALLBACK(launchDeleteElement), folderDelete);


    /* CALL FUNCTION WHICH FILLS SESSION PART */
    fillSessionBox(sessionBox, attachments_count, workwindow, activeFolder);

}

/*!
* \brief Fill the Session box
 *
 * The box is made up of a list of the passed Sessions
 * and the current one related to the current Folder.
 * This box allows the user to edit, create and delete session.
 * Attachments can also be added in a session
 *
 * \param[in] window : Current window to enable refresh
 * \param[in] box: session box that has to be filled
 * \param[in] attachmentCounterLabel : label to increase number of attachments
 * \param[in] patient : current patient
 * param[in] folderID : current folder
*/
void fillSessionBox(GtkWidget *box, GtkWidget *attachmentCounterLabel, WorkWindow * workwindow, int folderID){

    if(folderID == 0){
        GtkWidget *label = gtk_label_new("Ce patient n'a pas de dossier associé");
        GtkWidget *frame = gtk_frame_new("");
        gtk_container_add(GTK_CONTAINER(box), frame);
        gtk_container_add(GTK_CONTAINER(frame), label);
        gtk_widget_set_hexpand(frame, TRUE);
        gtk_widget_set_vexpand(frame, TRUE);
        return ;
    }

    int nb_session = getNbSession(folderID);
    if(nb_session == 0){
        GtkWidget *label = gtk_label_new("Créer une première séance pour ce dossier :");
        GtkWidget *frame = gtk_frame_new("Séances");
        GtkWidget *grid = gtk_grid_new();
        GtkWidget *button = gtk_button_new_from_icon_name("list-add", GTK_ICON_SIZE_MENU);
        gtk_widget_set_tooltip_text(button, "Ajouter une première séance");
        gtk_container_add(GTK_CONTAINER(box), frame);
        gtk_container_add(GTK_CONTAINER(frame), grid);
        gtk_grid_attach(GTK_GRID(grid), label, GTK_ALIGN_START, GTK_ALIGN_START, 15, 1);
        gtk_widget_set_margin_top(label, 15);
        gtk_grid_attach_next_to(GTK_GRID(grid), button, label, GTK_POS_BOTTOM, 15, 1);

        /* CONNECT BUTTON TO CREATE FIRST SESSION */
        AddFirstSessionStruct *firstSession = (AddFirstSessionStruct*) malloc(sizeof(AddFirstSessionStruct));
        firstSession->window = workwindow->window;
        firstSession->patientID = (int) workwindow->patient->id;
        firstSession->folderID = folderID;
        g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(addFirstSessionUI), firstSession);

        /* DISPLAY THE DATE/HOUR OF FIRST APPOINTMENT */
        Session *session0 = getSession0(folderID);
        GtkWidget *meeting_label1 = gtk_label_new("Le premier rendez-vous est programmé le ");
        GtkWidget *meeting_label2 = gtk_label_new(" à ");
        GtkWidget *state_label = gtk_label_new("");
        GtkWidget *date_entry = gtk_entry_new();
        GtkWidget *hour_entry = gtk_entry_new();
        GtkWidget *save_button = gtk_button_new_from_icon_name("document-save", GTK_ICON_SIZE_MENU);
        char *date = get_date_UI(&session0->nextSessionDate);
        gtk_entry_set_text(GTK_ENTRY(date_entry), date);
        free_info_UI(date);
        gtk_entry_set_text(GTK_ENTRY(hour_entry), session0->nextSessionHour);
        gtk_grid_attach_next_to(GTK_GRID(grid), meeting_label1, button, GTK_POS_BOTTOM, 1, 1);
        gtk_grid_attach_next_to(GTK_GRID(grid), date_entry, meeting_label1, GTK_POS_RIGHT, 1, 1);
        gtk_grid_attach_next_to(GTK_GRID(grid), meeting_label2, date_entry, GTK_POS_RIGHT, 1, 1);
        gtk_grid_attach_next_to(GTK_GRID(grid), hour_entry, meeting_label2, GTK_POS_RIGHT, 1, 1);
        gtk_grid_attach_next_to(GTK_GRID(grid), state_label, hour_entry, GTK_POS_RIGHT, 1, 1);
        gtk_grid_attach_next_to(GTK_GRID(grid), save_button, state_label, GTK_POS_RIGHT, 10, 1);

        firstSessionHoursStruct *fSHS = (firstSessionHoursStruct*) malloc(sizeof(firstSessionHoursStruct));
        fSHS->session = session0;
        fSHS->stateLabel = state_label;
        fSHS->dateEntry = date_entry;
        fSHS->hourEntry = hour_entry;
        g_signal_connect(date_entry, "activate", G_CALLBACK(modifyFirstSessionHours), fSHS);
        g_signal_connect(hour_entry, "activate", G_CALLBACK(modifyFirstSessionHours), fSHS);
        g_signal_connect(save_button, "clicked", G_CALLBACK(modifyFirstSessionHours), fSHS);

        /* SET VISUAL ATTRIBUTES */
        gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
        gtk_container_set_border_width(GTK_CONTAINER(frame), 5);
        gtk_widget_set_hexpand(frame, TRUE);
        gtk_widget_set_hexpand(label, TRUE);
        gtk_widget_set_hexpand(button, TRUE);

        gtk_widget_set_vexpand(box, TRUE);
        gtk_widget_set_vexpand(grid, TRUE);

        gtk_widget_set_halign(meeting_label1, GTK_ALIGN_START);
        gtk_widget_set_halign(date_entry, GTK_ALIGN_START);
        gtk_widget_set_halign(meeting_label2, GTK_ALIGN_START);
        gtk_widget_set_halign(hour_entry, GTK_ALIGN_START);
        gtk_widget_set_halign(save_button, GTK_ALIGN_END);
        gtk_widget_set_hexpand(meeting_label1, FALSE);
        gtk_widget_set_hexpand(date_entry, FALSE);
        gtk_widget_set_hexpand(meeting_label2, FALSE);
        gtk_widget_set_hexpand(hour_entry, FALSE);
        gtk_widget_set_hexpand(save_button, FALSE);

        gtk_frame_set_label_align(GTK_FRAME(frame), (float) 0.5, (float) 0.5);

    }

    else {
        /* DECLARE VARIABLES */
        int session_cursor;

        GtkWidget *grid_session_section = NULL;
        GtkWidget *grid_add_session[nb_session];

        GtkWidget *frame_session_note[nb_session];

        GtkWidget *notebook;
        GtkWidget *session_title_new[nb_session];
        GtkWidget *entry_title_new[nb_session];
        GtkWidget *session_date_new[nb_session];
        GtkWidget *entry_date_new[nb_session];
        GtkWidget *calendar_session_date_button[nb_session];
        GtkWidget *save_button[nb_session];
        GtkWidget *delete_button[nb_session];
        GtkWidget *new_session_button[nb_session];
        GtkWidget *session_next_meeting[nb_session];
        GtkWidget *entry_next_meeting[nb_session];
        GtkWidget *calendar_next_meeting_button[nb_session];
        GtkWidget *session_next_meeting_hour[nb_session];
        GtkWidget *entry_next_meeting_hour[nb_session];
        GtkWidget *space[nb_session];
        GtkWidget *session_attach_button[nb_session];
        GtkWidget *text_session_note[nb_session];
        GtkTextBuffer *session_buffer[nb_session];
        GtkTextIter end[nb_session];
        GtkWidget *text_box[nb_session];


        char *session_date_char[nb_session];
        char *next_session_date_char[nb_session];

        SessionList *session_list = NULL;
        SessionEntries *saveSession[nb_session];
        DeleteElements *sessionDelete[nb_session];
        MediaType *mediaChooser[nb_session];

        /* ASSIGN VARIABLES */
        notebook = gtk_notebook_new();
        gtk_notebook_set_scrollable(GTK_NOTEBOOK(notebook), TRUE);
        grid_session_section = gtk_grid_new();

        session_list = getSessionList(folderID);
        setOnFirst(session_list);
        for (session_cursor = 0; session_cursor < nb_session; session_cursor++) {
            grid_add_session[session_cursor] = gtk_grid_new();

            frame_session_note[session_cursor] = gtk_frame_new("Observations");

            session_title_new[session_cursor] = gtk_label_new("Titre :");
            entry_title_new[session_cursor] = gtk_entry_new();
            gtk_entry_set_text(GTK_ENTRY(entry_title_new[session_cursor]), session_list->current->session.sessionName);

            session_date_new[session_cursor] = gtk_label_new("Date :");
            entry_date_new[session_cursor] = gtk_entry_new();
            session_date_char[session_cursor] = get_date_UI(&session_list->current->session.sessionDate);
            gtk_entry_set_text(GTK_ENTRY(entry_date_new[session_cursor]), session_date_char[session_cursor]);
            free_info_UI(session_date_char[session_cursor]);
            calendar_session_date_button[session_cursor] = gtk_button_new_from_icon_name("x-office-calendar",
                                                                                         GTK_ICON_SIZE_LARGE_TOOLBAR);
            session_next_meeting[session_cursor] = gtk_label_new("Prochain rendez-vous : ");
            entry_next_meeting[session_cursor] = gtk_entry_new();
            next_session_date_char[session_cursor] = get_date_UI(&session_list->current->session.nextSessionDate);
            gtk_entry_set_text(GTK_ENTRY(entry_next_meeting[session_cursor]), next_session_date_char[session_cursor]);
            free_info_UI(next_session_date_char[session_cursor]);
            calendar_next_meeting_button[session_cursor] = gtk_button_new_from_icon_name("x-office-calendar",
                                                                                         GTK_ICON_SIZE_LARGE_TOOLBAR);
            session_next_meeting_hour[session_cursor] = gtk_label_new("Heure : ");
            entry_next_meeting_hour[session_cursor] = gtk_entry_new();
            space[session_cursor] = gtk_label_new("");
            gtk_entry_set_text(GTK_ENTRY(entry_next_meeting_hour[session_cursor]), session_list->current->session.nextSessionHour);

            save_button[session_cursor] = gtk_button_new_from_icon_name("document-save", GTK_ICON_SIZE_MENU);
            gtk_widget_set_tooltip_text(save_button[session_cursor], "Enregistrer");
            delete_button[session_cursor] = gtk_button_new_from_icon_name("edit-delete", GTK_ICON_SIZE_MENU);
            gtk_widget_set_tooltip_text(delete_button[session_cursor], "Supprimer la séance");
            new_session_button[session_cursor] = gtk_button_new_from_icon_name("list-add", GTK_ICON_SIZE_MENU);
            gtk_widget_set_tooltip_text(new_session_button[session_cursor], "Nouvelle séance");
            session_attach_button[session_cursor] = gtk_button_new_from_icon_name("mail-attachment",GTK_ICON_SIZE_MENU);
            gtk_widget_set_tooltip_text(session_attach_button[session_cursor], "Joindre un élément");

            text_session_note[session_cursor] = gtk_text_view_new();
            session_buffer[session_cursor] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_session_note[session_cursor]));
            gtk_text_buffer_get_end_iter(session_buffer[session_cursor], &end[session_cursor]);
            gtk_text_buffer_insert(session_buffer[session_cursor], &end[session_cursor],
                                   session_list->current->session.observations, -1);
            gtk_text_view_set_buffer(GTK_TEXT_VIEW(text_session_note[session_cursor]), session_buffer[session_cursor]);
            text_box[session_cursor] = gtk_scrolled_window_new(NULL, NULL);

            gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_session_note[session_cursor]), 5);
            gtk_text_view_set_right_margin(GTK_TEXT_VIEW(text_session_note[session_cursor]), 5);
            gtk_text_view_set_top_margin(GTK_TEXT_VIEW(text_session_note[session_cursor]), 5);
            gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(text_session_note[session_cursor]), 5);

            setOnNext(session_list);
        }

        /* GRID WHICH ORGANIZES THE SESSION SECTION */
        gtk_grid_set_row_spacing(GTK_GRID(grid_session_section), 0);
        gtk_container_add(GTK_CONTAINER(box), grid_session_section);


        /* STRUCTURE USED TO CREATE A NEW SESSION */
        AddNewSessionStruct *newSessionStruct = (AddNewSessionStruct *) malloc(sizeof(AddNewSessionStruct));
        newSessionStruct->notebook = notebook;
        newSessionStruct->attachmentLabel = attachmentCounterLabel;
        newSessionStruct->folderID = folderID;
        newSessionStruct->patientID = (int) workwindow->patient->id;

        /* NOTEBOOK TO DISPLAY THE DIFFERENT SESSIONS */
        gtk_grid_attach(GTK_GRID(grid_session_section), notebook, GTK_ALIGN_START, GTK_ALIGN_CENTER, 1, 1);
        gtk_widget_set_hexpand(notebook, TRUE);
        gtk_widget_set_vexpand(notebook, TRUE);
        gtk_widget_set_halign(notebook, GTK_ALIGN_FILL);

        setOnFirst(session_list);
        for (session_cursor = 0; session_cursor < nb_session; session_cursor++) {
            /* Manage the entry to add a title */
            gtk_grid_attach(GTK_GRID(grid_add_session[session_cursor]), session_title_new[session_cursor],
                            GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
            gtk_widget_set_hexpand(session_title_new[session_cursor], FALSE);
            gtk_widget_set_vexpand(session_title_new[session_cursor], FALSE);
            gtk_widget_set_halign(session_title_new[session_cursor], GTK_ALIGN_START);

            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), entry_title_new[session_cursor],
                                    session_title_new[session_cursor], GTK_POS_BOTTOM, 1, 1);
            gtk_widget_set_hexpand(entry_title_new[session_cursor], FALSE);
            gtk_widget_set_vexpand(entry_title_new[session_cursor], FALSE);
            gtk_widget_set_halign(entry_title_new[session_cursor], GTK_ALIGN_START);

            /* Manage to display the date of the session */
            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), session_date_new[session_cursor],
                                    session_title_new[session_cursor], GTK_POS_RIGHT, 1, 1);
            gtk_widget_set_hexpand(session_date_new[session_cursor], FALSE);
            gtk_widget_set_vexpand(session_date_new[session_cursor], FALSE);
            gtk_widget_set_halign(session_date_new[session_cursor], GTK_ALIGN_START);

            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), entry_date_new[session_cursor],
                                    session_date_new[session_cursor], GTK_POS_BOTTOM, 1, 1);
            gtk_widget_set_hexpand(entry_date_new[session_cursor], FALSE);
            gtk_widget_set_vexpand(entry_date_new[session_cursor], FALSE);
            gtk_widget_set_halign(entry_date_new[session_cursor], GTK_ALIGN_START);
            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]),
                                    calendar_session_date_button[session_cursor], entry_date_new[session_cursor],
                                    GTK_POS_RIGHT, 1, 1);
            gtk_widget_set_hexpand(calendar_session_date_button[session_cursor], FALSE);
            gtk_widget_set_halign(calendar_session_date_button[session_cursor], GTK_ALIGN_START);
            g_signal_connect(GTK_BUTTON(calendar_session_date_button[session_cursor]), "clicked",
                             G_CALLBACK(launchCalendar), entry_date_new[session_cursor]);

            /* Manage to display the next appointment */
            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), session_next_meeting[session_cursor],
                                    entry_date_new[session_cursor], GTK_POS_RIGHT, 1, 1);
            gtk_widget_set_hexpand(session_next_meeting[session_cursor], TRUE);
            gtk_widget_set_vexpand(session_next_meeting[session_cursor], FALSE);
            gtk_widget_set_halign(session_next_meeting[session_cursor], GTK_ALIGN_END);

            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), entry_next_meeting[session_cursor],
                                    session_next_meeting[session_cursor], GTK_POS_RIGHT, 8, 1);
            gtk_widget_set_hexpand(entry_next_meeting[session_cursor], FALSE);
            gtk_widget_set_vexpand(entry_next_meeting[session_cursor], FALSE);
            gtk_widget_set_halign(entry_next_meeting[session_cursor], GTK_ALIGN_START);
            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]),
                                    calendar_next_meeting_button[session_cursor], entry_next_meeting[session_cursor],
                                    GTK_POS_RIGHT, 8, 1);
            g_signal_connect(GTK_BUTTON(calendar_next_meeting_button[session_cursor]), "clicked",
                             G_CALLBACK(launchCalendar), entry_next_meeting[session_cursor]);

            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]),
                                    session_next_meeting_hour[session_cursor], session_next_meeting[session_cursor],
                                    GTK_POS_BOTTOM, 1, 1);
            gtk_widget_set_hexpand(session_next_meeting_hour[session_cursor], TRUE);
            gtk_widget_set_vexpand(session_next_meeting_hour[session_cursor], FALSE);
            gtk_widget_set_halign(session_next_meeting_hour[session_cursor], GTK_ALIGN_END);

            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), entry_next_meeting_hour[session_cursor],
                                    entry_next_meeting[session_cursor], GTK_POS_BOTTOM, 8, 1);
            gtk_widget_set_hexpand(entry_next_meeting_hour[session_cursor], FALSE);
            gtk_widget_set_vexpand(entry_next_meeting_hour[session_cursor], FALSE);
            gtk_widget_set_halign(entry_next_meeting_hour[session_cursor], GTK_ALIGN_START);

            /* Manage to display the new session button */
            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), new_session_button[session_cursor],
                                    entry_next_meeting[session_cursor], GTK_POS_TOP, 7, 1);
            gtk_widget_set_hexpand(new_session_button[session_cursor], FALSE);
            gtk_widget_set_vexpand(new_session_button[session_cursor], FALSE);
            gtk_widget_set_halign(new_session_button[session_cursor], GTK_ALIGN_END);
            g_signal_connect(GTK_BUTTON(new_session_button[session_cursor]), "clicked", G_CALLBACK(addNewSessionUI),
                             newSessionStruct);


            /* Manage to display the save button */
            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), save_button[session_cursor],
                                    calendar_next_meeting_button[session_cursor], GTK_POS_TOP, 1, 1);
            gtk_widget_set_hexpand(save_button[session_cursor], FALSE);
            gtk_widget_set_vexpand(save_button[session_cursor], FALSE);
            gtk_widget_set_halign(save_button[session_cursor], GTK_ALIGN_END);

            saveSession[session_cursor] = (SessionEntries *) malloc(sizeof(SessionEntries));
            saveSession[session_cursor]->session = &session_list->current->session;
            saveSession[session_cursor]->origin = (int) session_list->current->session.idSession;
            saveSession[session_cursor]->sessionName = entry_title_new[session_cursor];
            saveSession[session_cursor]->sessionDate = entry_date_new[session_cursor];
            saveSession[session_cursor]->nextSessionDate = entry_next_meeting[session_cursor];
            saveSession[session_cursor]->nextSessionHour = entry_next_meeting_hour[session_cursor];
            saveSession[session_cursor]->observations = text_session_note[session_cursor];
            saveSession[session_cursor]->notebook = notebook;
            g_signal_connect(GTK_BUTTON(save_button[session_cursor]), "clicked", G_CALLBACK(saveSessionEntries),
                             saveSession[session_cursor]);


            /* Manage the button to attach items */
            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), space[session_cursor], entry_title_new[session_cursor], GTK_POS_BOTTOM, 1, 1);
            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), session_attach_button[session_cursor], space[session_cursor], GTK_POS_BOTTOM, 1, 1);
            gtk_widget_set_hexpand(session_attach_button[session_cursor], FALSE);
            gtk_widget_set_vexpand(session_attach_button[session_cursor], FALSE);
            mediaChooser[session_cursor] = (MediaType *) malloc(sizeof(MediaType));
            mediaChooser[session_cursor]->patientID = (int) workwindow->patient->id;
            mediaChooser[session_cursor]->folderID = folderID;
            mediaChooser[session_cursor]->mediaType = 1;
            mediaChooser[session_cursor]->counterLabel = attachmentCounterLabel;
            mediaChooser[session_cursor]->isNewPatient = 0;
            g_signal_connect(GTK_BUTTON(session_attach_button[session_cursor]), "clicked", G_CALLBACK(launchFileChooser), mediaChooser[session_cursor]);

            /* Manage to display the delete session button */
            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), delete_button[session_cursor],
                                    session_attach_button[session_cursor], GTK_POS_BOTTOM, 1, 1);
            gtk_widget_set_hexpand(delete_button[session_cursor], FALSE);
            gtk_widget_set_vexpand(delete_button[session_cursor], TRUE);
            gtk_widget_set_valign(delete_button[session_cursor], GTK_ALIGN_END);
            sessionDelete[session_cursor] = (DeleteElements *) malloc(sizeof(DeleteElements));
            sessionDelete[session_cursor]->window = workwindow->window;
            sessionDelete[session_cursor]->isFolder = 0;
            sessionDelete[session_cursor]->sessionID = (int) session_list->current->session.idSession;
            sessionDelete[session_cursor]->notebook = notebook;
            sessionDelete[session_cursor]->patientID = (int) workwindow->patient->id;
            sessionDelete[session_cursor]->folderID = folderID;
            g_signal_connect(GTK_BUTTON(delete_button[session_cursor]), "clicked", G_CALLBACK(launchDeleteElement),
                             sessionDelete[session_cursor]);


            /* Manage the frame and its entry to add informations about the session */
            gtk_frame_set_label_align(GTK_FRAME(frame_session_note[session_cursor]), 0, (float) 0.5);
            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), frame_session_note[session_cursor],
                                    session_attach_button[session_cursor], GTK_POS_RIGHT, 11, 3);
            gtk_widget_set_hexpand(frame_session_note[session_cursor], TRUE);
            gtk_widget_set_vexpand(frame_session_note[session_cursor], TRUE);

            gtk_container_add(GTK_CONTAINER(frame_session_note[session_cursor]), text_box[session_cursor]);
            gtk_container_add(GTK_CONTAINER(text_box[session_cursor]), text_session_note[session_cursor]);
            gtk_widget_set_hexpand(text_session_note[session_cursor], TRUE);
            gtk_widget_set_vexpand(text_session_note[session_cursor], TRUE);

            gtk_notebook_append_page(GTK_NOTEBOOK(notebook), grid_add_session[session_cursor],
                                     gtk_label_new(session_list->current->session.sessionName));
            setOnNext(session_list);
        }
    }
}

/*!
 * \brief Allows to close the home window and open the work window
 *
 * When the user click on a patient from the patient window, this function closes
 * the patient window and open the session window related to the patient selected.
 *
 * * \param[in] but : Button pressed to call this function
 * \param[in] window_id : Window to be refresh and ID of the Patient concerned

*/
void launchWorkView(GtkWidget *but, Window_id *window_id){
    int fullScreen = 0;
    if(gtk_window_is_maximized(GTK_WINDOW(window_id->window))==TRUE) fullScreen = 1;
    gtk_widget_destroy(window_id->window);
    setWorkWindow(fullScreen, window_id->patientID, window_id->folderID);

}

/*!
 * \brief Create a new default session in BDD and display it in notebook
 *
 * When the user wants to create a new session, this function add an empty
 * session in BDD and in the notebook
 *
 * \param[in] button : Button pressed to call this function
 * \param[in] newSessionStruct : Structure containing widgets to update
*/
void addNewSessionUI(GtkWidget *button, AddNewSessionStruct *newSessionStruct){
    /* DECLARE VARIABLES */
    GtkWidget *notebook = newSessionStruct->notebook;
    Session *new_session = createEmptySession(newSessionStruct->folderID);
    new_session->idSession = (unsigned int) getFutureSessionId();
    GtkWidget *grid_add_session;
    GtkWidget *frame_session_note;

    GtkWidget *session_title_new;
    GtkWidget *entry_title_new;
    GtkWidget *session_date_new;
    GtkWidget *entry_date_new;
    GtkWidget *calendar_session_date_button = NULL;
    GtkWidget *save_button;
    GtkWidget *new_session_button;
    GtkWidget *session_next_meeting;
    GtkWidget *entry_next_meeting;
    GtkWidget *calendar_next_meeting_button = NULL;
    GtkWidget *session_next_meeting_hour;
    GtkWidget *entry_next_meeting_hour;
    GtkWidget *space;
    GtkWidget *session_attach_button;
    GtkWidget *delete_button = NULL;
    GtkWidget *text_session_note;
    GtkTextBuffer *session_buffer;
    GtkTextIter end;
    GtkWidget *text_box = NULL;

    /* ASSIGN VARIABLES */
    grid_add_session = gtk_grid_new();
    frame_session_note = gtk_frame_new("Observations");

    session_title_new = gtk_label_new("Titre :");
    entry_title_new = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_title_new), new_session->sessionName);

    session_date_new = gtk_label_new("Date :");
    entry_date_new = gtk_entry_new();
    char *session_date_char = get_date_UI(&new_session->sessionDate);
    gtk_entry_set_text(GTK_ENTRY(entry_date_new), session_date_char);
    free_info_UI(session_date_char);
    calendar_session_date_button = gtk_button_new_from_icon_name("x-office-calendar", GTK_ICON_SIZE_LARGE_TOOLBAR);


    session_next_meeting = gtk_label_new("Prochain rendez-vous : ");
    entry_next_meeting = gtk_entry_new();
    char *next_session_date_char = get_date_UI(&new_session->nextSessionDate);
    gtk_entry_set_text(GTK_ENTRY(entry_next_meeting), next_session_date_char);
    free_info_UI(next_session_date_char);
    calendar_next_meeting_button = gtk_button_new_from_icon_name("x-office-calendar", GTK_ICON_SIZE_LARGE_TOOLBAR);

    session_next_meeting_hour = gtk_label_new("Heure : ");
    entry_next_meeting_hour = gtk_entry_new();
    space = gtk_label_new("");
    gtk_entry_set_text(GTK_ENTRY(entry_next_meeting_hour), "12:00");

    save_button = gtk_button_new_from_icon_name("document-save", GTK_ICON_SIZE_MENU);
    gtk_widget_set_tooltip_text(save_button, "Enregistrer");
    new_session_button = gtk_button_new_from_icon_name("list-add", GTK_ICON_SIZE_MENU);
    gtk_widget_set_tooltip_text(new_session_button, "Nouvelle séance");
    session_attach_button = gtk_button_new_from_icon_name("mail-attachment", GTK_ICON_SIZE_MENU);
    gtk_widget_set_tooltip_text(session_attach_button, "Joindre un élément");
    delete_button = gtk_button_new_from_icon_name("edit-delete", GTK_ICON_SIZE_MENU);
    gtk_widget_set_tooltip_text(delete_button, "Supprimer la séance");

    text_session_note = gtk_text_view_new();
    session_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_session_note));
    gtk_text_buffer_get_end_iter(session_buffer, &end);
    gtk_text_buffer_insert(session_buffer, &end, new_session->observations, -1);
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(text_session_note), session_buffer);
    text_box = gtk_scrolled_window_new(NULL, NULL);

    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_session_note), 5);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(text_session_note), 5);
    gtk_text_view_set_top_margin(GTK_TEXT_VIEW(text_session_note), 5);
    gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(text_session_note), 5);

    /* CREATE THE STRUCTURE OF THE WINDOW */
    /* Manage the entry to add a title */
    gtk_grid_attach(GTK_GRID(grid_add_session), session_title_new, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(session_title_new, FALSE);
    gtk_widget_set_vexpand(session_title_new, FALSE);
    gtk_widget_set_halign(session_title_new, GTK_ALIGN_START);

    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), entry_title_new, session_title_new, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(entry_title_new, FALSE);
    gtk_widget_set_vexpand(entry_title_new, FALSE);
    gtk_widget_set_halign(entry_title_new, GTK_ALIGN_START);

    /* Manage to display the date of the session */
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), session_date_new, session_title_new, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_hexpand(session_date_new, FALSE);
    gtk_widget_set_vexpand(session_date_new, FALSE);
    gtk_widget_set_halign(session_date_new, GTK_ALIGN_START);

    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), entry_date_new, session_date_new, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(entry_date_new, FALSE);
    gtk_widget_set_vexpand(entry_date_new, FALSE);
    gtk_widget_set_halign(entry_date_new, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), calendar_session_date_button, entry_date_new, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_hexpand(calendar_session_date_button, FALSE);
    gtk_widget_set_halign(calendar_session_date_button, GTK_ALIGN_START);
    g_signal_connect(GTK_BUTTON(calendar_session_date_button), "clicked", G_CALLBACK(launchCalendar), entry_date_new);


    /* Manage to display the next appointment */
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), session_next_meeting, entry_date_new, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_hexpand(session_next_meeting, TRUE);
    gtk_widget_set_vexpand(session_next_meeting, FALSE);
    gtk_widget_set_halign(session_next_meeting, GTK_ALIGN_END);

    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), entry_next_meeting, session_next_meeting, GTK_POS_RIGHT, 8, 1);
    gtk_widget_set_hexpand(entry_next_meeting, FALSE);
    gtk_widget_set_vexpand(entry_next_meeting, FALSE);
    gtk_widget_set_halign(entry_next_meeting, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), calendar_next_meeting_button, entry_next_meeting, GTK_POS_RIGHT, 8, 1);
    g_signal_connect(GTK_BUTTON(calendar_next_meeting_button), "clicked", G_CALLBACK(launchCalendar), entry_next_meeting);

    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), session_next_meeting_hour, session_next_meeting, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(session_next_meeting_hour, TRUE);
    gtk_widget_set_vexpand(session_next_meeting_hour, FALSE);
    gtk_widget_set_halign(session_next_meeting_hour, GTK_ALIGN_END);

    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), entry_next_meeting_hour, entry_next_meeting, GTK_POS_BOTTOM, 8, 1);
    gtk_widget_set_hexpand(entry_next_meeting_hour, FALSE);
    gtk_widget_set_vexpand(entry_next_meeting_hour, FALSE);
    gtk_widget_set_halign(entry_next_meeting_hour, GTK_ALIGN_START);

    /* Manage to display the new session button */
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), new_session_button, entry_next_meeting, GTK_POS_TOP, 7, 1);
    gtk_widget_set_hexpand(new_session_button, FALSE);
    gtk_widget_set_vexpand(new_session_button, FALSE);
    gtk_widget_set_halign(new_session_button, GTK_ALIGN_END);
    g_signal_connect(GTK_BUTTON(new_session_button), "clicked", G_CALLBACK(addNewSessionUI), newSessionStruct);

    /* Manage to display the save button */
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), save_button, calendar_next_meeting_button, GTK_POS_TOP, 1, 1);
    gtk_widget_set_hexpand(save_button, FALSE);
    gtk_widget_set_vexpand(save_button, FALSE);
    gtk_widget_set_halign(save_button, GTK_ALIGN_END);

    SessionEntries *saveSession = (SessionEntries*) malloc(sizeof(SessionEntries));
    saveSession->session = new_session;
    saveSession->origin = (int) new_session->idSession;
    saveSession->sessionName = entry_title_new;
    saveSession->sessionDate = entry_date_new;
    saveSession->nextSessionDate = entry_next_meeting;
    saveSession->nextSessionHour = entry_next_meeting_hour;
    saveSession->observations = text_session_note;
    saveSession->notebook = notebook;
    g_signal_connect(GTK_BUTTON(save_button), "clicked", G_CALLBACK(saveSessionEntries), saveSession);

    /* Manage the button to attach items */
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), space, entry_title_new, GTK_POS_BOTTOM, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), session_attach_button, space, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(session_attach_button, FALSE);
    gtk_widget_set_vexpand(session_attach_button, FALSE);
    MediaType *mediaChooser = (MediaType *) malloc(sizeof(MediaType));
    mediaChooser->patientID = newSessionStruct->patientID;
    mediaChooser->folderID = newSessionStruct->folderID;
    mediaChooser->mediaType = 1;
    mediaChooser->counterLabel = newSessionStruct->attachmentLabel;
    mediaChooser->isNewPatient = 0;
    g_signal_connect(GTK_BUTTON(session_attach_button), "clicked", G_CALLBACK(launchFileChooser), mediaChooser);


    /* Manage to display the delete session button */
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), delete_button, session_attach_button, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(delete_button, FALSE);
    gtk_widget_set_vexpand(delete_button, TRUE);
    gtk_widget_set_valign(delete_button, GTK_ALIGN_END);
    DeleteElements *sessionDelete = (DeleteElements *) malloc(sizeof(DeleteElements));
    sessionDelete->isFolder = 0;
    sessionDelete->sessionID = (int) newSessionStruct->folderID;
    sessionDelete->notebook = notebook;
    sessionDelete->patientID = (int) newSessionStruct->patientID;
    sessionDelete->folderID = newSessionStruct->folderID;
    g_signal_connect(GTK_BUTTON(delete_button), "clicked", G_CALLBACK(launchDeleteElement), sessionDelete);


    /* Manage the frame and its entry to add informations about the session */
    gtk_frame_set_label_align(GTK_FRAME(frame_session_note), 0, (float) 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), frame_session_note, session_attach_button, GTK_POS_RIGHT, 11, 3);
    gtk_widget_set_hexpand(frame_session_note, TRUE);
    gtk_widget_set_vexpand(frame_session_note, TRUE);

    gtk_container_add(GTK_CONTAINER(frame_session_note), text_box);
    gtk_container_add(GTK_CONTAINER(text_box), text_session_note);
    gtk_widget_set_hexpand(text_session_note, TRUE);
    gtk_widget_set_vexpand(text_session_note, TRUE);

    char *new_session_name = get_new_session_name();
    gtk_notebook_insert_page(GTK_NOTEBOOK(notebook), grid_add_session, gtk_label_new(new_session_name), 0);
    free(new_session_name);

    addSession(new_session);
    gtk_widget_show_all(notebook);

}

/*!
 * \brief Create the first session of a folder in BDD and display it
 *
 * When a folder contains no sessio and this function is called, it creates a new session
 * in BDD and display it in the notebook
 *
 * \param[in] button : Button pressed to call this function
 * \param[in] firstSessionStruct : Structure containing widgets to update
*/
void addFirstSessionUI(GtkWidget *button, AddFirstSessionStruct *firstSessionStruct){
    int fullScreen = 0;
    if(gtk_window_is_maximized(GTK_WINDOW(firstSessionStruct->window))==TRUE) fullScreen = 1;
    gtk_widget_destroy(firstSessionStruct->window);
    createNewSession(firstSessionStruct->folderID);
    setWorkWindow(fullScreen, firstSessionStruct->patientID, firstSessionStruct->folderID);
}

void modifyFirstSessionHours(GtkWidget *entry, firstSessionHoursStruct *fSHS){

    gtk_label_set_text(GTK_LABEL(fSHS->stateLabel), "(enregistré)");

    fSHS->session->nextSessionDate.day = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(fSHS->dateEntry)))->day;
    fSHS->session->nextSessionDate.month = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(fSHS->dateEntry)))->month;
    fSHS->session->nextSessionDate.year = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(fSHS->dateEntry)))->year;

    strcpy(fSHS->session->nextSessionHour, (char*) gtk_entry_get_text(GTK_ENTRY(fSHS->hourEntry)));
    modifySession(fSHS->session);
}


/* HELPERS */

/*!
 * \brief Set right default margin
 * \param[in] widget Widget concerned
*/
void setStartMargin(GtkWidget *widget){
    gtk_widget_set_margin_start(widget, 5);
}

/*!
 * \brief Set top default margin
 * \param[in] widget Widget concerned
*/
void setTopMargin(GtkWidget *widget){
    gtk_widget_set_margin_top(widget, 5);
}
