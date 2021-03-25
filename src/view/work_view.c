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
 * \param[in] session Session to be opened
*/
GtkWidget *setWorkWindow(int id_patient, Session *session, int session_type){

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
    window_id->session = session;
    window_id->session_type = session_type;
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

    boxPart[2] = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(boxPart[2]), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
    setStartMargin(boxPart[2]);
    setTopMargin(boxPart[2]);
    gtk_grid_attach_next_to(GTK_GRID(grid), boxPart[2],boxPart[1], GTK_POS_BOTTOM, 4, 1);
    gtk_widget_set_hexpand(boxPart[2], TRUE);
    gtk_widget_set_vexpand(boxPart[2], TRUE);

    /* Fill in the 3 spaces */
    fillPatientBox(window, boxPart[0], patient, window_id->session_type);
    fillFolderBox(boxPart[1]);
    fillSessionBox(window, boxPart[2], window_id->session, window_id->patientID, window_id->session_type);
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
 * \param[in] box Existing patient box
 * \param[in] patient Current Patient
 * \param[in] patient Patient opened
*/
void fillPatientBox(GtkWidget *window, GtkWidget *box, Patient *patient, int session_type){

    /* CREATE STRUCT TO PASS ARGUMENTS TO DIALOG BOX */
    Patient_window *patient_window = (Patient_window*) malloc(sizeof(Patient_window));
    patient_window->patient = patient;
    patient_window->window = window;
    patient_window->origin = 1;
    patient_window->session_type = session_type;


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
    gtk_box_pack_start(GTK_BOX(box), grid_left_section, TRUE, TRUE, 0);


    /* ******************************* FIRST PART : BUTTON "REVENIR A LA LISTE PATIENT" ******************************* */
    gtk_grid_attach(GTK_GRID(grid_left_section), back_button, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(back_button, FALSE);
    gtk_widget_set_vexpand(back_button, FALSE);
    gtk_widget_set_halign(back_button, GTK_ALIGN_START);
    g_signal_connect(GTK_BUTTON(back_button), "clicked", G_CALLBACK(launchHomeView), window);



    /* ************************** SECOND PART : SECTION WHICH CONTAINS PATIENT INFORMATION **************************** */
    /* Manage the frame global and its grid */
    gtk_frame_set_label_align(GTK_FRAME(frame_info), 0.5, 0.5);
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
    gtk_frame_set_label_align(GTK_FRAME(frame_etat_civil), 0, 0.5);
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
    gtk_frame_set_label_align(GTK_FRAME(frame_medical_info), 0, 0.5);
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
    gtk_frame_set_label_align(GTK_FRAME(frame_other_info), 0, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_info), frame_other_info, frame_medical_info, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(frame_other_info, TRUE);
    gtk_widget_set_vexpand(frame_other_info, FALSE);

    /* Section which fills other information */
    gtk_container_add(GTK_CONTAINER(frame_other_info), grid_other_info);
    gtk_widget_set_hexpand(grid_other_info, TRUE);
    gtk_grid_attach(GTK_GRID(grid_other_info), patient_other_info, GTK_ALIGN_CENTER, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(patient_other_info, TRUE);


    /* ******************************* THIRD PART : SECTION WHICH CONTAINS THE FOLDERS ******************************** */
    GtkWidget *folder_box = NULL;
    folder_box = gtk_scrolled_window_new(NULL, NULL);
    gtk_grid_attach_next_to(GTK_GRID(grid_left_section), folder_box, frame_info, GTK_POS_BOTTOM, 3, 1);
    gtk_widget_set_hexpand(folder_box, TRUE);
    gtk_widget_set_vexpand(folder_box, TRUE);

    GtkWidget *folder_grid = NULL;
    folder_grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(folder_box), folder_grid);

    int nb_folders = 3; // sere récupéré par une fonction
    int i;
    GtkWidget *folder_button[nb_folders];
    char *name_folder[nb_folders];
    char name_folder1[] = "#Dossier1"; // sera récupéré par une fonction
    char name_folder2[] = "#Dossier2";
    char name_folder3[] = "#Dossier3";
    name_folder[0] = name_folder1;
    name_folder[1] = name_folder2;
    name_folder[2] = name_folder3;

    folder_button[0] = gtk_button_new_with_label(name_folder[0]);
    gtk_grid_attach(GTK_GRID(folder_grid), folder_button[0], GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(folder_button[0], TRUE);
    for(i = 1; i < nb_folders; i++){
        folder_button[i] = gtk_button_new_with_label(name_folder[i]);
        gtk_grid_attach_next_to(GTK_GRID(folder_grid), folder_button[i], folder_button[i-1], GTK_POS_BOTTOM, 1, 1);
        gtk_widget_set_hexpand(folder_button[i], TRUE);
    }

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
void fillFolderBox(GtkWidget *box){

    /* Getting folder  ************************************************************** */
    Folder *folder = getFolder(1);
    /* ****************************************************************************** */

    /* Create a grid which contains the different elements of the folder ************ */
    GtkWidget *grid_part2 = NULL;
    grid_part2 = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(box), grid_part2, TRUE, TRUE, 0);
    /* ****************************************************************************** */

    /* Create a frame for the folder zone ******************************************* */
    GtkWidget *cadre_folder = NULL;
    cadre_folder = gtk_frame_new("Dossier");
    gtk_frame_set_label_align(GTK_FRAME(cadre_folder), 0.5, 0.5);
    gtk_grid_attach(GTK_GRID(grid_part2), cadre_folder, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(cadre_folder, TRUE);
    gtk_widget_set_vexpand(cadre_folder, TRUE);
    /* ****************************************************************************** */

    /* Create a grid to display all the elements ************************************ */
    GtkWidget *grid_folder = NULL;
    grid_folder = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(cadre_folder), grid_folder);
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
    char *indicator = get_indicator_files_UI(folder);
    attachments_label = gtk_label_new("Pièces jointes:    ");
    attachments_count = gtk_label_new(indicator);
    free_info_UI(indicator);
    gtk_box_pack_start(GTK_BOX(hbox_attachments), attachments_label, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(hbox_attachments), attachments_count, FALSE, FALSE, 0);

    /* BUTTON */
    GtkWidget *attachments_button = NULL;
    attachments_button = gtk_button_new_from_icon_name("mail-attachment", GTK_ICON_SIZE_MENU);
    gtk_widget_set_hexpand(attachments_button, FALSE);
    gtk_widget_set_vexpand(attachments_button, FALSE);
    gtk_box_pack_start(GTK_BOX(hbox_attachments), attachments_button, FALSE, FALSE, 0);
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
    GtkWidget *edit_folder_button = NULL;
    edit_folder_button = gtk_button_new_from_icon_name("text-editor", GTK_ICON_SIZE_MENU);
    g_signal_connect(GTK_BUTTON(edit_folder_button), "clicked", G_CALLBACK(launchFolderEditor), folder);
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
 * \param[in] box Existing Session box
 * \param[in] window Current window to enable refresh
 * \param[in] currentSession Current Session
 * \param[in] idPatient ID of the current Patient
*/
void fillSessionBox(GtkWidget *window, GtkWidget *box, Session *currentSession, int idPatient, int session_type){

    /* DECLARE VARIABLES */
    GtkWidget *grid_session_section = NULL;
    GtkWidget *grid_add_session = NULL;

    GtkWidget *frame_add_session = NULL;
    GtkWidget *frame_session_note = NULL;

    GtkWidget *notebook;
    GtkWidget *session_title_new = NULL;
    GtkWidget *entry_title_new = NULL;
    GtkWidget *session_date_new = NULL;
    GtkWidget *entry_date_new = NULL;
    GtkWidget *save_button = NULL;
    GtkWidget *new_session_button = NULL;
    GtkWidget *session_next_meeting = NULL;
    GtkWidget *entry_next_meeting = NULL;
    GtkWidget *session_attach_button = NULL;
    GtkWidget *text_session_note = NULL;
    GtkTextBuffer *session_buffer = NULL;
    GtkTextIter end;

    /* ASSIGN VARIABLES */
    notebook = gtk_notebook_new();
    grid_session_section = gtk_grid_new();
    grid_add_session = gtk_grid_new();

    frame_add_session = gtk_frame_new("Séance en cours");
    frame_session_note = gtk_frame_new("Observations");

    session_title_new = gtk_label_new("Titre :");
    entry_title_new = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_title_new), currentSession->sessionName);

    session_date_new = gtk_label_new("Date :");
    entry_date_new = gtk_entry_new();
    char *session_date_char = get_date_UI(&currentSession->sessionDate);
    gtk_entry_set_text(GTK_ENTRY(entry_date_new), session_date_char);
    free_info_UI(session_date_char);

    session_next_meeting = gtk_label_new("Prochain rendez-vous : ");
    entry_next_meeting = gtk_entry_new();
    char *next_session_date_char = get_date_UI(&currentSession->nextSessionDate);
    gtk_entry_set_text(GTK_ENTRY(entry_next_meeting), next_session_date_char);
    free_info_UI(next_session_date_char);

    save_button = gtk_button_new_from_icon_name("document-save", GTK_ICON_SIZE_MENU);
    new_session_button = gtk_button_new_from_icon_name("list-add", GTK_ICON_SIZE_MENU);
    session_attach_button = gtk_button_new_from_icon_name("mail-attachment", GTK_ICON_SIZE_MENU);

    text_session_note = gtk_text_view_new();
    session_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_session_note));
    gtk_text_buffer_get_end_iter(session_buffer, &end);
    gtk_text_buffer_insert(session_buffer, &end, currentSession->observations, -1);
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(text_session_note), session_buffer);

    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_session_note), 5);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(text_session_note), 5);
    gtk_text_view_set_top_margin(GTK_TEXT_VIEW(text_session_note), 5);
    gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(text_session_note), 5);


    /* MANAGE GRID WHICH ORGANIZES THE SESSION SECTION */
    gtk_grid_set_row_spacing(GTK_GRID(grid_session_section), 0);
    gtk_container_add(GTK_CONTAINER(box), grid_session_section);
    //gtk_box_pack_start(GTK_BOX(box), grid_session_section, TRUE, TRUE, 0);


    /* ******************************** FIRST PART : SECTION TO ADD A NEW SESSION ************************************ */
    /* Manage to add a notebook */
    gtk_grid_attach(GTK_GRID(grid_session_section), notebook, GTK_ALIGN_START, GTK_ALIGN_CENTER, 1, 1);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), session_date_new, gtk_label_new("Patients actifs"));
    gtk_widget_set_hexpand(notebook, TRUE);
    gtk_widget_set_vexpand(notebook, TRUE);
    gtk_widget_set_halign(notebook, GTK_ALIGN_FILL);

    /* Manage the frame and its grid to add a session */
    gtk_frame_set_label_align(GTK_FRAME(frame_add_session), 0.5, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_session_section), frame_add_session, notebook, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(frame_add_session, TRUE);
    gtk_widget_set_vexpand(frame_add_session, TRUE);
    gtk_widget_set_halign(frame_add_session, GTK_ALIGN_FILL);

    gtk_container_set_border_width(GTK_CONTAINER(grid_add_session), 0);
    gtk_grid_set_row_spacing(GTK_GRID(grid_add_session), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid_add_session), 5);
    gtk_container_add(GTK_CONTAINER(frame_add_session), grid_add_session);

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
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), save_button, entry_next_meeting, GTK_POS_TOP, 6, 1);
    gtk_widget_set_hexpand(save_button, FALSE);
    gtk_widget_set_vexpand(save_button, FALSE);
    gtk_widget_set_halign(save_button, GTK_ALIGN_END);

    /* Manage to display the new session button */
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), new_session_button, entry_next_meeting, GTK_POS_TOP, 8, 1);
    gtk_widget_set_hexpand(new_session_button, FALSE);
    gtk_widget_set_vexpand(new_session_button, FALSE);
    gtk_widget_set_halign(new_session_button, GTK_ALIGN_END);
    Window_id *window_id1 = (Window_id*) malloc(sizeof(Window_id));
    window_id1->window = window;
    window_id1->patientID = idPatient;
    window_id1->session = createEmptySession();
    window_id1->session_type = 0;
    g_signal_connect(GTK_BUTTON(new_session_button), "clicked", G_CALLBACK(launchWorkView), window_id1);


    /* Manage to display the save button */
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), save_button, new_session_button, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_hexpand(save_button, FALSE);
    gtk_widget_set_vexpand(save_button, FALSE);
    gtk_widget_set_halign(save_button, GTK_ALIGN_END);

    NewSessionEntries *saveSession = (NewSessionEntries*) malloc(sizeof(NewSessionEntries));
    saveSession->session = currentSession;
    saveSession->origin = session_type;
    saveSession->sessionName = entry_title_new;
    saveSession->sessionDate = entry_date_new;
    saveSession->nextSessionDate = entry_next_meeting;
    saveSession->observations = text_session_note;
    saveSession->window_id = window_id1;
    g_signal_connect(GTK_BUTTON(save_button), "clicked", G_CALLBACK(saveNewSession), saveSession);

    /* Manage to display the next appointment */
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), session_next_meeting, entry_date_new, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_hexpand(session_next_meeting, FALSE);
    gtk_widget_set_vexpand(session_next_meeting, FALSE);
    gtk_widget_set_halign(session_next_meeting, GTK_ALIGN_END);

    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), entry_next_meeting, session_next_meeting, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_hexpand(entry_next_meeting, FALSE);
    gtk_widget_set_vexpand(entry_next_meeting, FALSE);
    gtk_widget_set_halign(entry_next_meeting, GTK_ALIGN_START);

    /* Manage the button to attach items */
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), session_attach_button, entry_title_new, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(session_attach_button, FALSE);
    gtk_widget_set_vexpand(session_attach_button, FALSE);
    //gtk_widget_set_halign(session_attach_button, GTK_ALIGN_CENTER);

    /* Manage the frame and its entry to add informations about the session */
    gtk_frame_set_label_align(GTK_FRAME(frame_session_note), 0, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), frame_session_note, session_attach_button, GTK_POS_RIGHT, 5, 3);
    gtk_widget_set_hexpand(frame_session_note, TRUE);
    gtk_widget_set_vexpand(frame_session_note, TRUE);
    //gtk_widget_set_halign(frame_session_note, GTK_ALIGN_START);

    gtk_container_add(GTK_CONTAINER(frame_session_note), text_session_note);
    gtk_widget_set_hexpand(text_session_note, TRUE);
    gtk_widget_set_vexpand(text_session_note, TRUE);


    /* SECOND PART : SECTION TO DISPLAY OLD SESSIONS */

    /* DECLARE VARIABLES */

    int nb_session = getNbSession(1);
    int session_cursor;
    char *date[nb_session];
    char *nextDate[nb_session];
    SessionList *session_list = NULL;
    GtkWidget *session_notebook;
    GtkWidget *edit_button[nb_session];
    GtkWidget *date_label[nb_session];
    GtkWidget *nextDate_label[nb_session];
    GtkWidget *observations_label[nb_session];
    GtkWidget *session_date[nb_session];
    GtkWidget *session_nextDate[nb_session];
    GtkWidget *session_observations[nb_session];
    GtkWidget *session_grid[nb_session];
    Window_id *window_id[nb_session];


    /* ASSIGN VARIABLES */
    session_notebook = gtk_notebook_new();
    session_list = getSessionList(1);
    setOnFirst(session_list);

    for(session_cursor=0; session_cursor<nb_session; session_cursor++){
        edit_button[session_cursor] = gtk_button_new_from_icon_name("text-editor", GTK_ICON_SIZE_MENU);

        session_grid[session_cursor] = gtk_grid_new();
        gtk_grid_set_column_spacing(GTK_GRID(session_grid[session_cursor]), 5);
        gtk_container_set_border_width(GTK_CONTAINER(session_grid[session_cursor]), 0);

        date_label[session_cursor] = gtk_label_new("Date : ");
        date[session_cursor] = get_date_UI(&session_list->current->session.sessionDate);
        session_date[session_cursor] = gtk_label_new(date[session_cursor]);
        free(date[session_cursor]);

        nextDate_label[session_cursor] = gtk_label_new("Date du prochain rendez-vous : ");
        nextDate[session_cursor] = get_date_UI(&session_list->current->session.nextSessionDate);
        session_nextDate[session_cursor] = gtk_label_new(nextDate[session_cursor]);
        free(nextDate[session_cursor]);

        observations_label[session_cursor] = gtk_label_new("Observations : ");
        session_observations[session_cursor] = gtk_label_new(session_list->current->session.observations);

        window_id[session_cursor] = (Window_id*) malloc(sizeof(Window_id));
        window_id[session_cursor]->window = window;
        window_id[session_cursor]->session = &session_list->current->session;
        window_id[session_cursor]->patientID = idPatient;
        window_id[session_cursor]->session_type = 1;

        setOnNext(session_list);
    }

    //gtk_notebook_append_page(GTK_NOTEBOOK(session_notebook), session_grid, gtk_label_new("Patients actifs"));
    //gtk_notebook_append_page(GTK_NOTEBOOK(session_notebook), gtk_label_new("Fiches patient \narchivées \nici..."), gtk_label_new("Archives"));

    gtk_grid_attach_next_to(GTK_GRID(grid_session_section), session_notebook, frame_add_session, GTK_POS_BOTTOM, 1, 1);

    /* Loop to display all the other sessions */
    setOnFirst(session_list);
    for(session_cursor=1; session_cursor<nb_session+1; session_cursor++){
        gtk_notebook_append_page(GTK_NOTEBOOK(session_notebook), session_grid[session_cursor-1], gtk_label_new(session_list->current->session.sessionName));

        gtk_grid_attach(GTK_GRID(session_grid[session_cursor-1]), date_label[session_cursor-1], GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
        gtk_widget_set_halign(date_label[session_cursor-1], GTK_ALIGN_START);

        gtk_grid_attach_next_to(GTK_GRID(session_grid[session_cursor-1]), session_date[session_cursor-1], date_label[session_cursor-1], GTK_POS_RIGHT, 1, 1);
        gtk_widget_set_halign(session_date[session_cursor-1], GTK_ALIGN_START);

        gtk_grid_attach_next_to(GTK_GRID(session_grid[session_cursor-1]), nextDate_label[session_cursor-1], session_date[session_cursor-1], GTK_POS_RIGHT, 1, 1);
        gtk_widget_set_hexpand(nextDate_label[session_cursor-1], TRUE);
        gtk_widget_set_halign(nextDate_label[session_cursor-1], GTK_ALIGN_END);

        gtk_grid_attach_next_to(GTK_GRID(session_grid[session_cursor-1]), session_nextDate[session_cursor-1], nextDate_label[session_cursor-1], GTK_POS_RIGHT, 1, 1);
        gtk_widget_set_hexpand(session_nextDate[session_cursor-1], FALSE);
        gtk_widget_set_halign(session_nextDate[session_cursor-1], GTK_ALIGN_END);

        gtk_grid_attach_next_to(GTK_GRID(session_grid[session_cursor-1]), edit_button[session_cursor-1], session_nextDate[session_cursor-1], GTK_POS_RIGHT, 1, 1);
        gtk_widget_set_hexpand(edit_button[session_cursor-1], FALSE);
        gtk_widget_set_halign(edit_button[session_cursor-1], GTK_ALIGN_END);
        g_signal_connect(GTK_BUTTON(edit_button[session_cursor-1]), "clicked", G_CALLBACK(launchWorkView), window_id[session_cursor-1]);

        gtk_grid_attach_next_to(GTK_GRID(session_grid[session_cursor-1]), observations_label[session_cursor-1], date_label[session_cursor-1], GTK_POS_BOTTOM, 1, 1);
        gtk_widget_set_halign(observations_label[session_cursor-1], GTK_ALIGN_START);

        gtk_grid_attach_next_to(GTK_GRID(session_grid[session_cursor-1]), session_observations[session_cursor-1], observations_label[session_cursor-1], GTK_POS_RIGHT, 3, 1);
        gtk_widget_set_halign(session_observations[session_cursor-1], GTK_ALIGN_START);

        setOnNext(session_list);
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
    setWorkWindow(window_id->patientID, window_id->session, window_id->session_type);
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
