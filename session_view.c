//
// Created by julien on 02/02/2021.
//

#include "session_view.h"
#include "session_controller.h"
#include "connect_struct_UI.h"
#include "patient.h"
#include <gtk/gtk.h>
#include <gtk/gtklabel.h>


GtkWidget *setSessionWindow(){
    GtkWidget *window = NULL;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_activate_focus(GTK_WINDOW(window));
    gtk_window_set_title(GTK_WINDOW(window), "Kinesia");
    gtk_window_set_default_size(GTK_WINDOW(window), 1200, 720);
    gtk_window_maximize(GTK_WINDOW(window));
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    return window;
}

void setSessionEnvironment(GtkWidget *window){

    /* Création patient pour tests sur la lecture de structure ********/
    Patient *patient = (Patient*) malloc(sizeof(Patient));
    //Name
    patient->name = (char*) malloc(10*sizeof(char));
    strcpy(patient->name, "Claude");
    patient->firstname = (char*) malloc(10*sizeof(char));
    strcpy(patient->firstname, "François");
    //Birthdate
    patient->birthdate.day = 1;
    patient->birthdate.month = 2;
    patient->birthdate.year = 1939;
    //Job
    patient->job = (char*) malloc(10*sizeof(char));
    strcpy(patient->job, "Chanteur");
    //Height Weight
    patient->height = 170;
    patient->weight = 59;
    //Global pathologies
    patient->global_pathologies = (char*) malloc(100*sizeof(char));
    strcpy(patient->global_pathologies, "Souffre d'une maladie cardiaque\nEst diabétique...");
    //First consultation
    patient->first_consultation.day = 7;
    patient->first_consultation.month = 1;
    patient->first_consultation.year = 1960;
    //Phone number
    patient->phone_number = (char*) malloc(11*sizeof(char));
    strcpy(patient->phone_number, "0610472037");
    //email
    patient->mail_address = (char*) malloc(26*sizeof(char));
    strcpy(patient->mail_address, "claude.francois@gmail.com");
    //adress
    patient->address.number = (char*) malloc(3*sizeof(char));
    strcpy(patient->address.number, "46");
    patient->address.street = (char*) malloc(30*sizeof(char));
    strcpy(patient->address.street, "boulevard Exelmans");
    //postcode
    patient->address.postCode = (char*) malloc(5*sizeof(char));
    strcpy(patient->address.postCode, "75116");
    //city
    patient->address.city = (char*) malloc(15*sizeof(char));
    strcpy(patient->address.city, "Paris");
    /* ****************************************************************/

    Patient *patient2 = getPatient(1);

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
    gtk_widget_set_vexpand(boxPart[1], TRUE);

    boxPart[2] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    setStartMargin(boxPart[2]);
    setTopMargin(boxPart[2]);
    gtk_grid_attach_next_to(GTK_GRID(grid), boxPart[2],boxPart[1], GTK_POS_BOTTOM, 4, 1);
    gtk_widget_set_hexpand(boxPart[2], TRUE);
    gtk_widget_set_vexpand(boxPart[2], TRUE);

    /* Fill in the 3 spaces */
    createPatientInfoWindow(boxPart[0], patient2);
    createFolderInfoWindow(boxPart[1]);
    createSessionInfoWindow(boxPart[2]);
}

