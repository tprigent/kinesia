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
#include "../model/session_manager.h"


/*!
* \brief Initiate session window with some default parameters
 *
 * Focus, position, size, title and destroy callback are set.
 *
 * \param[in] id_patient ID of the patient file opened
*/
GtkWidget *setWorkWindow(int id_patient, int id_folder){

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
* \brief Split the main window in three spaces and fill them
 *
 * The three spaces are:
 * on the left side the patient,
 * at the top right the current folder,
 * and at the bottom right the list of all the sessions.
 *
 * The three boxes are filled by external functions.
 *
 * \param[in] window_id Window_id structure with window, patient ID and session
*/
void setWorkEnvironment(Window_id *window_id){

    /* GET PATIENT STRUCTURE FROM BDD */
    Patient *patient = getPatient(window_id->patientID);

    GtkWidget *window = window_id->window;
    GtkWidget *grid = NULL;
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

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
    fillPatientBox(window, boxPart[0], boxPart[1], boxPart[2], patient, window_id->folderID);
}


/*!
* \brief Fill the Patient box
 *
 * The box is made up of the main infos (anamnesis) and a photo from the Patient.
 *
 * At the top a button to go back to the patient view is set up.
 *
 * At the bottom a folder chooser is displayed.
 *
 * \param[in] window Current window to enable refresh
 * \param[in] box Existing patient box
 * \param[in] patient Current Patient
*/
void fillPatientBox(GtkWidget *window, GtkWidget *patientBox, GtkWidget *folderBox, GtkWidget *sessionBox, Patient *patient, int id_folder){

    /* CREATE STRUCT TO PASS ARGUMENTS TO DIALOG BOX */
    Patient_window *patient_window = (Patient_window*) malloc(sizeof(Patient_window));
    patient_window->patient = patient;
    patient_window->window = window;
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

    char *patient_name_char = get_name_UI(patient);
    char *patient_birth_char = get_age_and_birthdate(patient);
    char *patient_height_weight_char = get_height_weight_UI(patient);
    char *patient_first_consultation_char = get_first_consultation_UI(patient);

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
    patient_photo_pixbuf = gdk_pixbuf_new_from_file(getProfilePhotoPath(patient), NULL);
    patient_photo_pixbuf = gdk_pixbuf_scale_simple(patient_photo_pixbuf, 145, 193, GDK_INTERP_BILINEAR);
    patient_photo = gtk_image_new_from_pixbuf(GDK_PIXBUF(patient_photo_pixbuf));
    patient_name = gtk_label_new(patient_name_char);
    free_info_UI(patient_name_char);
    patient_birth = gtk_label_new(patient_birth_char);
    free_info_UI(patient_birth_char);
    patient_job = gtk_label_new(patient->job);
    patient_height_weight = gtk_label_new(patient_height_weight_char);
    free_info_UI(patient_height_weight_char);
    patient_first_consultation = gtk_label_new(patient_first_consultation_char);
    free_info_UI(patient_first_consultation_char);
    patient_other_info = gtk_label_new(patient->global_pathologies);


    /* MANAGE THE GRID WHICH ORGANIZES THE LEFT SECTION */
    gtk_grid_set_row_spacing(GTK_GRID(grid_left_section), 5);
    gtk_box_pack_start(GTK_BOX(patientBox), grid_left_section, TRUE, TRUE, 0);


    /* ******************************* FIRST PART : BUTTON "REVENIR A LA LISTE PATIENT" ******************************* */
    gtk_grid_attach(GTK_GRID(grid_left_section), back_button, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(back_button, FALSE);
    gtk_widget_set_vexpand(back_button, FALSE);
    gtk_widget_set_halign(back_button, GTK_ALIGN_START);
    g_signal_connect(GTK_BUTTON(back_button), "clicked", G_CALLBACK(launchHomeView), window);



    /* ************************** SECOND PART : SECTION WHICH CONTAINS PATIENT INFORMATION **************************** */
    /* Manage the frame global and its grid */
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
    gtk_widget_set_hexpand(patient_name, TRUE);
    gtk_widget_set_vexpand(patient_name, FALSE);
    gtk_widget_set_halign(patient_name, GTK_ALIGN_CENTER);

    // Birthdate
    gtk_label_set_use_markup(GTK_LABEL(patient_birth), TRUE);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), patient_birth, patient_name, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(patient_birth, TRUE);
    gtk_widget_set_vexpand(patient_birth, FALSE);
    gtk_widget_set_halign(patient_birth, GTK_ALIGN_CENTER);

    // Job
    gtk_label_set_use_markup(GTK_LABEL(patient_job), TRUE);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), patient_job, patient_birth, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(patient_job, TRUE);
    gtk_widget_set_vexpand(patient_job, FALSE);
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
    gtk_widget_set_halign(patient_height_weight, GTK_ALIGN_CENTER);

    // First consultation
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), patient_first_consultation, patient_height_weight, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(patient_first_consultation, TRUE);
    gtk_widget_set_vexpand(patient_first_consultation, FALSE);
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


    /* ******************************* THIRD PART : SECTION WHICH CONTAINS THE FOLDERS ******************************** */

    /* DECLARE VARIABLES */
    GtkWidget *folder_box = NULL;
    folder_box = gtk_scrolled_window_new(NULL, NULL);
    gtk_grid_attach_next_to(GTK_GRID(grid_left_section), folder_box, frame_info, GTK_POS_BOTTOM, 3, 1);
    gtk_widget_set_hexpand(folder_box, TRUE);
    gtk_widget_set_vexpand(folder_box, TRUE);

    GtkWidget *folder_grid = NULL;
    folder_grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(folder_box), folder_grid);

    int *idFolderTab = getIdFolder((int) patient->id);
    int folder_cursor;

    int nb_folders = getNbFolder((int) patient->id);
    GtkWidget *folder_button[nb_folders];
    char *name_folder[nb_folders];

    /* ASSIGN VARIABLES */
    for(folder_cursor = 0; folder_cursor < nb_folders; folder_cursor++){

        name_folder[folder_cursor] = getNameFolder(idFolderTab[folder_cursor]);
        folder_button[folder_cursor] = gtk_button_new_with_label(name_folder[folder_cursor]);
        free(name_folder[folder_cursor]);
    }

    /* MANAGE TO DISPLAY BUTTONS */
    if(nb_folders > 0){
        gtk_grid_attach(GTK_GRID(folder_grid), folder_button[0], GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
        gtk_widget_set_hexpand(folder_button[0], TRUE);
        Window_id *window_id[nb_folders];
        window_id[0] = (Window_id*) malloc(sizeof(Window_id));
        window_id[0]->window = window;
        window_id[0]->patientID = (int) patient->id;
        window_id[0]->folderID = idFolderTab[0];
        g_signal_connect(GTK_BUTTON(folder_button[0]), "clicked", G_CALLBACK(launchWorkView), window_id[0]);

        for(folder_cursor = 1; folder_cursor < nb_folders; folder_cursor++){
            gtk_grid_attach_next_to(GTK_GRID(folder_grid), folder_button[folder_cursor], folder_button[folder_cursor-1], GTK_POS_BOTTOM, 1, 1);
            gtk_widget_set_hexpand(folder_button[folder_cursor], TRUE);
            window_id[folder_cursor] = (Window_id*) malloc(sizeof(Window_id));
            window_id[folder_cursor]->window = window;
            window_id[folder_cursor]->patientID = (int) patient->id;
            window_id[folder_cursor]->folderID = idFolderTab[folder_cursor];
            g_signal_connect(GTK_BUTTON(folder_button[folder_cursor]), "clicked", G_CALLBACK(launchWorkView), window_id[folder_cursor]);
        }
    }

    if(nb_folders>0 && id_folder == 0){
        fillFolderBox(window, folderBox, idFolderTab[0], patient);
        fillSessionBox(window, sessionBox, idFolderTab[0], patient);
    }
    else if(nb_folders>0 && id_folder != 0){
        fillFolderBox(window, folderBox, id_folder, patient);
        fillSessionBox(window, sessionBox, id_folder, patient);
    }
    else{
        fillFolderBox(window, folderBox, 0, patient);
        fillSessionBox(window, sessionBox, 0, patient);
    }


    /*folder_button[0] = gtk_button_new_with_label(name_folder[0]);
    gtk_grid_attach(GTK_GRID(folder_grid), folder_button[0], GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(folder_button[0], TRUE);
    for(i = 1; i < nb_folders; i++){
        folder_button[i] = gtk_button_new_with_label(name_folder[i]);
        gtk_grid_attach_next_to(GTK_GRID(folder_grid), folder_button[i], folder_button[i-1], GTK_POS_BOTTOM, 1, 1);
        gtk_widget_set_hexpand(folder_button[i], TRUE);
    }*/

}

