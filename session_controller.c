//
// Created by Théo Prigent on 08/02/2021.
//

#include <gtk/gtk.h>
#include "session_controller.h"
#include "connect_struct_UI.h"

void launchFolderEditor(){

    /* DECLARE VARIABLES */
    GtkWidget *dialog;
    GtkWidget *folder_name_label;
    GtkWidget *start_treatment_label;
    GtkWidget *pathology_label;
    GtkWidget *other_infos_label;
    GtkWidget *folder_name_entry;
    GtkWidget *start_treatment_entry;
    GtkWidget *pathology_entry;
    GtkWidget *other_infos_entry;
    GtkWidget *content_area;

    /* CREATE THE DIALOG BOX */
    dialog = gtk_dialog_new_with_buttons ("Édition du dossier",NULL,GTK_DIALOG_MODAL,
                                          "Annuler",GTK_RESPONSE_REJECT,
                                          "Enregistrer", GTK_RESPONSE_ACCEPT,NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    /* DECLARE ELEMENTS OF THE DIALOG BOX */
    folder_name_label = gtk_label_new ("Nom du dossier");
    start_treatment_label = gtk_label_new("Date de début du traitement");
    pathology_label = gtk_label_new("Pathologie");
    other_infos_label = gtk_label_new("Autres informations");

    folder_name_entry = gtk_entry_new();
    start_treatment_entry = gtk_entry_new();
    pathology_entry = gtk_entry_new();
    other_infos_entry = gtk_entry_new();

    /* FILL THE DIALOG BOX */
    gtk_container_add(GTK_CONTAINER(content_area), folder_name_label);
    gtk_container_add(GTK_CONTAINER(content_area), folder_name_entry);
    gtk_widget_set_margin_bottom(folder_name_entry, 5);
    gtk_container_add(GTK_CONTAINER(content_area), start_treatment_label);
    gtk_container_add(GTK_CONTAINER(content_area), start_treatment_entry);
    gtk_widget_set_margin_bottom(start_treatment_entry, 5);
    gtk_container_add(GTK_CONTAINER(content_area), pathology_label);
    gtk_container_add(GTK_CONTAINER(content_area), pathology_entry);
    gtk_widget_set_margin_bottom(pathology_entry, 5);
    gtk_container_add(GTK_CONTAINER(content_area), other_infos_label);
    gtk_container_add(GTK_CONTAINER(content_area), other_infos_entry);
    gtk_widget_set_margin_bottom(other_infos_entry, 10);

    /* SETUP THE VIEW PARAMETERS */
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 5);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(dialog);

    /* MANAGE THE USER ACTION */
    int result = gtk_dialog_run (GTK_DIALOG (dialog));
    switch (result)
    {
        case GTK_RESPONSE_ACCEPT:
            // TODO: enregistrer les nouvelles informations;
            break;
        default:
            break;
    }

    /* DESTROY DIALOG BOX */
    gtk_widget_destroy(dialog);

}