void createPatientInfoWindow(GtkWidget *box, Patient *patient){

    /* DECLARE VARIABLES */
    GtkWidget *frame_info = NULL;
    GtkWidget *frame_etat_civil = NULL;
    GtkWidget *frame_medical_info = NULL;
    GtkWidget *frame_other_info = NULL;

    GtkWidget *grid_left_section = NULL;
    GtkWidget *grid_info = NULL;
    GtkWidget *grid_etat_civil = NULL;
    GtkWidget *grid_medical_info = NULL;

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

    char * patient_name_char = get_name_UI(patient);
    char *patient_birth_char = get_date_UI(&patient->birthdate);
    char *patient_height_weight_char = get_height_weight_UI(patient);
    char * patient_first_consultation_char = get_first_consultation_UI(patient);

    /* ASSIGN VARIABLES */
    frame_info = gtk_frame_new("Informations patient");
    frame_etat_civil = gtk_frame_new("Etat civil");
    frame_medical_info = gtk_frame_new("Informations médicales");
    frame_other_info = gtk_frame_new("Informations importantes");

    grid_left_section = gtk_grid_new();
    grid_info = gtk_grid_new();
    grid_etat_civil = gtk_grid_new();
    grid_medical_info = gtk_grid_new();

    back_button = gtk_button_new_with_label("< Revenir à la liste");
    edit_button = gtk_button_new_from_icon_name("text-editor", GTK_ICON_SIZE_MENU);
    patient_photo_pixbuf = gdk_pixbuf_new_from_file("../photo_patients/claude.jpeg", NULL);
    patient_photo_pixbuf = gdk_pixbuf_scale_simple(patient_photo_pixbuf, 170, 250, GDK_INTERP_BILINEAR);
    patient_photo = gtk_image_new_from_pixbuf(GDK_PIXBUF(patient_photo_pixbuf));
    patient_name = gtk_label_new(patient_name_char);    free_info_UI(patient_name_char);
    patient_birth = gtk_label_new(patient_birth_char);  free_info_UI(patient_birth_char);
    patient_job = gtk_label_new(patient->job);
    patient_height_weight = gtk_label_new(patient_height_weight_char);  free_info_UI(patient_height_weight_char);
    patient_first_consultation = gtk_label_new(patient_first_consultation_char);    free_info_UI(patient_first_consultation_char);
    patient_other_info = gtk_label_new(patient->global_pathologies);


    /* MANAGE THE GRID WHICH ORGANIZES THE LEFT SECTION */
    gtk_grid_set_row_spacing(GTK_GRID(grid_left_section), 5);
    gtk_box_pack_start(GTK_BOX(box), grid_left_section, TRUE, TRUE, 0);


    /******************************** FIRST PART : BUTTON "REVENIR A LA LISTE PATIENT" ********************************/
    gtk_grid_attach(GTK_GRID(grid_left_section), back_button, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(back_button, FALSE);
    gtk_widget_set_vexpand(back_button, FALSE);
    gtk_widget_set_halign(back_button, GTK_ALIGN_START);


    /*************************** SECOND PART : SECTION WHICH CONTAINS PATIENT INFORMATION *****************************/
    /* Manage the frame global and its grid */
    gtk_frame_set_label_align(GTK_FRAME(frame_info), 0.5, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_left_section), frame_info, back_button, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(frame_info, TRUE);
    gtk_widget_set_vexpand(frame_info, TRUE);

    gtk_container_add(GTK_CONTAINER(frame_info), grid_info);
    gtk_container_set_border_width(GTK_CONTAINER(grid_info), 5);

    /* Button to edit information */
    g_signal_connect(GTK_BUTTON(edit_button), "clicked", G_CALLBACK(launchPatientEditor), patient);
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
    gtk_container_add(GTK_CONTAINER(frame_other_info), patient_other_info);


    /******************************** THIRD PART : SECTION WHICH CONTAINS THE FOLDERS *********************************/
    GtkWidget *folder_box = NULL;
    folder_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_left_section), folder_box, frame_info, GTK_POS_BOTTOM, 3, 1);
    gtk_widget_set_hexpand(folder_box, TRUE);
    gtk_widget_set_vexpand(folder_box, FALSE);

    int nb_folders = 3; // sere récupéré par une fonction
    int i = 0;
    GtkWidget *folder_button[nb_folders];
    char *name_folder[nb_folders];
    char name_folder1[] = "#Dossier1"; // sera récupéré par une fonction
    char name_folder2[] = "#Dossier2";
    char name_folder3[] = "#Dossier3";
    name_folder[0] = name_folder1;
    name_folder[1] = name_folder2;
    name_folder[2] = name_folder3;

    for(i =0; i < nb_folders; i++){
        folder_button[i] = gtk_button_new_with_label(name_folder[i]);
        gtk_box_pack_start(GTK_BOX(folder_box), folder_button[i], FALSE, FALSE, 0);
    }

}

void createFolderInfoWindow(GtkWidget *box){

    /* Create sample folder for debug *********************************************** */
    Folder *folder = (Folder*) malloc(sizeof(Folder));
    folder->folderName = "Entorse de la cheville";
    folder->startOfTreatment.year = 2021;
    folder->startOfTreatment.month = 03;
    folder->startOfTreatment.day = 05;
    folder->pathology = "Entorse";
    folder->details = "Informations supplémentaires (retour à la ligne à gérer)";
    folder->numberOfFiles = 5;
    folder->idFolder = 111;
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
    g_signal_connect(GTK_BUTTON(edit_folder_button), "clicked", G_CALLBACK(launchFolderEditor), NULL);
    gtk_widget_set_hexpand(edit_folder_button, FALSE);
    gtk_widget_set_vexpand(edit_folder_button, FALSE);
    gtk_box_pack_start(GTK_BOX(hbox_edit_folder), edit_folder_button, FALSE, FALSE, 0);

    /* ****************************************************************************** */

}