/*!
* \brief Fill the Folder box
 *
 * The box is made up of the current Folder infos.
 *
 * A button is displayed to see the attached media related to this Folder.
 *
 * \param[in] box Existing Folder box
*/
void fillFolderBox(GtkWidget *window, GtkWidget *box, int activeFolder, Patient *patient){

    /* Getting folder  ************************************************************** */
    Folder *folder = NULL;
    if(activeFolder != 0){
        folder = getFolder(activeFolder);
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

        IdPatientCallback *idPatient = (IdPatientCallback*) malloc(sizeof(IdPatientCallback));
        idPatient->idPatient = (int) patient->id;
        idPatient->window = window;
        g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(launchNewFolderEditor), idPatient);
        return ;
    }

    /* ****************************************************************************** */

    /* Create a grid which contains the different elements of the folder ************ */
    GtkWidget *grid_part2 = NULL;
    grid_part2 = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(box), grid_part2, TRUE, TRUE, 0);
    /* ****************************************************************************** */

    /* Create a frame for the folder zone ******************************************* */
    GtkWidget *frame_folder = NULL;
    frame_folder = gtk_frame_new("Dossier");
    gtk_frame_set_label_align(GTK_FRAME(frame_folder), (float)0.5, (float) 0.5);
    gtk_grid_attach(GTK_GRID(grid_part2), frame_folder, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(frame_folder, TRUE);
    gtk_widget_set_vexpand(frame_folder, TRUE);
    /* ****************************************************************************** */

    /* Create a grid to display all the elements ************************************ */
    GtkWidget *grid_folder = NULL;
    grid_folder = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(frame_folder), grid_folder);
    gtk_container_set_border_width(GTK_CONTAINER(grid_folder), 0);
    /* ****************************************************************************** */


    /* Display the folder title ***************************************************** */
    /* BOX */
    GtkWidget *hbox_folder = NULL;
    hbox_folder = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_grid_attach(GTK_GRID(grid_folder), hbox_folder, GTK_ALIGN_CENTER, GTK_ALIGN_START, 3, 1);

    /* CONSTRAINTS */
    gtk_widget_set_hexpand(hbox_folder, TRUE);
    gtk_widget_set_vexpand(hbox_folder, FALSE);
    gtk_widget_set_halign(hbox_folder, GTK_ALIGN_CENTER);

    /* MARGINS */
    gtk_widget_set_margin_top(hbox_folder, 10);
    gtk_widget_set_margin_bottom(hbox_folder, 40);

    /* LABEL */
    GtkWidget *folder_title = NULL;
    char *formatted_folder_title_UI = get_formatted_folder_title_UI(folder);
    folder_title = gtk_label_new(formatted_folder_title_UI);
    free_info_UI(formatted_folder_title_UI);
    gtk_label_set_use_markup(GTK_LABEL(folder_title), TRUE);
    gtk_widget_set_halign(folder_title, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(hbox_folder), folder_title, FALSE, FALSE, 0);

    /* ****************************************************************************** */

    /* Display start of treatment *************************************************** */
    /* BOX */
    GtkWidget *hbox_treatment = NULL;
    hbox_treatment = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_folder), hbox_treatment, hbox_folder, GTK_POS_BOTTOM, 1, 1);

    /* CONSTRAINTS */
    gtk_widget_set_hexpand(hbox_treatment, TRUE);
    gtk_widget_set_vexpand(hbox_treatment, FALSE);
    gtk_widget_set_halign(hbox_treatment, GTK_ALIGN_START);

    /* MARGIN */
    setStartMargin(hbox_treatment);

    /* LABEL */
    GtkWidget *folder_start_treatment = NULL;
    GtkWidget *folder_date = NULL;
    char *start_of_treatment = get_date_UI(&folder->startOfTreatment);
    folder_start_treatment = gtk_label_new("Début de traitement: ");
    folder_date = gtk_label_new(start_of_treatment);
    free_info_UI(start_of_treatment);
    gtk_box_pack_start(GTK_BOX(hbox_treatment), folder_start_treatment, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_treatment), folder_date, FALSE, FALSE, 0);

    /* ****************************************************************************** */

    /* Display pathology ************************************************************ */
    /* BOX */
    GtkWidget *hbox_pathology = NULL;
    hbox_pathology = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_folder), hbox_pathology, hbox_treatment, GTK_POS_RIGHT, 1, 1);

    /* CONSTRAINTS */
    gtk_widget_set_hexpand(hbox_pathology, TRUE);
    gtk_widget_set_vexpand(hbox_pathology, FALSE);
    gtk_widget_set_halign(hbox_pathology, GTK_ALIGN_START);

    /* LABEL */
    GtkWidget *folder_pathology = NULL;
    GtkWidget *folder_pathology_name = NULL;
    folder_pathology = gtk_label_new("Pathologie: ");
    folder_pathology_name = gtk_label_new(folder->pathology);
    gtk_box_pack_start(GTK_BOX(hbox_pathology), folder_pathology, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_pathology), folder_pathology_name, FALSE, FALSE, 0);

    /* ****************************************************************************** */

    /* Display other infos ********************************************************** */
    /* BOXES */
    GtkWidget *vbox_infos = NULL;
    GtkWidget *vbox_infos_content = NULL;
    vbox_infos = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    vbox_infos_content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_folder), vbox_infos, hbox_treatment, GTK_POS_BOTTOM, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid_folder), vbox_infos_content, vbox_infos, GTK_POS_BOTTOM, 1, 1);

    /* CONSTRAINTS */
    gtk_widget_set_hexpand(vbox_infos, FALSE);
    gtk_widget_set_vexpand(vbox_infos, FALSE);
    gtk_widget_set_halign(vbox_infos, GTK_ALIGN_START);

    gtk_widget_set_hexpand(vbox_infos_content, FALSE);
    gtk_widget_set_vexpand(vbox_infos_content, FALSE);
    gtk_widget_set_halign(vbox_infos_content, GTK_ALIGN_START);

    /* MARGINS */
    gtk_widget_set_margin_top(vbox_infos, 20);
    gtk_widget_set_margin_top(vbox_infos_content, 5);
    setStartMargin(vbox_infos);
    setStartMargin(vbox_infos_content);

    /* LABELS */
    GtkWidget *folder_infos = NULL;
    GtkWidget *folder_infos_content = NULL;
    char *formatted_infos = get_formatted_folder_infos_UI(folder);
    folder_infos = gtk_label_new("<u>Autres informations</u> : ");
    gtk_label_set_use_markup(GTK_LABEL(folder_infos), TRUE);
    folder_infos_content = gtk_label_new(formatted_infos);
    //free_folder_infos_UI(formatted_infos);
    gtk_box_pack_start(GTK_BOX(vbox_infos), folder_infos, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_infos_content), folder_infos_content, FALSE, FALSE, 0);

    /* ****************************************************************************** */

    /* See attachments ************************************************************** */
    /* BOX */
    GtkWidget *hbox_attachments = NULL;
    hbox_attachments = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_folder), hbox_attachments, hbox_pathology, GTK_POS_BOTTOM,1,2);

    /* CONSTRAINTS */
    gtk_widget_set_hexpand(hbox_attachments, FALSE);
    gtk_widget_set_vexpand(hbox_attachments, FALSE);
    gtk_widget_set_halign(hbox_attachments, GTK_ALIGN_START);

    /* MARGINS */
    gtk_widget_set_margin_top(hbox_attachments, 20);

    /* LABEL */
    GtkWidget *attachments_label = NULL;
    GtkWidget *attachments_count = NULL;
    char *indicator = get_indicator_files_UI(patient);
    attachments_label = gtk_label_new("Pièces jointes:    ");
    attachments_count = gtk_label_new(indicator);
    free_info_UI(indicator);
    gtk_box_pack_start(GTK_BOX(hbox_attachments), attachments_label, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(hbox_attachments), attachments_count, FALSE, FALSE, 0);

    /* BUTTON */
    GtkWidget *attachments_button = NULL;
    attachments_button = gtk_button_new_from_icon_name("folder-documents", GTK_ICON_SIZE_MENU);
    gtk_widget_set_hexpand(attachments_button, FALSE);
    gtk_widget_set_vexpand(attachments_button, FALSE);
    gtk_box_pack_start(GTK_BOX(hbox_attachments), attachments_button, FALSE, FALSE, 0);
    g_signal_connect(GTK_BUTTON(attachments_button), "clicked", G_CALLBACK(launchAttachmentListViewer), patient);
    /* ****************************************************************************** */

    /* Edit button ****************************************************************** */
    /* BOX */
    GtkWidget *hbox_edit_folder = NULL;
    hbox_edit_folder = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_folder), hbox_edit_folder, hbox_folder, GTK_POS_RIGHT, 1, 1);

    /* CONSTRAINTS */
    gtk_widget_set_hexpand(hbox_edit_folder, FALSE);
    gtk_widget_set_vexpand(hbox_edit_folder, FALSE);
    gtk_widget_set_halign(hbox_edit_folder, GTK_ALIGN_END);
    gtk_widget_set_valign(hbox_edit_folder, GTK_ALIGN_END);

    /* BUTTON */
    GtkWidget *new_button = NULL;
    new_button = gtk_button_new_from_icon_name("list-add", GTK_ICON_SIZE_MENU);

    IdPatientCallback *idPatient = (IdPatientCallback*) malloc(sizeof(IdPatientCallback));
    idPatient->idPatient = (int) patient->id;
    idPatient->window = window;
    g_signal_connect(GTK_BUTTON(new_button), "clicked", G_CALLBACK(launchNewFolderEditor), idPatient);
    gtk_widget_set_hexpand(new_button, FALSE);
    gtk_widget_set_vexpand(new_button, FALSE);
    gtk_box_pack_start(GTK_BOX(hbox_edit_folder), new_button, FALSE, FALSE, 0);

    GtkWidget *edit_folder_button = NULL;
    edit_folder_button = gtk_button_new_from_icon_name("text-editor", GTK_ICON_SIZE_MENU);
    FolderEditorStruct *foldEditStruct = (FolderEditorStruct*) malloc(sizeof(FolderEditorStruct));
    foldEditStruct->folder = folder;
    foldEditStruct->edit_new = 1;
    foldEditStruct->window = window;
    g_signal_connect(GTK_BUTTON(edit_folder_button), "clicked", G_CALLBACK(launchFolderEditor), foldEditStruct);
    gtk_widget_set_hexpand(edit_folder_button, FALSE);
    gtk_widget_set_vexpand(edit_folder_button, FALSE);
    gtk_box_pack_start(GTK_BOX(hbox_edit_folder), edit_folder_button, FALSE, FALSE, 0);

    /* ****************************************************************************** */

}