void launchPatientEditor(GtkWidget *but_edit, gpointer data){
    Patient *patient = data;

    /* DECLARE VARIABLES */
    GtkWidget *dialog = NULL;
    GtkWidget *content_area = NULL;
    GtkWidget *patient_name = NULL;     //name
    GtkWidget *name = NULL;
    GtkWidget *name_box = NULL;
    GtkWidget *patient_surname = NULL;  //surname
    GtkWidget *surname = NULL;
    GtkWidget *surname_box = NULL;
    GtkWidget *patient_photo = NULL;    //photo
    GtkWidget *patient_birth = NULL;    //birth
    GtkWidget *birth = NULL;
    GtkWidget *birth_box = NULL;
    GtkWidget *patient_job = NULL;      //job
    GtkWidget *job = NULL;
    GtkWidget *job_box = NULL;
    GtkWidget *patient_address = NULL;   //adress
    GtkWidget *address = NULL;
    GtkWidget *address_box = NULL;
    GtkWidget *patient_postcode = NULL; //postcode
    GtkWidget *postcode = NULL;
    GtkWidget *postcode_box = NULL;
    GtkWidget *patient_city = NULL;     //city
    GtkWidget *city = NULL;
    GtkWidget *city_box = NULL;
    GtkWidget *patient_number = NULL;   //number
    GtkWidget *number = NULL;
    GtkWidget *number_box = NULL;
    GtkWidget *patient_email = NULL;    //email
    GtkWidget *email = NULL;
    GtkWidget *email_box = NULL;
    GtkWidget *patient_ssn = NULL;      //ssn
    GtkWidget *patient_weight = NULL;   //weight
    GtkWidget *weight = NULL;
    GtkWidget *weight_box = NULL;
    GtkWidget *patient_height = NULL;   //height
    GtkWidget *height = NULL;
    GtkWidget *height_box = NULL;
    GtkWidget *patient_info = NULL;
    GtkWidget *name_entry = NULL;
    GtkWidget *surname_entry = NULL;
    GtkWidget *photo_button = NULL;
    GtkWidget *birth_entry = NULL;
    GtkWidget *job_entry = NULL;
    GtkWidget *address_entry = NULL;
    GtkWidget *postcode_entry = NULL;
    GtkWidget *city_entry = NULL;
    GtkWidget *number_entry = NULL;
    GtkWidget *email_entry = NULL;
    GtkWidget *ssn_entry = NULL;
    GtkWidget *weight_entry = NULL;
    GtkWidget *height_entry = NULL;
    GtkWidget *info_entry = NULL;


    /* DECLARE ELEMENTS OF THE DIALOG BOX */
    name = gtk_label_new("Prénom : ");
    patient_name = gtk_label_new(patient->name);
    name_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    surname = gtk_label_new("Nom : ");
    patient_surname = gtk_label_new(patient->firstname);
    surname_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    patient_photo = gtk_label_new("Photo : ");

    birth = gtk_label_new("Date de naissance : ");
    char *patient_birth_char = get_date_UI(&patient->birthdate);
    patient_birth = gtk_label_new(patient_birth_char);
    free_info_UI(patient_birth_char);
    birth_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    job = gtk_label_new("Profession : ");
    patient_job = gtk_label_new(patient->job);
    job_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    address = gtk_label_new("Adresse : ");
    char *patient_adress_char = get_adress_UI(patient);
    patient_address = gtk_label_new(patient_adress_char);
    free_info_UI(patient_adress_char);
    address_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    postcode = gtk_label_new("Code postal : ");
    patient_postcode = gtk_label_new(patient->address.postCode);
    postcode_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    city = gtk_label_new("Ville : ");
    patient_city = gtk_label_new(patient->address.city);
    city_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    number = gtk_label_new("N° de téléphone : ");
    patient_number = gtk_label_new(patient->phone_number);
    number_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    email = gtk_label_new("email : ");
    patient_email = gtk_label_new(patient->mail_address);
    email_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    patient_ssn = gtk_label_new("N° de sécurité sociale : ");

    weight = gtk_label_new("Poids : ");
    char *patient_weight_char = get_weight_UI(patient);
    patient_weight = gtk_label_new(patient_weight_char);
    free_info_UI(patient_weight_char);
    weight_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    height = gtk_label_new("Taille : ");
    char *patient_height_char = get_height_UI(patient);
    patient_height = gtk_label_new(patient_height_char);
    free_info_UI(patient_height_char);
    height_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    patient_info = gtk_label_new("Antécédents médicaux : ");
    photo_button = gtk_button_new_from_icon_name("mail-attachment", GTK_ICON_SIZE_LARGE_TOOLBAR);

    name_entry = gtk_entry_new();
    surname_entry = gtk_entry_new();
    birth_entry = gtk_entry_new();
    job_entry = gtk_entry_new();
    address_entry = gtk_entry_new();
    postcode_entry = gtk_entry_new();
    city_entry = gtk_entry_new();
    number_entry = gtk_entry_new();
    email_entry = gtk_entry_new();
    ssn_entry = gtk_entry_new();
    weight_entry = gtk_entry_new();
    height_entry = gtk_entry_new();
    info_entry = gtk_entry_new();


    /* CREATE THE DIALOG BOX */
    dialog = gtk_dialog_new_with_buttons ("Édition de la fiche patient",NULL,GTK_DIALOG_MODAL,
                                          "Annuler",GTK_RESPONSE_REJECT,
                                          "Enregistrer", GTK_RESPONSE_ACCEPT,NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));


    /* CREATE A GRID IN THE DIALOG BOX */
    GtkWidget *grid_dialog = NULL;
    grid_dialog = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(content_area), grid_dialog);
    gtk_container_set_border_width(GTK_CONTAINER(grid_dialog), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid_dialog), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid_dialog), 5);


    /* FRAME WHICH CONTAINS IDENTITY INFORMATION */
    GtkWidget *frame_etat_civil = NULL;
    frame_etat_civil = gtk_frame_new("Etat civil");
    gtk_frame_set_label_align(GTK_FRAME(frame_etat_civil), 0, 0.5);
    gtk_grid_attach(GTK_GRID(grid_dialog), frame_etat_civil, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(frame_etat_civil, TRUE);
    gtk_widget_set_vexpand(frame_etat_civil, FALSE);

    GtkWidget *grid_etat_civil = NULL;
    grid_etat_civil = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(frame_etat_civil), grid_etat_civil);
    gtk_container_set_border_width(GTK_CONTAINER(grid_etat_civil), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid_etat_civil), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid_etat_civil), 15);


    /* FILL THE IDENTITY INFORMATION */
    // Name
    gtk_grid_attach(GTK_GRID(grid_etat_civil), name_box, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(name_box, FALSE);
    gtk_widget_set_vexpand(name_box, FALSE);
    gtk_widget_set_halign(name_box, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(name_box), name, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(name_box), patient_name, FALSE, FALSE, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), name_entry, name_box, GTK_POS_BOTTOM, 1, 1);

    // Surname
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), surname_box, name_box, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_hexpand(surname_box, FALSE);
    gtk_widget_set_vexpand(surname_box, FALSE);
    gtk_widget_set_halign(surname_box, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(surname_box), surname, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(surname_box), patient_surname, FALSE, FALSE, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), surname_entry, surname_box, GTK_POS_BOTTOM, 1, 1);

    // Birthdate
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), birth_box, name_entry, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(surname_box, FALSE);
    gtk_widget_set_vexpand(surname_box, FALSE);
    gtk_widget_set_halign(surname_box, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(birth_box), birth, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(birth_box), patient_birth, FALSE, FALSE, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), birth_entry, birth_box, GTK_POS_BOTTOM, 1, 1);

    // Picture
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), patient_photo, surname_entry, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(patient_photo, TRUE);
    gtk_widget_set_vexpand(patient_photo, FALSE);
    gtk_widget_set_halign(patient_photo, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), photo_button, patient_photo, GTK_POS_BOTTOM, 1, 1);

    // Job
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), job_box, birth_entry, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(job_box, FALSE);
    gtk_widget_set_vexpand(job_box, FALSE);
    gtk_widget_set_halign(job_box, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(job_box), job, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(job_box), patient_job, FALSE, FALSE, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), job_entry, job_box, GTK_POS_BOTTOM, 1, 1);

    /* FRAME WHICH CONTAINS CONTACT INFORMATION */
    GtkWidget *frame_contact = NULL;
    frame_contact = gtk_frame_new("Contact ");
    gtk_frame_set_label_align(GTK_FRAME(frame_contact), 0, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), frame_contact, frame_etat_civil, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(frame_contact, TRUE);
    gtk_widget_set_vexpand(frame_contact, FALSE);

    GtkWidget *grid_contact = NULL;
    grid_contact = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(frame_contact), grid_contact);
    gtk_container_set_border_width(GTK_CONTAINER(grid_contact), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid_contact), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid_contact), 5);


    /* FILL THE CONTACT INFORMATION */
    // Phone number
    gtk_grid_attach(GTK_GRID(grid_contact), number_box, GTK_ALIGN_START, GTK_ALIGN_START, 2, 1);
    gtk_widget_set_hexpand(number_box, TRUE);
    gtk_widget_set_vexpand(number_box, FALSE);
    gtk_widget_set_halign(number_box, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(number_box), number, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(number_box), patient_number, FALSE, FALSE, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), number_entry, number_box, GTK_POS_BOTTOM, 2, 1);

    // email adress
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), email_box, number_entry, GTK_POS_BOTTOM, 2, 1);
    gtk_box_pack_start(GTK_BOX(email_box), email, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(email_box), patient_email, FALSE, FALSE, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), email_entry, email_box, GTK_POS_BOTTOM, 2, 1);

    // Adress
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), address_box, email_entry, GTK_POS_BOTTOM, 2, 1);
    gtk_box_pack_start(GTK_BOX(address_box), address, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(address_box), patient_address, FALSE, FALSE, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), address_entry, address_box, GTK_POS_BOTTOM, 2, 1);

    // Postcode
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), postcode_box, address_entry, GTK_POS_BOTTOM, 1, 1);
    gtk_box_pack_start(GTK_BOX(postcode_box), postcode, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(postcode_box), patient_postcode, FALSE, FALSE, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), postcode_entry, postcode_box, GTK_POS_BOTTOM, 1, 1);

    // City
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), city_box, postcode_box, GTK_POS_RIGHT, 1, 1);
    gtk_box_pack_start(GTK_BOX(city_box), city, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(city_box), patient_city, FALSE, FALSE, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), city_entry, city_box, GTK_POS_BOTTOM, 1, 1);


    /* FRAME WHICH CONTAINS MEDICAL INFORMATION */
    GtkWidget *frame_medical_info = NULL;
    frame_medical_info = gtk_frame_new("Informations médicales");
    gtk_frame_set_label_align(GTK_FRAME(frame_medical_info), 0, 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), frame_medical_info, frame_etat_civil, GTK_POS_RIGHT, 1, 2);
    gtk_widget_set_hexpand(frame_medical_info, TRUE);
    gtk_widget_set_vexpand(frame_medical_info, FALSE);

    GtkWidget *grid_medical_info = NULL;
    grid_medical_info = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(frame_medical_info), grid_medical_info);
    gtk_container_set_border_width(GTK_CONTAINER(grid_medical_info), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid_medical_info), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid_medical_info), 5);

    /* FILL THE MEDICAL INFORMATION */
    // Height
    gtk_grid_attach(GTK_GRID(grid_medical_info), height_box, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(height_box, FALSE);
    gtk_widget_set_vexpand(height_box, FALSE);
    gtk_widget_set_halign(height_box, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(height_box), height, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(height_box), patient_height, FALSE, FALSE, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), height_entry, height_box, GTK_POS_BOTTOM, 1, 1);

    // Weight
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), weight_box, height_box, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_hexpand(weight_box, FALSE);
    gtk_widget_set_vexpand(weight_box, FALSE);
    gtk_widget_set_halign(weight_box, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(weight_box), weight, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(weight_box), patient_weight, FALSE, FALSE, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), weight_entry, weight_box, GTK_POS_BOTTOM, 1, 1);

    // SSn
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), patient_ssn, height_entry, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(patient_ssn, TRUE);
    gtk_widget_set_vexpand(patient_ssn, FALSE);
    gtk_widget_set_halign(patient_ssn, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), ssn_entry, patient_ssn, GTK_POS_BOTTOM, 2, 1);

    // Important informations
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), patient_info, ssn_entry, GTK_POS_BOTTOM, 2, 1);
    gtk_widget_set_hexpand(patient_info, TRUE);
    gtk_widget_set_vexpand(patient_info, FALSE);
    gtk_widget_set_halign(patient_info, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), info_entry, patient_info, GTK_POS_BOTTOM, 2, 1);
    gtk_widget_set_vexpand(info_entry, TRUE);

    /* SETUP THE VIEW PARAMETERS */
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 5);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(dialog);

    /* MANAGE THE USER ACTION */
    int result = gtk_dialog_run (GTK_DIALOG (dialog));
    switch (result)
    {
        case GTK_RESPONSE_ACCEPT:
            // TODO: enregistrer les nouvelles informations;
            break;
        default:
            break;
    }

    /* DESTROY DIALOG BOX */
    gtk_widget_destroy(dialog);

}
