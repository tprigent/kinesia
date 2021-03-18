/*!
* \file editor_views.c
* \brief File with callback functions of the session view
*/


#include <gtk/gtk.h>
#include "work_view.h"
#include "home_view.h"
#include "editor_views.h"
#include "../controler/struct_to_UI.h"
#include "../controler/UI_to_struct.h"

/*!
 * \brief Set up the edit Folder dialog box
 *
 * Bi-choice dialog box: "Annuler" that does nothing and "Enregistrer" that saves data to Folder structure.
 *
 * This function sets the dialog box attributes (size, position, name)
 * and displays entries to edit or fill Folder structure.
 *
 * \param[in] folder Folder to be edited
 *
 * \todo active dynamic data once getFolder is done (lines to uncomment)
 * \todo do a setFolder if "Enregistrer" button is clicked
*/
void launchFolderEditor(Folder *folder){

    /* DECLARE VARIABLES */
    GtkWidget *dialog;
    GtkWidget *folder_name_label;
    GtkWidget *start_treatment_label;
    GtkWidget *pathology_label;
    GtkWidget *other_infos_label;

    GtkWidget *folder_name_entry;
    GtkWidget *start_treatment_entry;
    GtkWidget *pathology_entry;
    GtkWidget *other_infos_text;

    GtkTextIter end;
    GtkTextBuffer *other_infos_buffer;

    GtkWidget *content_area;

    GtkWidget *name_box;
    GtkWidget *treatment_box;
    GtkWidget *pathology_box;
    GtkWidget *infos_box;


    /* DECLARE ELEMENTS OF THE DIALOG BOX */
    folder_name_label = gtk_label_new ("Nom du dossier");
    start_treatment_label = gtk_label_new("Date de début du traitement");
    pathology_label = gtk_label_new("Pathologie");
    other_infos_label = gtk_label_new("Autres informations");

    folder_name_entry = gtk_entry_new();
    start_treatment_entry = gtk_entry_new();
    pathology_entry = gtk_entry_new();
    other_infos_text = gtk_text_view_new();
    other_infos_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(other_infos_text));
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(other_infos_text), 5);
    gtk_text_view_set_top_margin(GTK_TEXT_VIEW(other_infos_text), 5);

    // Entry constraints
    gtk_entry_set_max_length(GTK_ENTRY(folder_name_entry), 40);
    gtk_entry_set_max_length(GTK_ENTRY(start_treatment_entry), 10);
    gtk_entry_set_max_length(GTK_ENTRY(pathology_entry), 30);


    /* FILL THE ENTRIES */
    /*
    gtk_entry_set_text(GTK_ENTRY(folder_name_entry), folder->folderName);
    gtk_entry_set_text(GTK_ENTRY(start_treatment_entry), get_date_UI(&folder->startOfTreatment));
    gtk_entry_set_text(GTK_ENTRY(pathology_label), folder->pathology);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, folder->details, -1);
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(other_infos_text), buffer);
     */

    name_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    treatment_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    pathology_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    infos_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);



    /* CREATE THE DIALOG BOX */
    dialog = gtk_dialog_new_with_buttons ("Édition du dossier",NULL,GTK_DIALOG_MODAL,
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
    GtkWidget *frame_folder = NULL;
    frame_folder = gtk_frame_new("Dossier en cours");
    gtk_frame_set_label_align(GTK_FRAME(frame_folder), 0, 0.5);
    gtk_grid_attach(GTK_GRID(grid_dialog), frame_folder, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(frame_folder, TRUE);
    gtk_widget_set_vexpand(frame_folder, TRUE);

    GtkWidget *grid_folder = NULL;
    grid_folder = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(frame_folder), grid_folder);
    gtk_container_set_border_width(GTK_CONTAINER(grid_folder), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid_folder), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid_folder), 15);
    gtk_widget_set_hexpand(grid_folder, TRUE);
    gtk_widget_set_vexpand(grid_folder, TRUE);

    /* FILL THE DIALOG BOX */
    /* Name */
    gtk_box_pack_start(GTK_BOX(name_box), folder_name_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(name_box), folder_name_entry, FALSE, FALSE, 0);
    gtk_widget_set_halign(folder_name_label, GTK_ALIGN_START);
    gtk_grid_attach(GTK_GRID(grid_folder), name_box, GTK_ALIGN_START, GTK_ALIGN_START, 3, 1);
    gtk_widget_set_margin_bottom(name_box, 5);
    gtk_widget_set_hexpand(name_box, FALSE);
    gtk_widget_set_vexpand(name_box, TRUE);


    /* Start treatment date */
    gtk_box_pack_start(GTK_BOX(treatment_box), start_treatment_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(treatment_box), start_treatment_entry, FALSE, FALSE, 0);
    gtk_widget_set_halign(start_treatment_label, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_folder), treatment_box, name_box, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_margin_bottom(treatment_box, 5);
    gtk_widget_set_hexpand(treatment_box, FALSE);
    gtk_widget_set_vexpand(treatment_box, TRUE);


    /* Pathology name */
    gtk_box_pack_start(GTK_BOX(pathology_box), pathology_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pathology_box), pathology_entry, FALSE, FALSE, 0);
    gtk_widget_set_halign(pathology_label, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_folder), pathology_box, treatment_box, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_margin_bottom(pathology_box, 10);
    gtk_widget_set_hexpand(pathology_box, FALSE);
    gtk_widget_set_vexpand(pathology_box, FALSE);

    /* Other infos */
    gtk_box_pack_start(GTK_BOX(infos_box), other_infos_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(infos_box), other_infos_text, TRUE, TRUE, 0);
    gtk_widget_set_vexpand(other_infos_text, TRUE);
    gtk_widget_set_hexpand(other_infos_text, TRUE);
    gtk_widget_set_size_request(infos_box, 350,1);
    gtk_widget_set_halign(other_infos_label, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_folder), infos_box, treatment_box, GTK_POS_RIGHT, 2, 2);
    gtk_widget_set_margin_bottom(infos_box, 10);
    gtk_widget_set_hexpand(infos_box, TRUE);
    gtk_widget_set_vexpand(infos_box, TRUE);



    /* SETUP THE VIEW PARAMETERS */
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 5);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    gtk_widget_show_all(dialog);

    /* MANAGE THE USER ACTION */
    int result = gtk_dialog_run (GTK_DIALOG (dialog));
    /* Action on button */
    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT){
        strcpy(folder->folderName, gtk_entry_get_text(GTK_ENTRY(folder_name_entry)));
        strcpy(folder->pathology, gtk_entry_get_text(GTK_ENTRY(pathology_entry)));
        strcpy(folder->details, gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(other_infos_buffer)));
        folder->startOfTreatment.day = parseDate((char *)gtk_entry_get_text(GTK_ENTRY(start_treatment_entry)))->day;
        folder->startOfTreatment.month = parseDate((char *)gtk_entry_get_text(GTK_ENTRY(start_treatment_entry)))->month;
        folder->startOfTreatment.year = parseDate((char *)gtk_entry_get_text(GTK_ENTRY(start_treatment_entry)))->year;
        // TODO: setFolder(folder);

        gtk_widget_destroy(dialog);
    } else {
        gtk_widget_destroy(dialog);
    }
}