/*!
* \brief Fill the Session box
 *
 * The box is made up of a list of the passed Sessions
 * and the current related to the current Folder.
 *
 * This box allows the user to edit data.
 *
 * The button to attach files is set up.
 *
 * \param[in] window Current window to enable refresh
 * \param[in] box Existing Session box
 * \param[in] idPatient ID of the current Patient
*/
void fillSessionBox(GtkWidget *window, GtkWidget *box, int idFolder, Patient *patient){

    if(idFolder == 0){
        GtkWidget *label = gtk_label_new("Ce patient n'a pas de dossier associé");
        GtkWidget *frame = gtk_frame_new("");
        gtk_container_add(GTK_CONTAINER(box), frame);
        gtk_container_add(GTK_CONTAINER(frame), label);
        gtk_widget_set_hexpand(frame, TRUE);
        gtk_widget_set_vexpand(frame, TRUE);
        return ;
    }

    int nb_session = getNbSession(idFolder);
    /*if(nb_session ==0){
        GtkWidget *label = gtk_label_new("Le dossier sélectionné ne contient aucune séance.\nAjouter une séance :");
        GtkWidget *frame = gtk_frame_new("");
        GtkWidget *grid = gtk_grid_new();
        GtkWidget *button = gtk_button_new_from_icon_name("list-add", GTK_ICON_SIZE_MENU);
        gtk_container_add(GTK_CONTAINER(box), frame);
        gtk_container_add(GTK_CONTAINER(frame), grid);
        gtk_grid_attach(GTK_GRID(grid), label, GTK_ALIGN_CENTER, GTK_ALIGN_CENTER, 1, 1);
        gtk_grid_attach_next_to(GTK_GRID(grid), button, label, GTK_POS_BOTTOM, 1, 1);
        gtk_widget_set_hexpand(frame, TRUE);
        gtk_widget_set_hexpand(grid, TRUE);
        gtk_widget_set_vexpand(grid, TRUE);
        gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
        gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
        gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
        gtk_widget_set_valign(label, GTK_ALIGN_CENTER);

        return ;
    }*/

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
    GtkWidget *save_button[nb_session];
    GtkWidget *new_session_button[nb_session];
    GtkWidget *session_next_meeting[nb_session];
    GtkWidget *entry_next_meeting[nb_session];
    GtkWidget *session_attach_button[nb_session];
    GtkWidget *text_session_note[nb_session];
    GtkTextBuffer *session_buffer[nb_session];
    GtkTextIter end[nb_session];

    char *session_date_char[nb_session];
    char *next_session_date_char[nb_session];

    SessionList *session_list = NULL;
    SessionEntries *saveSession[nb_session];

    /* ASSIGN VARIABLES */
    notebook = gtk_notebook_new();
    gtk_notebook_set_scrollable (GTK_NOTEBOOK(notebook), TRUE);
    grid_session_section = gtk_grid_new();


    if(nb_session>0){
        session_list = getSessionList(idFolder);
        setOnFirst(session_list);
    }


    for(session_cursor=0; session_cursor<nb_session; session_cursor++){
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

        session_next_meeting[session_cursor] = gtk_label_new("Prochain rendez-vous : ");
        entry_next_meeting[session_cursor] = gtk_entry_new();
        next_session_date_char[session_cursor] = get_date_UI(&session_list->current->session.nextSessionDate);
        gtk_entry_set_text(GTK_ENTRY(entry_next_meeting[session_cursor]), next_session_date_char[session_cursor]);
        free_info_UI(next_session_date_char[session_cursor]);

        save_button[session_cursor] = gtk_button_new_from_icon_name("document-save", GTK_ICON_SIZE_MENU);
        new_session_button[session_cursor] = gtk_button_new_from_icon_name("list-add", GTK_ICON_SIZE_MENU);
        session_attach_button[session_cursor] = gtk_button_new_from_icon_name("mail-attachment", GTK_ICON_SIZE_MENU);

        text_session_note[session_cursor] = gtk_text_view_new();
        session_buffer[session_cursor] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_session_note[session_cursor]));
        gtk_text_buffer_get_end_iter(session_buffer[session_cursor], &end[session_cursor]);
        gtk_text_buffer_insert(session_buffer[session_cursor], &end[session_cursor], session_list->current->session.observations, -1);
        gtk_text_view_set_buffer(GTK_TEXT_VIEW(text_session_note[session_cursor]), session_buffer[session_cursor]);

        gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_session_note[session_cursor]), 5);
        gtk_text_view_set_right_margin(GTK_TEXT_VIEW(text_session_note[session_cursor]), 5);
        gtk_text_view_set_top_margin(GTK_TEXT_VIEW(text_session_note[session_cursor]), 5);
        gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(text_session_note[session_cursor]), 5);

        setOnNext(session_list);
    }


    /* MANAGE GRID WHICH ORGANIZES THE SESSION SECTION */
    gtk_grid_set_row_spacing(GTK_GRID(grid_session_section), 0);
    gtk_container_add(GTK_CONTAINER(box), grid_session_section);


    /* ******************************** FIRST PART : SECTION TO ADD A NEW SESSION ************************************ */
    AddNewSessionStruct *newSessionStruct = (AddNewSessionStruct*) malloc(sizeof(AddNewSessionStruct));
    newSessionStruct->notebook = notebook;
    newSessionStruct->folderID = idFolder;

    if(nb_session == 0){
        addNewSessionUI(NULL, newSessionStruct, patient);
    }

    /* Manage to add a notebook */
    gtk_grid_attach(GTK_GRID(grid_session_section), notebook, GTK_ALIGN_START, GTK_ALIGN_CENTER, 1, 1);
    gtk_widget_set_hexpand(notebook, TRUE);
    gtk_widget_set_vexpand(notebook, TRUE);
    gtk_widget_set_halign(notebook, GTK_ALIGN_FILL);

    if(nb_session>0){
        setOnFirst(session_list);
        for(session_cursor=0; session_cursor<nb_session; session_cursor++){
            /* Manage the entry to add a title */
            gtk_grid_attach(GTK_GRID(grid_add_session[session_cursor]), session_title_new[session_cursor], GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
            gtk_widget_set_hexpand(session_title_new[session_cursor], FALSE);
            gtk_widget_set_vexpand(session_title_new[session_cursor], FALSE);
            gtk_widget_set_halign(session_title_new[session_cursor], GTK_ALIGN_START);

            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), entry_title_new[session_cursor], session_title_new[session_cursor], GTK_POS_BOTTOM, 1, 1);
            gtk_widget_set_hexpand(entry_title_new[session_cursor], FALSE);
            gtk_widget_set_vexpand(entry_title_new[session_cursor], FALSE);
            gtk_widget_set_halign(entry_title_new[session_cursor], GTK_ALIGN_START);

            /* Manage to display the date of the session */
            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), session_date_new[session_cursor], session_title_new[session_cursor], GTK_POS_RIGHT, 1, 1);
            gtk_widget_set_hexpand(session_date_new[session_cursor], FALSE);
            gtk_widget_set_vexpand(session_date_new[session_cursor], FALSE);
            gtk_widget_set_halign(session_date_new[session_cursor], GTK_ALIGN_START);

            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), entry_date_new[session_cursor], session_date_new[session_cursor], GTK_POS_BOTTOM, 1, 1);
            gtk_widget_set_hexpand(entry_date_new[session_cursor], FALSE);
            gtk_widget_set_vexpand(entry_date_new[session_cursor], FALSE);
            gtk_widget_set_halign(entry_date_new[session_cursor], GTK_ALIGN_START);

            /* Manage to display the next appointment */
            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), session_next_meeting[session_cursor], entry_date_new[session_cursor], GTK_POS_RIGHT, 1, 1);
            gtk_widget_set_hexpand(session_next_meeting[session_cursor], TRUE);
            gtk_widget_set_vexpand(session_next_meeting[session_cursor], FALSE);
            gtk_widget_set_halign(session_next_meeting[session_cursor], GTK_ALIGN_END);

            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), entry_next_meeting[session_cursor], session_next_meeting[session_cursor], GTK_POS_RIGHT, 8, 1);
            gtk_widget_set_hexpand(entry_next_meeting[session_cursor], FALSE);
            gtk_widget_set_vexpand(entry_next_meeting[session_cursor], FALSE);
            gtk_widget_set_halign(entry_next_meeting[session_cursor], GTK_ALIGN_START);

            /* Manage to display the save button */
            /*gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), save_button[session_cursor], entry_next_meeting[session_cursor], GTK_POS_TOP, 6, 1);
            gtk_widget_set_hexpand(save_button[session_cursor], FALSE);
            gtk_widget_set_vexpand(save_button[session_cursor], FALSE);
            gtk_widget_set_halign(save_button[session_cursor], GTK_ALIGN_END);*/

            /* Manage to display the new session button */
            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), new_session_button[session_cursor], entry_next_meeting[session_cursor], GTK_POS_TOP, 7, 1);
            gtk_widget_set_hexpand(new_session_button[session_cursor], FALSE);
            gtk_widget_set_vexpand(new_session_button[session_cursor], FALSE);
            gtk_widget_set_halign(new_session_button[session_cursor], GTK_ALIGN_END);
            g_signal_connect(GTK_BUTTON(new_session_button[session_cursor]), "clicked", G_CALLBACK(addNewSessionUI), newSessionStruct);


            /* Manage to display the save button */
            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), save_button[session_cursor], new_session_button[session_cursor], GTK_POS_RIGHT, 1, 1);
            gtk_widget_set_hexpand(save_button[session_cursor], FALSE);
            gtk_widget_set_vexpand(save_button[session_cursor], FALSE);
            gtk_widget_set_halign(save_button[session_cursor], GTK_ALIGN_END);

            saveSession[session_cursor] = (SessionEntries*) malloc(sizeof(SessionEntries));
            saveSession[session_cursor]->session = &session_list->current->session;
            saveSession[session_cursor]->origin = (int) session_list->current->session.idSession;
            saveSession[session_cursor]->sessionName = entry_title_new[session_cursor];
            saveSession[session_cursor]->sessionDate = entry_date_new[session_cursor];
            saveSession[session_cursor]->nextSessionDate = entry_next_meeting[session_cursor];
            saveSession[session_cursor]->observations = text_session_note[session_cursor];
            g_signal_connect(GTK_BUTTON(save_button[session_cursor]), "clicked", G_CALLBACK(saveSessionEntries), saveSession[session_cursor]);


            /* Manage the button to attach items */
            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), session_attach_button[session_cursor], entry_title_new[session_cursor], GTK_POS_BOTTOM, 1, 1);
            gtk_widget_set_hexpand(session_attach_button[session_cursor], FALSE);
            gtk_widget_set_vexpand(session_attach_button[session_cursor], FALSE);
            MediaType *mediaChooser = (MediaType *) malloc(sizeof(MediaType));
            mediaChooser->patient = patient;
            mediaChooser->mediaType = "attachment";
            g_signal_connect(GTK_BUTTON(session_attach_button[session_cursor]), "clicked", G_CALLBACK(launchFileChooser), mediaChooser);

            /* Manage the frame and its entry to add informations about the session */
            gtk_frame_set_label_align(GTK_FRAME(frame_session_note[session_cursor]), 0, (float)0.5);
            gtk_grid_attach_next_to(GTK_GRID(grid_add_session[session_cursor]), frame_session_note[session_cursor], session_attach_button[session_cursor], GTK_POS_RIGHT, 10, 3);
            gtk_widget_set_hexpand(frame_session_note[session_cursor], TRUE);
            gtk_widget_set_vexpand(frame_session_note[session_cursor], TRUE);


            gtk_container_add(GTK_CONTAINER(frame_session_note[session_cursor]), text_session_note[session_cursor]);
            gtk_widget_set_hexpand(text_session_note[session_cursor], TRUE);
            gtk_widget_set_vexpand(text_session_note[session_cursor], TRUE);

            gtk_notebook_append_page(GTK_NOTEBOOK(notebook), grid_add_session[session_cursor], gtk_label_new(session_list->current->session.sessionName));
            setOnNext(session_list);

        }
    }

}


