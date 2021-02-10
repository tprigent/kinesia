//
// Created by julien on 02/02/2021.
//

#include <stdlib.h>
#include "gtk_functions.h"
#include "controller.h"
#include <gtk/gtk.h>


void setMainWindow(GtkWidget *window){
    gtk_window_set_title(GTK_WINDOW(window), "Kinesia");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 600);
    gtk_window_maximize(GTK_WINDOW(window));
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

void createPatientInfoWindow(GtkWidget *box){
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
    gtk_grid_attach(GTK_GRID(grid_info), but_edit, GTK_ALIGN_END, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(but_edit, TRUE);
    gtk_widget_set_vexpand(but_edit, FALSE);
    gtk_widget_set_halign(but_edit, GTK_ALIGN_END);
    /* ************************************************** */

    /* Include the picture of the patient *****************/
    GtkWidget *photo = NULL;
    GdkPixbuf *photo2 = NULL;
    photo2 = gdk_pixbuf_new_from_file("./photo_patients/claude.jpeg", NULL);
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
    nom = gtk_label_new("Claude François");
    gtk_grid_attach(GTK_GRID(grid_etat_civil), nom, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(nom, TRUE);
    gtk_widget_set_vexpand(nom, FALSE);
    gtk_widget_set_halign(nom, GTK_ALIGN_CENTER);

    // Birthdate
    GtkWidget *dateN = NULL;
    dateN = gtk_label_new("1 février 1939");
    gtk_label_set_use_markup(GTK_LABEL(dateN), TRUE);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), dateN, nom, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(dateN, TRUE);
    gtk_widget_set_vexpand(dateN, FALSE);
    gtk_widget_set_halign(dateN, GTK_ALIGN_CENTER);

    // Profession
    GtkWidget *profession = NULL;
    profession = gtk_label_new("Chanteur");
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
    poids_taille = gtk_label_new("59 kg    ;   1.70m");
    gtk_grid_attach(GTK_GRID(grid_medical_info), poids_taille, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(poids_taille, TRUE);
    gtk_widget_set_vexpand(poids_taille, FALSE);
    gtk_widget_set_halign(poids_taille, GTK_ALIGN_CENTER);

    // num de secu
    GtkWidget *num_secu = NULL;
    num_secu = gtk_label_new("N° de sécurité sociale");
    gtk_label_set_use_markup(GTK_LABEL(num_secu), TRUE);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), num_secu, poids_taille, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(num_secu, TRUE);
    gtk_widget_set_vexpand(num_secu, FALSE);
    gtk_widget_set_halign(num_secu, GTK_ALIGN_CENTER);
    /* ************************************************** */

    /* Frame which contains important informations ********/
    GtkWidget *frame_important_info = NULL;
    frame_important_info = gtk_frame_new("Informations importantes");
    gtk_frame_set_label_align(GTK_FRAME(frame_important_info), 0, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_info), frame_important_info, frame_medical_info, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(frame_important_info, TRUE);
    gtk_widget_set_vexpand(frame_important_info, FALSE);

    GtkWidget *label_imp_info = NULL;
    label_imp_info = gtk_label_new("Informations médicales particulières \nPar exemple maladie cardiaque/diabète...");
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
    folder_title = gtk_label_new("<big><b>** CURRENT FOLDER **</b></big>");   //TODO: make this text dynamic
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
    folder_start_treatment = gtk_label_new("Début de traitement: ");
    folder_date = gtk_label_new("xx/xx/xxxx");              //TODO: make this text dynamic
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
    folder_pathology_name = gtk_label_new("pathology name"); //TODO: make this text dynamic
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
    folder_infos = gtk_label_new("<u>Autres informations</u> : ");
    gtk_label_set_use_markup(GTK_LABEL(folder_infos), TRUE);
    folder_infos_content = gtk_label_new("Suivi de type blablabla\nProtocole appliqué blablabla");
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
    attachments_label = gtk_label_new("Pièces jointes:    ");
    attachments_count = gtk_label_new("   (0)");                     //TODO: make this indicator dynamic
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

void setStartMargin(GtkWidget *widget){
    gtk_widget_set_margin_start(widget, 5);
}

void setTopMargin(GtkWidget *widget){
    gtk_widget_set_margin_top(widget, 5);
}