/*!
 * \brief Set up the edit Patient dialog box
 *
 * Bi-choice dialog box: "Annuler" that does nothing and "Enregistrer" that saves data to Patient structure.
 *
 * This function sets the dialog box attributes (size, position, name)
 * and displays entries to edit or fill Patient structure.
 *
 * More data is displayed than in the session view (all Patient anamnesis).
 *
 * \param[in] but_edit Edit button clicked to launch this view
 * \param[in] patient Patient to be edited
 *
 * \todo do a setPatient if "Enregistrer" button is clicked
*/
void launchPatientEditor(GtkWidget *but_edit, Patient_window *patient_window){


    /* GET INFO FROM PATIENT WINDOW STRUCT */
    Patient *patient = patient_window->patient;
    GtkWidget *window = patient_window->window;
    int origin = patient_window->origin;


    printPatient(patient, "before being edited");
    printf("\n\n**********TEST**********\n\n");

    /* DECLARE VARIABLES */
    char *mediaType = "profil";
    GtkWidget *dialog = NULL;
    GtkWidget *content_area = NULL;
    GtkWidget *name = NULL;
    GtkWidget *surname = NULL;
    GtkWidget *patient_photo = NULL;    //photo
    GtkWidget *birth = NULL;
    GtkWidget *gender = NULL;
    GtkWidget *job = NULL;
    GtkWidget *address = NULL;
    GtkWidget *postcode = NULL;
    GtkWidget *city = NULL;
    GtkWidget *number = NULL;
    GtkWidget *email = NULL;
    GtkWidget *patient_ssn = NULL;      //ssn
    GtkWidget *weight = NULL;
    GtkWidget *height = NULL;
    GtkWidget *first_consult = NULL;
    GtkWidget *patient_info = NULL;
    GtkWidget *name_entry = NULL;
    GtkWidget *surname_entry = NULL;
    GtkWidget *photo_button = NULL;
    GtkWidget *birth_entry = NULL;
    GtkWidget *gender_combo_box = NULL;
    GtkWidget *job_entry = NULL;
    GtkWidget *address_entry = NULL;
    GtkWidget *postcode_entry = NULL;
    GtkWidget *city_entry = NULL;
    GtkWidget *number_entry = NULL;
    GtkWidget *email_entry = NULL;
    GtkWidget *ssn_entry = NULL;
    GtkWidget *weight_entry = NULL;
    GtkWidget *height_entry = NULL;
    GtkWidget *first_consult_entry = NULL;
    GtkWidget *info_text = NULL;
    GtkTextBuffer *info_buffer = NULL;
    GtkTextIter start, end;



    /* DECLARE ELEMENTS OF THE DIALOG BOX */

    name_entry = gtk_entry_new();
    surname_entry = gtk_entry_new();
    birth_entry = gtk_entry_new();
    gender_combo_box = gtk_combo_box_text_new();
    job_entry = gtk_entry_new();
    address_entry = gtk_entry_new();
    postcode_entry = gtk_entry_new();
    city_entry = gtk_entry_new();
    number_entry = gtk_entry_new();
    email_entry = gtk_entry_new();
    ssn_entry = gtk_entry_new();
    weight_entry = gtk_entry_new();
    height_entry = gtk_entry_new();
    first_consult_entry = gtk_entry_new();
    info_text = gtk_text_view_new();

    // entry parameters
    gtk_entry_set_max_length(GTK_ENTRY(name_entry), 30);
    gtk_entry_set_max_length(GTK_ENTRY(surname_entry), 30);
    gtk_entry_set_max_length(GTK_ENTRY(birth_entry), 10);
    gtk_entry_set_max_length(GTK_ENTRY(job_entry), 10);
    gtk_entry_set_max_length(GTK_ENTRY(address_entry), 60);
    gtk_entry_set_max_length(GTK_ENTRY(postcode_entry), 5);
    gtk_entry_set_max_length(GTK_ENTRY(city_entry), 25);
    gtk_entry_set_max_length(GTK_ENTRY(number_entry), 11);
    gtk_entry_set_max_length(GTK_ENTRY(email_entry), 40);
    gtk_entry_set_max_length(GTK_ENTRY(ssn_entry), 27);
    gtk_entry_set_max_length(GTK_ENTRY(weight_entry), 10);
    gtk_entry_set_max_length(GTK_ENTRY(height_entry), 10);
    gtk_entry_set_max_length(GTK_ENTRY(first_consult_entry), 10);

    gtk_entry_set_input_purpose(GTK_ENTRY(name_entry), GTK_INPUT_PURPOSE_NAME);
    gtk_entry_set_input_purpose(GTK_ENTRY(surname_entry), GTK_INPUT_PURPOSE_NAME);
    gtk_entry_set_input_purpose(GTK_ENTRY(postcode_entry), GTK_INPUT_PURPOSE_DIGITS);
    gtk_entry_set_input_purpose(GTK_ENTRY(number_entry), GTK_INPUT_PURPOSE_PHONE);
    gtk_entry_set_input_purpose(GTK_ENTRY(email_entry), GTK_INPUT_PURPOSE_EMAIL);
    gtk_entry_set_input_purpose(GTK_ENTRY(ssn_entry), GTK_INPUT_PURPOSE_DIGITS);


    info_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(info_text));
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(info_text), 5);
    gtk_text_view_set_top_margin(GTK_TEXT_VIEW(info_text), 5);
    gtk_text_buffer_get_end_iter(info_buffer, &end);

    name = gtk_label_new("Prénom : ");
    gtk_entry_set_text(GTK_ENTRY(name_entry), patient->firstname);

    surname = gtk_label_new("Nom : ");
    gtk_entry_set_text(GTK_ENTRY(surname_entry), patient->name);

    patient_photo = gtk_label_new("Photo : ");

    birth = gtk_label_new("Date de naissance : ");
    char *patient_birth_char = get_date_UI(&patient->birthdate);
    gtk_entry_set_text(GTK_ENTRY(birth_entry), patient_birth_char);
    free_info_UI(patient_birth_char);

    gender = gtk_label_new("Sexe : ");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(gender_combo_box), NULL, "Femme");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(gender_combo_box), NULL, "Homme");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(gender_combo_box), NULL, "Autre");
    gtk_combo_box_set_active(GTK_COMBO_BOX(gender_combo_box), patient->gender);

    job = gtk_label_new("Profession : ");
    gtk_entry_set_text(GTK_ENTRY(job_entry), patient->job);

    address = gtk_label_new("Adresse : ");
    char *patient_adress_char = get_adress_UI(patient);
    gtk_entry_set_text(GTK_ENTRY(address_entry), patient_adress_char);
    free_info_UI(patient_adress_char);

    postcode = gtk_label_new("Code postal : ");
    gtk_entry_set_text(GTK_ENTRY(postcode_entry), patient->address.postCode);

    city = gtk_label_new("Ville : ");
    gtk_entry_set_text(GTK_ENTRY(city_entry), patient->address.city);

    number = gtk_label_new("N° de téléphone : ");
    gtk_entry_set_text(GTK_ENTRY(number_entry), patient->phone_number);

    email = gtk_label_new("e-mail : ");
    gtk_entry_set_text(GTK_ENTRY(email_entry), patient->mail_address);

    patient_ssn = gtk_label_new("N° de sécurité sociale : ");
    gtk_entry_set_text(GTK_ENTRY(ssn_entry), patient->ssn);

    weight = gtk_label_new("Poids : ");
    gtk_entry_set_text(GTK_ENTRY(weight_entry), patient->weight);

    height = gtk_label_new("Taille : ");
    gtk_entry_set_text(GTK_ENTRY(height_entry), patient->height);

    first_consult = gtk_label_new("Date de première consultation : ");
    char *patient_first_consult = get_date_UI(&patient->first_consultation);
    gtk_entry_set_text(GTK_ENTRY(first_consult_entry), patient_first_consult);
    free_info_UI(patient_first_consult);

    patient_info = gtk_label_new("Informations importantes : ");
    gtk_text_buffer_insert(info_buffer, &end, patient->global_pathologies, -1);
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(info_text), info_buffer);


    photo_button = gtk_button_new_from_icon_name("mail-attachment", GTK_ICON_SIZE_LARGE_TOOLBAR);

    g_signal_connect(GTK_BUTTON(photo_button), "clicked", G_CALLBACK(launchFileChooser), mediaType);

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
    frame_etat_civil = gtk_frame_new("État civil");
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
    gtk_grid_attach(GTK_GRID(grid_etat_civil), name, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_halign(name, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), name_entry, name, GTK_POS_BOTTOM, 1, 1);

    // Surname
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), surname, name, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_halign(surname, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), surname_entry, surname, GTK_POS_BOTTOM, 1, 1);

    // Birthdate
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), birth, name_entry, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_halign(birth, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), birth_entry, birth, GTK_POS_BOTTOM, 1, 1);

    // Gender
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), gender, surname_entry, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_halign(gender, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), gender_combo_box, gender, GTK_POS_BOTTOM, 1, 1);

    // Job
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), job, birth_entry, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_halign(job, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), job_entry, job, GTK_POS_BOTTOM, 1, 1);

    // Picture
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), patient_photo, gender_combo_box, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(patient_photo, TRUE);
    gtk_widget_set_vexpand(patient_photo, FALSE);
    gtk_widget_set_halign(patient_photo, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), photo_button, patient_photo, GTK_POS_BOTTOM, 1, 1);

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
    gtk_grid_attach(GTK_GRID(grid_contact), number, GTK_ALIGN_START, GTK_ALIGN_START, 2, 1);
    gtk_widget_set_halign(number, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), number_entry, number, GTK_POS_BOTTOM, 2, 1);

    // email adress
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), email, number_entry, GTK_POS_BOTTOM, 2, 1);
    gtk_widget_set_halign(email, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), email_entry, email, GTK_POS_BOTTOM, 2, 1);

    // Address
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), address, email_entry, GTK_POS_BOTTOM, 2, 1);
    gtk_widget_set_halign(address, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), address_entry, address, GTK_POS_BOTTOM, 2, 1);

    // Postcode
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), postcode, address_entry, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_halign(postcode, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), postcode_entry, postcode, GTK_POS_BOTTOM, 1, 1);

    // City
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), city, postcode, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_halign(city, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_contact), city_entry, city, GTK_POS_BOTTOM, 1, 1);


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
    gtk_grid_attach(GTK_GRID(grid_medical_info), height, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(height, FALSE);
    gtk_widget_set_vexpand(height, FALSE);
    gtk_widget_set_halign(height, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), height_entry, height, GTK_POS_BOTTOM, 1, 1);

    // Weight
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), weight, height, GTK_POS_RIGHT, 1, 1);
    gtk_widget_set_hexpand(weight, FALSE);
    gtk_widget_set_vexpand(weight, FALSE);
    gtk_widget_set_halign(weight, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), weight_entry, weight, GTK_POS_BOTTOM, 1, 1);

    // First consultation date
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), first_consult, height_entry, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_halign(first_consult, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), first_consult_entry, first_consult, GTK_POS_BOTTOM, 2, 1);

    // ssn
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), patient_ssn, first_consult_entry, GTK_POS_BOTTOM, 2, 1);
    gtk_widget_set_halign(patient_ssn, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), ssn_entry, patient_ssn, GTK_POS_BOTTOM, 2, 1);

    // Important information
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), patient_info, ssn_entry, GTK_POS_BOTTOM, 2, 1);
    gtk_widget_set_hexpand(patient_info, TRUE);
    gtk_widget_set_vexpand(patient_info, FALSE);
    gtk_widget_set_halign(patient_info, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), info_text, patient_info, GTK_POS_BOTTOM, 2, 1);
    gtk_widget_set_vexpand(info_text, TRUE);

    /* SETUP THE VIEW PARAMETERS */
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 5);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(dialog);


    /* MANAGE THE USER ACTION */
    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT){
        /* NAME */
        strcpy(patient->name, (char*)gtk_entry_get_text(GTK_ENTRY(surname_entry)));
        strcpy(patient->firstname, (char*)gtk_entry_get_text(GTK_ENTRY(name_entry)));

        /* BIRTHDAY */
        patient->birthdate.day = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(birth_entry)))->day;
        patient->birthdate.month = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(birth_entry)))->month;
        patient->birthdate.year = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(birth_entry)))->year;

        /* WEIGHT AND HEIGHT */
        strcpy(patient->weight, (char*)gtk_entry_get_text(GTK_ENTRY(weight_entry)));
        strcpy(patient->height, (char*)gtk_entry_get_text(GTK_ENTRY(height_entry)));
        //patient->weight = convertToInt((char*) gtk_entry_get_text(GTK_ENTRY(weight_entry)));
        //patient->height = convertToInt((char *) gtk_entry_get_text(GTK_ENTRY(height_entry)));

        /* FIRST CONSULTATION */
        patient->first_consultation.day = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(first_consult_entry)))->day;
        patient->first_consultation.month = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(first_consult_entry)))->month;
        patient->first_consultation.year = parseDate((char*) gtk_entry_get_text(GTK_ENTRY(first_consult_entry)))->year;

        /* SOCIAL SECURITY NUMBER */
        strcpy(patient->ssn, (char*) gtk_entry_get_text(GTK_ENTRY(ssn_entry)));

        /* CONTACT */
        strcpy(patient->phone_number, (char*) gtk_entry_get_text(GTK_ENTRY(number_entry)));
        strcpy(patient->mail_address, (char*) gtk_entry_get_text(GTK_ENTRY(email_entry)));

        /* GENDER */
        char *genderResult = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(gender_combo_box));
        if(strcmp(genderResult, "Homme") == 0){
            patient->gender = MAN;
        } else if (strcmp(genderResult, "Femme") == 0){
            patient->gender = WOMAN;
        } else {
            patient->gender = OTHER;
        }

        /* ADDRESS */
        parseAddress((char*) gtk_entry_get_text(GTK_ENTRY(address_entry)), &patient->address);
        strcpy(patient->address.city, (char*) gtk_entry_get_text(GTK_ENTRY(city_entry)));
        strcpy(patient->address.postCode, (char*) gtk_entry_get_text(GTK_ENTRY(postcode_entry)));
        //other infos

        /* JOB */
        strcpy(patient->job, (char*) gtk_entry_get_text(GTK_ENTRY(job_entry)));

        /* ADDITIONAL INFO */
        GtkTextBuffer *info_result_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(info_text));
        char *info_text_result;
        gtk_text_buffer_get_bounds(info_result_buffer, &start, &end);
        info_text_result = gtk_text_buffer_get_text (info_result_buffer, &start, &end, FALSE);
        strcpy(patient->global_pathologies, info_text_result);

        /* Print for debug */
        //printPatient(patient, "saving data from user entries");

        /* Save data in model */
        if(origin == 1){
            modifyPatient(patient);
        } else {
            addPatient(patient);
        }

        /* Reload the session window */
        gtk_widget_destroy(dialog);

        gtk_widget_destroy(window);

        if(origin == 1){
            setWorkWindow((int) patient->id);
        }else{
            setHomeWindow();
        }
        gtk_widget_destroy(dialog);

    } else {
        gtk_widget_destroy(dialog);
    }

}

