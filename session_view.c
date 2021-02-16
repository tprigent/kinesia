//
// Created by julien on 02/02/2021.
//

#include "session_view.h"
#include "session_controller.h"
#include "connect_struct_UI.h"
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
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    return window;
}

void setSessionEnvironment(GtkWidget *window){

    /* Création patient pour tests sur la lecture de structure ********/
    Patient *patient = (Patient*) malloc(sizeof(Patient));
    //Name
    patient->name = (char*) malloc(10*sizeof(char));
    strcpy(patient->name, "Claude");
    patient->forename = (char*) malloc(10*sizeof(char));
    strcpy(patient->forename, "François");
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
    patient->address.numMaison = (char*) malloc(3*sizeof(char));
    strcpy(patient->address.numMaison, "46");
    patient->address.rue = (char*) malloc(30*sizeof(char));
    strcpy(patient->address.rue, "boulevard Exelmans");
    //postcode
    patient->address.codePostal = (char*) malloc(5*sizeof(char));
    strcpy(patient->address.codePostal, "75116");
    //city
    patient->address.ville = (char*) malloc(15*sizeof(char));
    strcpy(patient->address.ville, "Paris");
    /* ****************************************************************/

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
    createPatientInfoWindow(boxPart[0], patient);
    createFolderInfoWindow(boxPart[1]);
    createSessionInfoWindow(boxPart[2]);
}