void createSessionInfoWindow(GtkWidget *box){

    /* DECLARE VARIABLES */
    GtkWidget *grid_session_section = NULL;
    GtkWidget *grid_add_session = NULL;

    GtkWidget *frame_add_session = NULL;
    GtkWidget *frame_session_note = NULL;

    GtkWidget *session_title_new = NULL;
    GtkWidget *entry_title_new = NULL;
    GtkWidget *session_next_meeting = NULL;
    GtkWidget *session_attach_button = NULL;
    GtkWidget *entry_session_note = NULL;

    /* ASSIGN VARIABLES */
    grid_session_section = gtk_grid_new();
    grid_add_session = gtk_grid_new();

    frame_add_session = gtk_frame_new("Séance en cours");
    frame_session_note = gtk_frame_new("Observations");

    session_title_new = gtk_label_new("Titre :");
    entry_title_new = gtk_entry_new();
    session_next_meeting = gtk_label_new("Prochain rendez-vous : 13/02/2020");
    session_attach_button = gtk_button_new_from_icon_name("mail-attachment", GTK_ICON_SIZE_MENU);
    entry_session_note = gtk_entry_new();


    /* MANAGE GRID WHICH ORGANIZES THE SESSION SECTION */
    gtk_grid_set_row_spacing(GTK_GRID(grid_session_section), 10);
    gtk_box_pack_start(GTK_BOX(box), grid_session_section, TRUE, TRUE, 0);


    /********************************* FIRST PART : SECTION TO ADD A NEW SESSION ************************************ */
    /* Manage the frame and its grid to add a session */
    gtk_frame_set_label_align(GTK_FRAME(frame_add_session), 0.5, 0.5);
    gtk_grid_attach(GTK_GRID(grid_session_section), frame_add_session, GTK_ALIGN_START, GTK_ALIGN_CENTER, 1, 1);
    gtk_widget_set_hexpand(frame_add_session, TRUE);
    gtk_widget_set_vexpand(frame_add_session, TRUE);
    gtk_widget_set_halign(frame_add_session, GTK_ALIGN_FILL);

    gtk_container_set_border_width(GTK_CONTAINER(grid_add_session), 5);
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

    /* Manage to display the next appointment */
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), session_next_meeting, entry_title_new, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_hexpand(session_next_meeting, FALSE);
    gtk_widget_set_vexpand(session_next_meeting, FALSE);
    gtk_widget_set_halign(session_next_meeting, GTK_ALIGN_END);

    /* Manage the button to attach items */
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), session_attach_button, entry_title_new, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(session_attach_button, FALSE);
    gtk_widget_set_vexpand(session_attach_button, FALSE);
    gtk_widget_set_halign(entry_title_new, GTK_ALIGN_START);

    /* Manage the frame and its entry to add informations about the session */
    gtk_frame_set_label_align(GTK_FRAME(frame_session_note), 0, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_add_session), frame_session_note, session_attach_button, GTK_POS_RIGHT, 1, 4);
    gtk_widget_set_hexpand(frame_session_note, TRUE);
    gtk_widget_set_vexpand(frame_session_note, TRUE);

    gtk_container_add(GTK_CONTAINER(frame_session_note), entry_session_note);
    gtk_widget_set_hexpand(entry_session_note, TRUE);
    gtk_widget_set_vexpand(entry_session_note, TRUE);


    /******************************** SECOND PART : SECTION TO DISPLAY OLD SESSIONS ************************************/
    /* Cette section n'estpas encore terminée */
    // 2ème séance
    GtkWidget *session2 = NULL; //Pour l'instant modélisé par bouton avant d'apprend a faire des menus déroulant
    session2 = gtk_button_new_with_label("Séance du 27/01/2021");
    gtk_grid_attach_next_to(GTK_GRID(grid_session_section), session2, frame_add_session, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(session2, TRUE);
    gtk_widget_set_vexpand(session2, FALSE);
    gtk_widget_set_halign(session2, GTK_ALIGN_FILL);

    // 1ère séance
    GtkWidget *session1 = NULL; //Pour l'instant modélisé par bouton avant d'apprend a faire des menus déroulant
    session1 = gtk_button_new_with_label("Séance du 12/01/2021");
    gtk_grid_attach_next_to(GTK_GRID(grid_session_section), session1, session2, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(session1, TRUE);
    gtk_widget_set_vexpand(session1, FALSE);
    gtk_widget_set_halign(session1, GTK_ALIGN_FILL);
    /* ****************************************************************************** */

}


/* HELPERS */

void setStartMargin(GtkWidget *widget){
    gtk_widget_set_margin_start(widget, 5);
}

void setTopMargin(GtkWidget *widget){
    gtk_widget_set_margin_top(widget, 5);
}

void setBottomMargin(GtkWidget *widget){
    gtk_widget_set_margin_bottom(widget, 5);
}