/*!
 * \brief Set up the edit Patient dialog box with empty entries
 *
 * This function creates a patient with no attributes and pass it to launchPatientEditor
 * in order to create a new patient.
 *
 * \param[in] but_new button clicked to launch this view
 * \param[in] window Patient window
*/
void launchNewPatientEditor(GtkWidget *but_new, GtkWidget *window){
    Patient *patient = NULL;
    Address address;
    Date date;
    int id = getNbPatient();
    id++;

    allocateAddress(&address);
    allocatePatient(&patient);
    char *empty = " ";

    setDate(&date, 1, 1, 2000);
    setAddress(&address, empty, empty, empty, empty, empty);
    setPatient(patient, empty, empty, date, empty, 0, address, empty, empty, empty, empty, empty, empty, date, empty, id);

    /* CREATE STRUCT */
    Patient_window *patient_window = (Patient_window*) malloc(sizeof(Patient_window));
    patient_window->patient = patient;
    patient_window->window = window;
    patient_window->origin = 0;

    launchPatientEditor(but_new, patient_window);
}

void launchFileChooser(GtkWidget *photo_button, char *type){
    GtkWidget *dialog;
    Patient *patient = getPatient(1);                 //todo: make this dynamic
    dialog = gtk_file_chooser_dialog_new("Sélection du fichier",
                                      NULL,
                                      GTK_FILE_CHOOSER_ACTION_OPEN,
                                      "Annuler", GTK_RESPONSE_CANCEL,
                                      "Utiliser", GTK_RESPONSE_ACCEPT,
                                      NULL);

    gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    /* Action on button */
    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT){
        char *filename;
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (dialog));
        printf("%s\n", filename);
        copyToMedia(filename, patient , type);
        getProfileExtension(patient);
    }

    gtk_widget_destroy (dialog);
}