void createPatientInfoWindow(GtkWidget *box, Patient *patient){
    /* Create a grid to organize the information section **************************** */
    GtkWidget *grid_part1 = NULL;
    grid_part1 = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid_part1), 5);
    gtk_box_pack_start(GTK_BOX(box), grid_part1, TRUE, TRUE, 0);
    /* ****************************************************************************** */

    /* first part : button "revenir liste patient" ********************************** */
    GtkWidget *but_back = NULL;
    but_back = gtk_button_new_with_label("< Revenir à la liste");
    gtk_grid_attach(GTK_GRID(grid_part1), but_back, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(but_back, FALSE);
    gtk_widget_set_vexpand(but_back, FALSE);
    gtk_widget_set_halign(but_back, GTK_ALIGN_START);
    /* ****************************************************************************** */


    /* Second part : section which contains patient informations ******************** */
    /* Creation of the frame */
    GtkWidget *cadre_info = NULL;
    cadre_info = gtk_frame_new("Informations patient");
    gtk_frame_set_label_align(GTK_FRAME(cadre_info), 0.5, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_part1), cadre_info, but_back, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(cadre_info, TRUE);
    gtk_widget_set_vexpand(cadre_info, TRUE);

    /* Creation of a grid to fill the frame ****************/
    GtkWidget *grid_info = NULL;
    grid_info = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(cadre_info), grid_info);
    gtk_container_set_border_width(GTK_CONTAINER(grid_info), 5);
    /* ************************************************** */

    /* Creation of a button to change information *********/
    GtkWidget *but_edit = NULL;
    but_edit = gtk_button_new_from_icon_name("text-editor", GTK_ICON_SIZE_MENU);
    g_signal_connect(GTK_BUTTON(but_edit), "clicked", G_CALLBACK(launchPatientEditor), patient);
    gtk_grid_attach(GTK_GRID(grid_info), but_edit, GTK_ALIGN_END, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(but_edit, TRUE);
    gtk_widget_set_vexpand(but_edit, FALSE);
    gtk_widget_set_halign(but_edit, GTK_ALIGN_END);
    /* ************************************************** */

    /* Include the picture of the patient *****************/
    GtkWidget *photo = NULL;
    GdkPixbuf *photo2 = NULL;
    photo2 = gdk_pixbuf_new_from_file("../photo_patients/claude.jpeg", NULL);
    photo2 = gdk_pixbuf_scale_simple(photo2, 170, 250, GDK_INTERP_BILINEAR);
    photo = gtk_image_new_from_pixbuf(GDK_PIXBUF(photo2));
    gtk_grid_attach_next_to(GTK_GRID(grid_info), photo, but_edit, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(photo, FALSE);
    gtk_widget_set_vexpand(photo, FALSE);
    gtk_widget_set_halign(photo, GTK_ALIGN_CENTER);
    /* ************************************************** */

    /* Frame which contains identity informations *********/
    GtkWidget *frame_etat_civil = NULL;
    frame_etat_civil = gtk_frame_new("Etat civil");
    gtk_frame_set_label_align(GTK_FRAME(frame_etat_civil), 0, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_info), frame_etat_civil, photo, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(frame_etat_civil, TRUE);
    gtk_widget_set_vexpand(frame_etat_civil, FALSE);

    GtkWidget *grid_etat_civil = NULL;
    grid_etat_civil = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(frame_etat_civil), grid_etat_civil);
    /* ************************************************** */

    /* Section which fills the identity informations ******/
    // Name
    GtkWidget *nom = NULL;
    char * name = get_name_UI(patient);
    nom = gtk_label_new(name);
    free_name_UI(name);
    gtk_grid_attach(GTK_GRID(grid_etat_civil), nom, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(nom, TRUE);
    gtk_widget_set_vexpand(nom, FALSE);
    gtk_widget_set_halign(nom, GTK_ALIGN_CENTER);

    // Birthdate
    GtkWidget *dateN = NULL;
    char *birth = get_date_UI(&patient->birthdate);
    dateN = gtk_label_new(birth);
    free_date_UI(birth);
    gtk_label_set_use_markup(GTK_LABEL(dateN), TRUE);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), dateN, nom, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(dateN, TRUE);
    gtk_widget_set_vexpand(dateN, FALSE);
    gtk_widget_set_halign(dateN, GTK_ALIGN_CENTER);

    // Profession
    GtkWidget *profession = NULL;
    char * job = get_job_UI(patient);
    profession = gtk_label_new(job);
    gtk_label_set_use_markup(GTK_LABEL(profession), TRUE);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), profession, dateN, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(profession, TRUE);
    gtk_widget_set_vexpand(profession, FALSE);
    gtk_widget_set_halign(profession, GTK_ALIGN_CENTER);
    /* ************************************************** */

    /* Frame which contains medical informations *********/
    GtkWidget *frame_medical_info = NULL;
    frame_medical_info = gtk_frame_new("Informations médicales");
    gtk_frame_set_label_align(GTK_FRAME(frame_medical_info), 0, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_info), frame_medical_info, frame_etat_civil, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(frame_medical_info, TRUE);
    gtk_widget_set_vexpand(frame_medical_info, FALSE);

    GtkWidget *grid_medical_info = NULL;
    grid_medical_info = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(frame_medical_info), grid_medical_info);
    /* ************************************************** */

    /* Section which fills the identity informations ******/
    // Weight and height
    GtkWidget *poids_taille = NULL;
    char *height_weight = get_height_weight_UI(patient);
    poids_taille = gtk_label_new(height_weight);
    free_height_weight_UI(height_weight);
    gtk_grid_attach(GTK_GRID(grid_medical_info), poids_taille, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(poids_taille, TRUE);
    gtk_widget_set_vexpand(poids_taille, FALSE);
    gtk_widget_set_halign(poids_taille, GTK_ALIGN_CENTER);

    // First consultation
    GtkWidget *first_consultation = NULL;
    char * first_consultation_char = get_first_consultation_UI(patient);
    first_consultation = gtk_label_new(first_consultation_char);
    gtk_label_set_use_markup(GTK_LABEL(first_consultation), TRUE);
    free_first_consultation_UI(first_consultation_char);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), first_consultation, poids_taille, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(first_consultation, TRUE);
    gtk_widget_set_vexpand(first_consultation, FALSE);
    gtk_widget_set_halign(first_consultation, GTK_ALIGN_CENTER);
    /* ************************************************** */

    /* Frame which contains important informations ********/
    GtkWidget *frame_important_info = NULL;
    frame_important_info = gtk_frame_new("Informations importantes");
    gtk_frame_set_label_align(GTK_FRAME(frame_important_info), 0, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_info), frame_important_info, frame_medical_info, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(frame_important_info, TRUE);
    gtk_widget_set_vexpand(frame_important_info, FALSE);

    GtkWidget *label_imp_info = NULL;
    char * global_pathologies = get_global_pathologies_UI(patient);
    label_imp_info = gtk_label_new(global_pathologies);
    gtk_container_add(GTK_CONTAINER(frame_important_info), label_imp_info);
    /* ************************************************** */

    /* ****************************************************************************** */


    /* Third part : section which contains the folders ***************************** */
    GtkWidget *vbox_folder = NULL;
    vbox_folder = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_part1), vbox_folder, cadre_info, GTK_POS_BOTTOM, 3, 1);
    gtk_widget_set_hexpand(vbox_folder, TRUE);
    gtk_widget_set_vexpand(vbox_folder, FALSE);

    int nb_folders = 3; // sere récupéré par une fonction
    int i = 0;
    GtkWidget *button_folder[nb_folders];
    char *name_folder[nb_folders];
    char name_folder1[] = "#Dossier1"; // sera récupéré parne fonction
    char name_folder2[] = "#Dossier2";
    char name_folder3[] = "#Dossier3";
    name_folder[0] = name_folder1;
    name_folder[1] = name_folder2;
    name_folder[2] = name_folder3;


    for(i =0; i < nb_folders; i++){
        button_folder[i] = gtk_button_new_with_label(name_folder[i]);
        gtk_box_pack_start(GTK_BOX(vbox_folder), button_folder[i], FALSE, FALSE, 0);
    }
    /* ****************************************************************************** */
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
    free_formatted_folder_title_UI(formatted_folder_title_UI);
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
    free_date_UI(start_of_treatment);
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
    free_indicator_files_UI(indicator);
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
    /* Create a grid to organize the session section ******************************** */
    GtkWidget *grid_part3 = NULL;
    grid_part3 = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid_part3), 10);
    gtk_box_pack_start(GTK_BOX(box), grid_part3, TRUE, TRUE, 0);
    /* ****************************************************************************** */

    /* First part : section to add a new session *********************************** */
    /* Creation of the frame to add a session */
    GtkWidget *add_session = NULL;
    add_session = gtk_frame_new("Séance en cours");
    gtk_frame_set_label_align(GTK_FRAME(add_session), 0.5, 0.5);
    gtk_grid_attach(GTK_GRID(grid_part3), add_session, GTK_ALIGN_START, GTK_ALIGN_CENTER, 1, 1);
    gtk_widget_set_hexpand(add_session, TRUE);
    gtk_widget_set_vexpand(add_session, TRUE);
    gtk_widget_set_halign(add_session, GTK_ALIGN_FILL);

    /* Creation of a grid to fill the add_session frame */
    GtkWidget *add_session_grid = NULL;
    add_session_grid = gtk_grid_new();
    gtk_container_set_border_width(GTK_CONTAINER(add_session_grid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(add_session_grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(add_session_grid), 5);
    gtk_container_add(GTK_CONTAINER(add_session), add_session_grid);

    /* Creation of an entry for the title */
    GtkWidget *title_label = NULL;
    title_label = gtk_label_new("Titre :");
    gtk_grid_attach(GTK_GRID(add_session_grid), title_label, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(title_label, FALSE);
    gtk_widget_set_vexpand(title_label, FALSE);
    gtk_widget_set_halign(title_label, GTK_ALIGN_START);

    GtkWidget *title_entry = NULL;
    title_entry = gtk_entry_new();
    gtk_grid_attach_next_to(GTK_GRID(add_session_grid), title_entry, title_label, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(title_entry, FALSE);
    gtk_widget_set_vexpand(title_entry, FALSE);
    gtk_widget_set_halign(title_entry, GTK_ALIGN_START);

    /* Creation of label to display the next appointment */
    GtkWidget *next_session_label = NULL;
    next_session_label = gtk_label_new("Prochain rendez-vous : 13/02/2020");
    gtk_grid_attach_next_to(GTK_GRID(add_session_grid), next_session_label, title_entry, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_hexpand(next_session_label, FALSE);
    gtk_widget_set_vexpand(next_session_label, FALSE);
    gtk_widget_set_halign(next_session_label, GTK_ALIGN_END);

    /* Creation of a button to attach items */
    GtkWidget *attach_button = NULL;
    attach_button = gtk_button_new_from_icon_name("mail-attachment", GTK_ICON_SIZE_MENU);
    gtk_grid_attach_next_to(GTK_GRID(add_session_grid), attach_button, title_entry, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(attach_button, FALSE);
    gtk_widget_set_vexpand(attach_button, FALSE);
    gtk_widget_set_halign(title_entry, GTK_ALIGN_START);

    /* Creation of a frame to add informations about the session */
    GtkWidget *session_note_frame = NULL;
    session_note_frame = gtk_frame_new("Observations");
    gtk_frame_set_label_align(GTK_FRAME(session_note_frame), 0, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(add_session_grid), session_note_frame, attach_button, GTK_POS_RIGHT, 1, 4);
    gtk_widget_set_hexpand(session_note_frame, TRUE);
    gtk_widget_set_vexpand(session_note_frame, TRUE);

    GtkWidget *session_note_entry = NULL;
    session_note_entry = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(session_note_frame), session_note_entry);
    gtk_widget_set_hexpand(session_note_entry, TRUE);
    gtk_widget_set_vexpand(session_note_entry, TRUE);
    /* ****************************************************************************** */


    /* Second part : section to search old sessions ********************************* */
    // 2ème séance
    GtkWidget *session2 = NULL; //Pour l'instant modélisé par bouton avant d'apprend a faire des menus déroulant
    session2 = gtk_button_new_with_label("Séance du 27/01/2021");
    gtk_grid_attach_next_to(GTK_GRID(grid_part3), session2, add_session, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(session2, TRUE);
    gtk_widget_set_vexpand(session2, FALSE);
    gtk_widget_set_halign(session2, GTK_ALIGN_FILL);

    // 1ère séance
    GtkWidget *session1 = NULL; //Pour l'instant modélisé par bouton avant d'apprend a faire des menus déroulant
    session1 = gtk_button_new_with_label("Séance du 12/01/2021");
    gtk_grid_attach_next_to(GTK_GRID(grid_part3), session1, session2, GTK_POS_BOTTOM, 1, 1);
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