/*!
 * \brief Allows to close the patient window and open the session window
 *
 * When the user click on a patient from the patient window, this function closes
 * the patient window and open the session window related to the patient selected.
 *
 * \param[in] window_id Window to be refresh and ID of the Patient concerned
 * \param[in] but Button pressed to launch the work view
*/
void launchWorkView(GtkWidget *but, Window_id *window_id){
    gtk_widget_destroy(window_id->window);
    setWorkWindow(window_id->patientID, window_id->folderID);
}

/*!
 * \brief Add an empty session when creating a new one
 *
 * When the current folder contains no session, or when the user wants to create
 * a new session, this function add an empty session to the notebook
 *
 * \param[in] but Button pressed to launch the work view
 * \param[in] notebook The notebook which contains the sessions
*/
void addNewSessionUI(GtkWidget *button, AddNewSessionStruct *newSessionStruct, Patient *patient){
    /* DECLARE VARIABLES */
    GtkWidget *notebook = newSessionStruct->notebook;
    Session *new_session = createEmptySession(newSessionStruct->folderID);
    GtkWidget *grid_add_session;
    GtkWidget *frame_session_note;

    GtkWidget *session_title_new;
    GtkWidget *entry_title_new;
    GtkWidget *session_date_new;
    GtkWidget *entry_date_new;
    GtkWidget *save_button;
    GtkWidget *session_next_meeting;
    GtkWidget *entry_next_meeting;
    GtkWidget *session_attach_button;
    GtkWidget *text_session_note;
    GtkTextBuffer *session_buffer;
    GtkTextIter end;

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

    session_next_meeting = gtk_label_new("Prochain rendez-vous : ");
    entry_next_meeting = gtk_entry_new();
    char *next_session_date_char = get_date_UI(&new_session->nextSessionDate);
    gtk_entry_set_text(GTK_ENTRY(entry_next_meeting), next_session_date_char);
    free_info_UI(next_session_date_char);

    save_button = gtk_button_new_from_icon_name("document-save", GTK_ICON_SIZE_MENU);
    session_attach_button = gtk_button_new_from_icon_name("mail-attachment", GTK_ICON_SIZE_MENU);

    text_session_note = gtk_text_view_new();
    session_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_session_note));
    gtk_text_buffer_get_end_iter(session_buffer, &end);
    gtk_text_buffer_insert(session_buffer, &end, new_session->observations, -1);
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(text_session_note), session_buffer);

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

    /* Manage to display the next appointment */
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), session_next_meeting, entry_date_new, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_hexpand(session_next_meeting, TRUE);
    gtk_widget_set_vexpand(session_next_meeting, FALSE);
    gtk_widget_set_halign(session_next_meeting, GTK_ALIGN_END);

    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), entry_next_meeting, session_next_meeting, GTK_POS_RIGHT, 8, 1);
    gtk_widget_set_hexpand(entry_next_meeting, FALSE);
    gtk_widget_set_vexpand(entry_next_meeting, FALSE);
    gtk_widget_set_halign(entry_next_meeting, GTK_ALIGN_START);

    /* Manage to display the save button */
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), save_button, entry_next_meeting, GTK_POS_TOP, 8, 1);
    gtk_widget_set_hexpand(save_button, FALSE);
    gtk_widget_set_vexpand(save_button, FALSE);
    gtk_widget_set_halign(save_button, GTK_ALIGN_END);

    SessionEntries *saveSession = (SessionEntries*) malloc(sizeof(SessionEntries));
    saveSession->session = new_session;
    saveSession->origin = (int) new_session->idSession;
    saveSession->sessionName = entry_title_new;
    saveSession->sessionDate = entry_date_new;
    saveSession->nextSessionDate = entry_next_meeting;
    saveSession->observations = text_session_note;
    g_signal_connect(GTK_BUTTON(save_button), "clicked", G_CALLBACK(saveSessionEntries), saveSession);

    /* Manage the button to attach items */
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), session_attach_button, entry_title_new, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(session_attach_button, FALSE);
    gtk_widget_set_vexpand(session_attach_button, FALSE);

    /* Manage the frame and its entry to add informations about the session */
    gtk_frame_set_label_align(GTK_FRAME(frame_session_note), 0, (float) 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), frame_session_note, session_attach_button, GTK_POS_RIGHT, 10, 3);
    gtk_widget_set_hexpand(frame_session_note, TRUE);
    gtk_widget_set_vexpand(frame_session_note, TRUE);

    gtk_container_add(GTK_CONTAINER(frame_session_note), text_session_note);
    gtk_widget_set_hexpand(text_session_note, TRUE);
    gtk_widget_set_vexpand(text_session_note, TRUE);

    char *new_session_name = get_new_session_name();
    gtk_notebook_insert_page(GTK_NOTEBOOK(notebook), grid_add_session, gtk_label_new(new_session_name), 0);
    free(new_session_name);

    //freeSession(new_session);
    gtk_widget_show_all(notebook);

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