void launchDeletePatientWarning(GtkWidget *delete_button, Patient_window *patient_window){
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *title;
    GtkWidget *explanations;
    GtkWidget *symbol;

    dialog = gtk_dialog_new_with_buttons ("Suppression d'une fiche patient",NULL,GTK_DIALOG_MODAL,
                                          "Annuler",GTK_RESPONSE_REJECT,
                                          "Supprimer", GTK_RESPONSE_ACCEPT,NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    /* CREATE A GRID IN THE DIALOG BOX */
    GtkWidget *grid_dialog = NULL;
    grid_dialog = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(content_area), grid_dialog);
    gtk_container_set_border_width(GTK_CONTAINER(grid_dialog), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid_dialog), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid_dialog), 5);

    /* INITIATE MESSAGE ELEMENTS */
    title = gtk_label_new("Attention, vous êtes sur le point de supprimer la fiche patient de ...");

    /* FILL THE GRID */
    gtk_grid_attach(GTK_GRID(grid_dialog), title, GTK_ALIGN_START, GTK_ALIGN_START, 5, 1);
    gtk_widget_set_halign(title, TRUE);
    gtk_widget_set_hexpand(title, TRUE);


    /* SETUP THE VIEW PARAMETERS */
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 5);
    gtk_window_set_default_size(GTK_WINDOW(dialog), 300, 150);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(dialog);

    /* MANAGE THE USER ACTION */
    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT){
        // deletePatient(...);
        gtk_widget_destroy(dialog);
    } else {
        gtk_widget_destroy(dialog);
    }
}
