/*!
* \file editor_views.c
* \brief File with callback functions to launch dialog boxes across the software
*/


#include <gtk/gtk.h>
#include <libgen.h>
#include <ctype.h>
#include "work_view.h"
#include "home_view.h"
#include "editor_views.h"
#include "../controller/struct_to_BDD_patient.h"
#include "../controller/struct_to_BDD_session.h"
#include "../controller/struct_to_BDD_folder.h"
#include "../controller/BDD_to_struct_folder.h"
#include "../controller/BDD_to_struct_session.h"
#include "../controller/display_helpers.h"
#include "../controller/UI_to_struct.h"
#include "../model/folder_manager.h"
#include "../model/session_manager.h"

/*!
 * \brief Set up the edit Folder dialog box
 *
 * Bi-choice dialog box: "Annuler" that does nothing and "Enregistrer" that saves data to Folder structure.
 *
 * This function sets the dialog box attributes (size, position, name)
 * and displays entries to edit or fill Folder structure.
 *
 * \param[in] button : button clicked to launch this view
 * \param[in] foldEditStruct : Structure containing infos needed to modify folder and reload the view
 * */
void launchFolderEditor(GtkWidget *button, FolderEditorStruct *foldEditStruct){

    /* DECLARE VARIABLES */
    Folder *folder = foldEditStruct->folder;
    int edit_new = foldEditStruct->edit_new;

    GtkWidget *dialog;
    GtkWidget *folder_name_label;
    GtkWidget *start_treatment_label;
    GtkWidget *pathology_label;
    GtkWidget *other_infos_label;

    GtkWidget *folder_name_entry;
    GtkWidget *start_treatment_entry;
    GtkWidget *pathology_entry;
    GtkWidget *other_infos_text;

    GtkWidget *calendar_start_treatment_button = NULL;

    GtkTextIter end;
    GtkTextBuffer *other_infos_buffer;

    GtkWidget *content_area;

    GtkWidget *name_box;
    GtkWidget *treatment_box;
    GtkWidget *pathology_box;
    GtkWidget *infos_box;
    GtkWidget *scroll_info_box = NULL;


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
    gtk_entry_set_text(GTK_ENTRY(folder_name_entry), folder->folderName);
    gtk_entry_set_text(GTK_ENTRY(start_treatment_entry), get_date_UI(&folder->startOfTreatment));
    gtk_entry_set_text(GTK_ENTRY(pathology_entry), folder->pathology);
    gtk_text_buffer_get_end_iter(other_infos_buffer, &end);
    gtk_text_buffer_insert(other_infos_buffer, &end, folder->details, -1);
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(other_infos_text), other_infos_buffer);

    /* BUTTON TO SELECT DATE */
    calendar_start_treatment_button = gtk_button_new_from_icon_name("x-office-calendar", GTK_ICON_SIZE_LARGE_TOOLBAR);
    g_signal_connect(GTK_BUTTON(calendar_start_treatment_button), "clicked", G_CALLBACK(launchCalendar), start_treatment_entry);


    name_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    treatment_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    pathology_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    infos_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    scroll_info_box = gtk_scrolled_window_new(NULL, NULL);


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
    gtk_frame_set_label_align(GTK_FRAME(frame_folder), 0, (float) 0.5);
    gtk_grid_attach(GTK_GRID(grid_dialog), frame_folder, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(frame_folder, TRUE);
    gtk_widget_set_vexpand(frame_folder, TRUE);

    GtkWidget *grid_folder = NULL;
    grid_folder = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(frame_folder), grid_folder);
    gtk_container_set_border_width(GTK_CONTAINER(grid_folder), 0);
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
    GtkWidget *treatment_grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(treatment_box), treatment_grid, FALSE, FALSE, 0);
    gtk_grid_attach(GTK_GRID(treatment_grid), start_treatment_label, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(treatment_grid), start_treatment_entry, start_treatment_label, GTK_POS_BOTTOM, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(treatment_grid), calendar_start_treatment_button, start_treatment_entry, GTK_POS_RIGHT, 1, 1);
    /*gtk_box_pack_start(GTK_BOX(treatment_box), start_treatment_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(treatment_box), start_treatment_entry, FALSE, FALSE, 0);
    gtk_widget_set_halign(start_treatment_label, GTK_ALIGN_START);*/
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
    gtk_box_pack_start(GTK_BOX(infos_box), scroll_info_box, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(scroll_info_box), other_infos_text);
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

    /* Action on button */

    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT){
        saveFolderEntries(folder, folder_name_entry, pathology_entry, other_infos_text, start_treatment_entry, edit_new);

        gtk_widget_destroy(dialog);

        int fullScreen = 0;
        if(gtk_window_is_maximized(GTK_WINDOW(foldEditStruct->window))==TRUE) fullScreen = 1;
        gtk_widget_destroy(foldEditStruct->window);
        setWorkWindow(fullScreen, (int) folder->idPatient, 0);
    } else {
        gtk_widget_destroy(dialog);
    }
}

/*!
 * \brief Call the folder editor with a new folder
 * *
 * This function creates a new folder with default attributes and calls
 * folder editor with this new folder struct
 *
 * \param[in] button : button clicked to launch this view
 * \param[in] idPatientCall : Structure containing infos needed to create Folder and reload the view
 *
*/
void launchNewFolderEditor(GtkWidget *button, IdPatientCallback *idPatientCall){
    Folder *folder = createEmptyFolder(idPatientCall->idPatient);
    FolderEditorStruct *foldEditStruct = (FolderEditorStruct*) malloc(sizeof(FolderEditorStruct));
    foldEditStruct->folder = folder;
    foldEditStruct->edit_new = 0;
    foldEditStruct->window = idPatientCall->window;


    launchFolderEditor(button, foldEditStruct);
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
 * \param[in] but_edit : button clicked to launch this view
 * \param[in] patient_window : Structure containing infos needed to modify Patient and reload the view
 *
*/
void launchPatientEditor(GtkWidget *but_edit, Patient_window *patient_window){

    /* GET INFO FROM PATIENT WINDOW STRUCT */
    Patient *patient = patient_window->patient;
    GtkWidget *window = patient_window->window;
    int origin = patient_window->origin;

    /* DECLARE VARIABLES */
    MediaType *photoChooser = (MediaType*) malloc(sizeof(MediaType));
    GtkWidget *dialog = NULL;
    GtkWidget *content_area = NULL;
    GtkWidget *name = NULL;
    GtkWidget *surname = NULL;
    GtkWidget *patient_photo = NULL;    //photo
    GtkWidget *birth = NULL;
    GtkWidget *calendar_birth_button = NULL;
    GtkWidget *gender = NULL;
    GtkWidget *job = NULL;
    GtkWidget *address = NULL;
    GtkWidget *postcode = NULL;
    GtkWidget *city = NULL;
    GtkWidget *number = NULL;
    GtkWidget *email = NULL;
    GtkWidget *patient_ssn = NULL;
    GtkWidget *weight = NULL;
    GtkWidget *height = NULL;
    GtkWidget *first_consult = NULL;
    GtkWidget *calendar_first_consult_button = NULL;
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
    GtkTextIter end;
    GtkWidget *text_box = NULL;



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

    photoChooser->patientID = (int) patient->id;
    photoChooser->mediaType = 0;
    photoChooser->isNewPatient = !origin;

    // entry parameters
    gtk_entry_set_max_length(GTK_ENTRY(name_entry), 30);
    gtk_entry_set_max_length(GTK_ENTRY(surname_entry), 30);
    gtk_entry_set_max_length(GTK_ENTRY(birth_entry), 10);
    gtk_entry_set_max_length(GTK_ENTRY(job_entry), 30);
    gtk_entry_set_max_length(GTK_ENTRY(address_entry), 100);
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
    text_box = gtk_scrolled_window_new(NULL, NULL);

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
    if(patient->gender == WOMAN) gtk_combo_box_set_active(GTK_COMBO_BOX(gender_combo_box), 0);
    else if (patient->gender == MAN) gtk_combo_box_set_active(GTK_COMBO_BOX(gender_combo_box), 1);
    else if (patient->gender == OTHER) gtk_combo_box_set_active(GTK_COMBO_BOX(gender_combo_box), 2);

    job = gtk_label_new("Profession : ");
    gtk_entry_set_text(GTK_ENTRY(job_entry), patient->job);

    address = gtk_label_new("Adresse : ");
    gtk_entry_set_text(GTK_ENTRY(address_entry), patient->address.street);

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
    calendar_birth_button = gtk_button_new_from_icon_name("x-office-calendar", GTK_ICON_SIZE_LARGE_TOOLBAR);
    calendar_first_consult_button = gtk_button_new_from_icon_name("x-office-calendar", GTK_ICON_SIZE_LARGE_TOOLBAR);

    g_signal_connect(GTK_BUTTON(photo_button), "clicked", G_CALLBACK(launchFileChooser), photoChooser);
    g_signal_connect(GTK_BUTTON(calendar_birth_button), "clicked", G_CALLBACK(launchCalendar), birth_entry);
    g_signal_connect(GTK_BUTTON(calendar_first_consult_button), "clicked", G_CALLBACK(launchCalendar), first_consult_entry);

    /* CREATE THE DIALOG BOX */
    dialog = gtk_dialog_new_with_buttons ("Édition de la fiche patient",NULL,GTK_DIALOG_MODAL,
                                          "Annuler",GTK_RESPONSE_REJECT,
                                          "Enregistrer", GTK_RESPONSE_ACCEPT,NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));


    /* CREATE A GRID IN THE DIALOG BOX */
    GtkWidget *grid_dialog = NULL;
    grid_dialog = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(content_area), grid_dialog);
    gtk_container_set_border_width(GTK_CONTAINER(grid_dialog), 0);
    gtk_grid_set_row_spacing(GTK_GRID(grid_dialog), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid_dialog), 5);


    /* FRAME WHICH CONTAINS IDENTITY INFORMATION */
    GtkWidget *frame_etat_civil = NULL;
    frame_etat_civil = gtk_frame_new("État civil");
    gtk_frame_set_label_align(GTK_FRAME(frame_etat_civil), 0, (float) 0.5);
    gtk_grid_attach(GTK_GRID(grid_dialog), frame_etat_civil, GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
    gtk_widget_set_hexpand(frame_etat_civil, TRUE);
    gtk_widget_set_vexpand(frame_etat_civil, FALSE);

    GtkWidget *grid_etat_civil = NULL;
    grid_etat_civil = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(frame_etat_civil), grid_etat_civil);
    gtk_container_set_border_width(GTK_CONTAINER(grid_etat_civil), 0);
    gtk_grid_set_row_spacing(GTK_GRID(grid_etat_civil), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid_etat_civil), 15);


    /* FILL THE IDENTITY INFORMATION */
    // Name
    gtk_grid_attach(GTK_GRID(grid_etat_civil), name, GTK_ALIGN_START, GTK_ALIGN_START, 2, 1);
    gtk_widget_set_halign(name, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), name_entry, name, GTK_POS_BOTTOM, 2, 1);

    // Surname
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), surname, name, GTK_POS_RIGHT, 2, 1);
    gtk_widget_set_halign(surname, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), surname_entry, surname, GTK_POS_BOTTOM, 2, 1);

    // Birthdate
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), birth, name_entry, GTK_POS_BOTTOM, 2, 1);
    gtk_widget_set_halign(birth, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), birth_entry, birth, GTK_POS_BOTTOM, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), calendar_birth_button, birth_entry, GTK_POS_RIGHT, 1, 1);

    // Gender
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), gender, surname_entry, GTK_POS_BOTTOM, 2, 1);
    gtk_widget_set_halign(gender, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), gender_combo_box, gender, GTK_POS_BOTTOM, 2, 1);

    // Job
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), job, birth_entry, GTK_POS_BOTTOM, 2, 1);
    gtk_widget_set_halign(job, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), job_entry, job, GTK_POS_BOTTOM, 2, 1);

    // Picture
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), patient_photo, gender_combo_box, GTK_POS_BOTTOM, 2, 1);
    gtk_widget_set_hexpand(patient_photo, TRUE);
    gtk_widget_set_vexpand(patient_photo, FALSE);
    gtk_widget_set_halign(patient_photo, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_etat_civil), photo_button, patient_photo, GTK_POS_BOTTOM, 2, 1);

    /* FRAME WHICH CONTAINS CONTACT INFORMATION */
    GtkWidget *frame_contact = NULL;
    frame_contact = gtk_frame_new("Contact ");
    gtk_frame_set_label_align(GTK_FRAME(frame_contact), 0, (float) 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), frame_contact, frame_etat_civil, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_hexpand(frame_contact, TRUE);
    gtk_widget_set_vexpand(frame_contact, FALSE);

    GtkWidget *grid_contact = NULL;
    grid_contact = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(frame_contact), grid_contact);
    gtk_container_set_border_width(GTK_CONTAINER(grid_contact), 0);
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
    gtk_frame_set_label_align(GTK_FRAME(frame_medical_info), 0, (float) 0.5);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), frame_medical_info, frame_etat_civil, GTK_POS_RIGHT, 1, 2);
    gtk_widget_set_hexpand(frame_medical_info, TRUE);
    gtk_widget_set_vexpand(frame_medical_info, FALSE);

    GtkWidget *grid_medical_info = NULL;
    grid_medical_info = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(frame_medical_info), grid_medical_info);
    gtk_container_set_border_width(GTK_CONTAINER(grid_medical_info), 0);
    gtk_grid_set_row_spacing(GTK_GRID(grid_medical_info), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid_medical_info), 5);

    /* FILL THE MEDICAL INFORMATION */
    // Height
    gtk_grid_attach(GTK_GRID(grid_medical_info), height, GTK_ALIGN_START, GTK_ALIGN_START, 2, 1);
    gtk_widget_set_hexpand(height, FALSE);
    gtk_widget_set_vexpand(height, FALSE);
    gtk_widget_set_halign(height, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), height_entry, height, GTK_POS_BOTTOM, 2, 1);

    // Weight
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), weight, height, GTK_POS_RIGHT, 2, 1);
    gtk_widget_set_hexpand(weight, FALSE);
    gtk_widget_set_vexpand(weight, FALSE);
    gtk_widget_set_halign(weight, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), weight_entry, weight, GTK_POS_BOTTOM, 2, 1);

    // First consultation date
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), first_consult, height_entry, GTK_POS_BOTTOM, 2, 1);
    gtk_widget_set_halign(first_consult, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), first_consult_entry, first_consult, GTK_POS_BOTTOM, 3, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), calendar_first_consult_button, first_consult_entry, GTK_POS_RIGHT, 1, 1);


    // ssn
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), patient_ssn, first_consult_entry, GTK_POS_BOTTOM, 2, 1);
    gtk_widget_set_halign(patient_ssn, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), ssn_entry, patient_ssn, GTK_POS_BOTTOM, 4, 1);

    // Important information
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), patient_info, ssn_entry, GTK_POS_BOTTOM, 4, 1);
    gtk_widget_set_hexpand(patient_info, TRUE);
    gtk_widget_set_vexpand(patient_info, FALSE);
    gtk_widget_set_halign(patient_info, GTK_ALIGN_START);
    gtk_grid_attach_next_to(GTK_GRID(grid_medical_info), text_box, patient_info, GTK_POS_BOTTOM, 4, 1);
    gtk_container_add(GTK_CONTAINER(text_box), info_text);
    gtk_widget_set_vexpand(info_text, TRUE);

    /* SETUP THE VIEW PARAMETERS */
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 5);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(dialog);


    /* MANAGE THE USER ACTION */
    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT){

        /* Save entries */
        savePatientEntries(patient, origin, surname_entry, name_entry, birth_entry, weight_entry,
                           height_entry, first_consult_entry, ssn_entry, number_entry, email_entry,
                           gender_combo_box, address_entry, city_entry, postcode_entry, job_entry,
                           info_text, end);

        /* Reload the session window */
        gtk_widget_destroy(dialog);
        gtk_widget_destroy(window);

        /* Choose view to display: work_view if existing, home_view if new Patient */
        if(origin == 1){
            int fullScreen = 0;
            if(gtk_window_is_maximized(GTK_WINDOW(window))==TRUE) fullScreen = 1;
            setWorkWindow(fullScreen, (int) patient->id, 0);
        }else{
            int fullScreen = 0;
            if(gtk_window_is_maximized(GTK_WINDOW(window))==TRUE) fullScreen = 1;
            setHomeWindow(0, fullScreen, 0);
        }
    } else {
        gtk_widget_destroy(dialog);
    }

    free((MediaType*) photoChooser);

}

/*!
 * \brief Call the patient editor with a new folder
 *
 * This function creates a new patient with default attributes and calls
 * patient editor with this new patient struct
 *
 * \param[in] button : button clicked to launch this view
 * \param[in] window : Current window to reload the view
 *
*/
void launchNewPatientEditor(GtkWidget *but_new, GtkWidget *window){
    Patient *patient = NULL;
    Address address;
    Date date;
    int id = getNbPatient(ALL);
    id++;

    allocateAddress(&address);
    allocatePatient(&patient);
    char *empty = "";

    setDate(&date, 1, 1, 1900);
    setAddress(&address, empty, empty, empty, empty);
    setPatient(patient, empty, empty, date, empty, 0, address, empty, empty, empty, empty, empty, empty, date, empty, id,0);

    /* CREATE STRUCT */
    Patient_window *patient_window = (Patient_window*) malloc(sizeof(Patient_window));
    patient_window->patient = patient;
    patient_window->window = window;
    patient_window->origin = 0;

    launchPatientEditor(but_new, patient_window);
}

/*!
 * \brief Set up the file chooser for either profile picture or attachments
 *
 * This function launches an explorer to select the concerned file and copy it in the right patient folder.
 *
 * \param[in] photo_button Button that launches the dialog box
 * \param[in] type Type of media: "profil" or "attachment"
*/
void launchFileChooser(GtkWidget *photo_button, MediaType *mediaChooser){
    GtkFileChooserNative *dialog;
    GtkFileFilter *filter;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;

    dialog = gtk_file_chooser_native_new("Ouvrir un fichier",
                                         NULL,
                                         action,
                                         "_Ouvrir",
                                         "_Annuler");
    /* Define filters */
    if (mediaChooser->mediaType == 0){
        filter = gtk_file_filter_new();
        gtk_file_filter_add_pattern(filter, "*.jpg");
        gtk_file_filter_add_pattern(filter, "*.jpeg");
        gtk_file_filter_add_pattern(filter, "*.JPEG");
        gtk_file_filter_add_pattern(filter, "*.png");
        gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);
    }

    /* Manage user action */
    if (gtk_native_dialog_run(GTK_NATIVE_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT){
        char *filename;
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        printf("%s\n", filename);
        if(mediaChooser->mediaType == 0){
            if(mediaChooser->isNewPatient){
                copyToMedia(filename, getFuturePatientId() , mediaChooser->folderID, "profil");
            } else {
                copyToMedia(filename, mediaChooser->patientID , mediaChooser->folderID, "profil");
            }
        } else {
            copyToMedia(filename, mediaChooser->patientID , mediaChooser->folderID, basename(filename));
            gtk_label_set_text(GTK_LABEL(mediaChooser->counterLabel), get_indicator_files_UI(mediaChooser->patientID, mediaChooser->folderID));
        }
    }
    gtk_native_dialog_destroy(GTK_NATIVE_DIALOG(dialog));

}

/*!
 * \brief Get the date selected on calendar and write it in selected entry
 *
 * This function gets the selected date in calendar and automatically write it
 * in the entry passed in parameter
 *
 * \param[in] calendar : the calendar used to select the date
 * \param[in] entry : the entry in which the date should be written
*/
void changeDateCallback(GtkWidget *calendar, GtkWidget *entry){
    Date date;
    unsigned int year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);

    date.year = (int) year;
    date.month = (int) month + 1;
    date.day = (int) day;
    char *date_char = get_date_UI(&date);

    gtk_entry_set_text(GTK_ENTRY(entry), date_char);
    free(date_char);
}

/*!
 * \brief Create a dialog with a calendar to select date
 *
 * This function displays a dialog box containing a calendar to select
 * a date for dates entries
 *
 * \param[in] button : button clicked to launch this view
 * \param[in] entry : the entry in which the date should be written
*/
void launchCalendar(GtkWidget *button, GtkWidget *entry){

    /* CREATE THE DIALOG BOX */
    GtkWidget *dialog = NULL;
    GtkWidget *content_area = NULL;
    dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Calendrier");
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    /* ADD A CALENDAR IN THE BOX */
    GtkWidget *calendar = gtk_calendar_new();
    gtk_container_add(GTK_CONTAINER(content_area), calendar);

    gtk_widget_show_all(dialog);

    g_signal_connect(GTK_CALENDAR(calendar), "day-selected", G_CALLBACK(changeDateCallback), entry);

    if (gtk_dialog_run (GTK_DIALOG (dialog))){
        gtk_widget_destroy(dialog);
    }

}

/*!
 * \brief Set up the warning when the user tries to delete/archive a Patient
 *
 * This function launches a dialog box to request user confirmation.
 *
 * \param[in] button : Button clicked to launch this dialog box
 * \param[in] warning : Struct WarningType containing Patient id, window and action type
*/
void launchPatientWarning(GtkWidget *button, WarningType *warning){
    GtkWidget *dialog = NULL;
    GtkWidget *content_area = NULL;
    GtkWidget *title = NULL;
    GtkWidget *explanations = NULL;
    GtkWidget *patientName = NULL;
    GdkPixbuf *symbolPixbuf = NULL;
    GtkWidget *symbol = NULL;
    Patient *patient = NULL;

    patient = getPatient((int) warning->patientID);
    if(warning->actionType == 0){
        dialog = gtk_dialog_new_with_buttons ("Suppression d'une fiche patient",NULL,GTK_DIALOG_MODAL,
                                              "Annuler",GTK_RESPONSE_REJECT,
                                              "Supprimer", GTK_RESPONSE_ACCEPT,NULL);
    } else if (patient->isArchived == 0){

        dialog = gtk_dialog_new_with_buttons ("Archivage d'une fiche patient",NULL,GTK_DIALOG_MODAL,
                                              "Annuler",GTK_RESPONSE_REJECT,
                                              "Archiver", GTK_RESPONSE_ACCEPT,NULL);
    } else {
        dialog = gtk_dialog_new_with_buttons ("Réactivation d'une fiche patient",NULL,GTK_DIALOG_MODAL,
                                              "Annuler",GTK_RESPONSE_REJECT,
                                              "Réactiver", GTK_RESPONSE_ACCEPT,NULL);
    }

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    /* CREATE A GRID IN THE DIALOG BOX */
    GtkWidget *grid_dialog = NULL;
    grid_dialog = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(content_area), grid_dialog);
    gtk_container_set_border_width(GTK_CONTAINER(grid_dialog), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid_dialog), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid_dialog), 5);

    /* INITIATE MESSAGE ELEMENTS */
    title = gtk_label_new(NULL);
    if(warning->actionType == 0){
        gtk_label_set_markup(GTK_LABEL(title), "<b><big>Attention, vous êtes sur le point de supprimer une fiche patient.</big></b>");
        explanations = gtk_label_new("Tous les dossiers et séances rattachées seront également supprimées.");
        symbolPixbuf = gdk_pixbuf_new_from_file_at_scale("../media/graphic-assets/delete_512.png", 128, 128, TRUE, NULL);
    } else if (patient->isArchived == 0){
        gtk_label_set_markup(GTK_LABEL(title),
                             "<b><big>Vous êtes sur le point d'archiver une fiche patient</big></b>");
        explanations = gtk_label_new("Confirmez-vous cette action ?");
        symbolPixbuf = gdk_pixbuf_new_from_file_at_scale("../media/graphic-assets/archive_512.png", 64, 64, TRUE,NULL);
    } else {
        gtk_label_set_markup(GTK_LABEL(title),
                             "<b><big>Vous êtes sur le point de réactiver une fiche patient</big></b>");
        explanations = gtk_label_new("Confirmez-vous cette action ?");
        symbolPixbuf = gdk_pixbuf_new_from_file_at_scale("../media/graphic-assets/undo_512.png", 64, 64, TRUE,NULL);
    }
    patientName = gtk_label_new(getNameFirstnamePatient((int) warning->patientID));
    symbol = gtk_image_new_from_pixbuf(symbolPixbuf);

    /* FILL THE GRID */
    gtk_grid_attach(GTK_GRID(grid_dialog), title, GTK_ALIGN_START, GTK_ALIGN_START, 5, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), explanations, title, GTK_POS_BOTTOM, 5,1);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), patientName, explanations, GTK_POS_BOTTOM, 5, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), GTK_WIDGET(symbol), patientName, GTK_POS_BOTTOM, 5,1);

    /* SETUP THE VIEW PARAMETERS */
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 5);
    gtk_window_set_default_size(GTK_WINDOW(dialog), 300, 125);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(dialog);

    /* MANAGE THE USER ACTION */
    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT){
        if(warning->actionType == 0){
            deletePatient((int) patient->id);
            deleteMediaFolder((int) patient->id);
        } else {
            if(patient->isArchived == 1) patient->isArchived = 0;
            else if(patient->isArchived == 0) patient->isArchived = 1;
            modifyPatient(patient);
        }
        /* Reload the session window */
        gtk_widget_destroy(dialog);

        int fullScreen = 0;
        if(gtk_window_is_maximized(GTK_WINDOW(warning->window))==TRUE) fullScreen = 1;
        gtk_widget_destroy(warning->window);
        setHomeWindow(0, fullScreen, 0);

    } else {
        gtk_widget_destroy(dialog);
    }

}

/*!
 * \brief Set up the settings dialog box
 *
 * Bi-choice dialog box: "Annuler" that does nothing and "Enregistrer" that saves changes.
 *
 * \param[in] button : Button clicked to launch this dialog box
 * \param[in] settings : structure containing infos needed to change css mode and reload windows
*/
void launchSettingsEditor(GtkWidget *button, SoftwareSettings *settings){

    /* DECLARE VARIABLES */
    int cssMode;

    GtkWidget *label_whiteMode = NULL;
    GtkWidget *label_darkMode = NULL;

    GtkWidget *dialog;
    GtkWidget *content_area = NULL;
    GtkWidget *grid_dialog = NULL;
    GdkPixbuf *whitePixbuf = NULL;
    GtkWidget *whiteImage= NULL;
    GdkPixbuf *darkPixbuf = NULL;
    GtkWidget *darkImage= NULL;
    GtkWidget *toggle_switch = NULL;
    GtkWidget *darkModeLabel = NULL;
    GtkWidget *explanationsLabel = NULL;
    GtkWidget *licenseLabel = NULL;
    GtkWidget *INSAlabel = NULL;
    GtkWidget *authorsLabel = NULL;

    /* ASSIGN VARIABLES */
    label_whiteMode = gtk_label_new("Mode clair :");
    label_darkMode = gtk_label_new("Mode sombre :");
    darkModeLabel = gtk_label_new("Mode sombre ");
    explanationsLabel = gtk_label_new("<i>Ce logiciel a été développé dans le cadre d'un projet de langage C de troisième année.</i>");
    licenseLabel = gtk_link_button_new_with_label("https://gitlab.insa-rennes.fr/tprigent/projet-logiciel-kine.git", "© Kinesia (2021)");
    INSAlabel = gtk_label_new("<i>INSA Rennes, département EII</i>");
    authorsLabel = gtk_label_new("<i>Paul Bertho, Salomé Guinaudeau, Julien Priam, Théo Prigent</i>");
    gtk_label_set_use_markup(GTK_LABEL(authorsLabel), TRUE);
    gtk_label_set_use_markup(GTK_LABEL(INSAlabel), TRUE);
    gtk_label_set_use_markup(GTK_LABEL(explanationsLabel), TRUE);

    grid_dialog = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid_dialog), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid_dialog), 5);

    toggle_switch = gtk_switch_new();
    if(settings->cssMode == 1) gtk_switch_set_active(GTK_SWITCH(toggle_switch), TRUE);

    whitePixbuf = gdk_pixbuf_new_from_file_at_scale("../media/graphic-assets/whiteMode.png", 400, 300, TRUE, NULL);
    whiteImage = gtk_image_new_from_pixbuf(whitePixbuf);
    darkPixbuf = gdk_pixbuf_new_from_file_at_scale("../media/graphic-assets/darkMode.png", 400, 300, TRUE, NULL);
    darkImage = gtk_image_new_from_pixbuf(darkPixbuf);

    /* CREATE THE DIALOG BOX */
    dialog = gtk_dialog_new_with_buttons ("Paramètres",NULL,GTK_DIALOG_MODAL,
                                          "Annuler",GTK_RESPONSE_REJECT,
                                          "Enregistrer", GTK_RESPONSE_ACCEPT,NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_container_add(GTK_CONTAINER(content_area), grid_dialog);

    /* MANAGE TO ORGANIZE THE VIEW */
    gtk_grid_attach(GTK_GRID(grid_dialog), label_whiteMode, GTK_ALIGN_CENTER, GTK_ALIGN_CENTER, 14, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), label_darkMode, label_whiteMode, GTK_POS_RIGHT, 14, 1);

    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), whiteImage, label_whiteMode, GTK_POS_BOTTOM, 14, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), darkImage, label_darkMode, GTK_POS_BOTTOM, 14, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), darkModeLabel, whiteImage, GTK_POS_BOTTOM, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), toggle_switch, darkModeLabel, GTK_POS_RIGHT, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), explanationsLabel, toggle_switch, GTK_POS_BOTTOM, 23, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), INSAlabel, explanationsLabel, GTK_POS_BOTTOM, 23, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), authorsLabel, INSAlabel, GTK_POS_BOTTOM, 23, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), licenseLabel, authorsLabel, GTK_POS_BOTTOM, 23, 1);

    gtk_widget_set_margin_top(explanationsLabel, 15);

    /* SETUP THE VIEW PARAMETERS */
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 5);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    gtk_widget_show_all(dialog);


    /* Action on button */
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT){

        /* GET INFO FROM SWITCH */
        if(gtk_switch_get_active(GTK_SWITCH(toggle_switch))) cssMode = 1;
        else cssMode = 0;

        gtk_widget_destroy(dialog);

        int fullScreen = 0;
        if(gtk_window_is_maximized(GTK_WINDOW(settings->window))==TRUE) fullScreen = 1;
        gtk_widget_destroy(settings->window);
        setHomeWindow(1, fullScreen, cssMode);
    } else {
        gtk_widget_destroy(dialog);
    }
}

/*!
 * \brief Set up the attachments dialog box
 *
 * Tri-choice dialog box: "Annuler" that does nothing, "Supprimer" that deletes selected
 * attachments and "Ouvrir" that opens the selected attachments
 *
 * \param[in] button : Button clicked to launch this dialog box
 * \param[in] attachmentProperties : structure containing infos needed to display the attachments
*/
void launchAttachmentListViewer(GtkWidget *button, MediaType *attachmentProperties){
    GtkWidget *dialog = NULL;
    GtkWidget *grid = NULL;
    GtkWidget *content_area = NULL;
    GtkWidget *noAttachmentLabel = NULL;
    GtkWidget *checkList[getNbOfAttachments(attachmentProperties->patientID, attachmentProperties->folderID)];
    char **fileList = getMediaDirectoryContent(attachmentProperties->patientID, attachmentProperties->folderID);
    int nbOfAttachments = getNbOfAttachments(attachmentProperties->patientID, attachmentProperties->folderID);

    if(nbOfAttachments == 0){
        dialog = gtk_dialog_new_with_buttons("Pièces-jointes",
                                             NULL, GTK_DIALOG_MODAL,
                                             "Annuler", GTK_RESPONSE_CANCEL, NULL);
    } else {
        dialog = gtk_dialog_new_with_buttons("Pièces-jointes",
                                             NULL, GTK_DIALOG_MODAL,
                                             "Annuler", GTK_RESPONSE_CANCEL,
                                             "Supprimer", GTK_RESPONSE_DELETE_EVENT,
                                             "Ouvrir", GTK_RESPONSE_ACCEPT, NULL);
    }

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    /* Setup the main grid */
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(content_area), grid);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

    /* Message if no attachment */
    if(nbOfAttachments == 0){
        noAttachmentLabel = gtk_label_new("<i>Il n'y a aucune pièce-jointe associée à ce dossier</i>");
        gtk_label_set_use_markup(GTK_LABEL(noAttachmentLabel), TRUE);
        gtk_grid_attach(GTK_GRID(grid), noAttachmentLabel, GTK_ALIGN_CENTER, GTK_ALIGN_CENTER, 1, 1);
        gtk_widget_set_hexpand(noAttachmentLabel, TRUE);
    }

    /* Setup the list */
    int i;
    for(i=0; i < nbOfAttachments; i++){
        checkList[i] = gtk_check_button_new_with_label(fileList[i]);
        if(i == 0) {
            gtk_grid_attach(GTK_GRID(grid), checkList[0], GTK_ALIGN_START, GTK_ALIGN_START, 1, 1);
        } else {
            gtk_grid_attach_next_to(GTK_GRID(grid), checkList[i], checkList[i-1], GTK_POS_BOTTOM, 1, 1);
        }
        gtk_widget_set_hexpand(checkList[i], TRUE);
        gtk_widget_set_size_request(checkList[i], 100, 20);
    }

    /* Show all elements */
    gtk_widget_show_all(grid);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);

    /* Action on button */
    int response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_ACCEPT){
        int j;
        for(j=0; j < nbOfAttachments; j++){
            if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkList[j]))){
                char *mediaPath = getFolderMediaPath(attachmentProperties->patientID, attachmentProperties->folderID);
                char *command = (char*) malloc(sizeof(char) * 200);

                /* Build open command with file path */
                if(strcmp(OS, "macOS") == 0) strcpy(command, "open ");
                if(strcmp(OS, "linux") == 0) strcpy(command, "xdg-open ");
                if(strcmp(OS, "Windows") == 0) strcpy(command, "start ");
                strcat(command, mediaPath);
                strcat(command, fileList[j]);

                system(command);

                free(mediaPath);
                free(command);
            }
        }
    } else if(response == GTK_RESPONSE_DELETE_EVENT) {
        int j;
        for(j=0; j<getNbOfAttachments(attachmentProperties->patientID, attachmentProperties->folderID); j++) {
            if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkList[j]))){
                char *mediaPath = getFolderMediaPath(attachmentProperties->patientID, attachmentProperties->folderID);
                char *filePath = (char *) malloc(sizeof(char) * 200);

                strcpy(filePath, mediaPath);
                strcat(filePath, fileList[j]);

                remove(filePath);
                gtk_label_set_text(GTK_LABEL(attachmentProperties->counterLabel), get_indicator_files_UI(attachmentProperties->patientID, attachmentProperties->folderID));

                free(mediaPath);
                free(filePath);
            }
        }
    }
    gtk_widget_destroy(dialog);
}

/*!
 * \brief Set up the warning dialog box for session of folder deletion
 *
 * Bi-choice dialog box: "Annuler" that does nothing and "Supprimer" which deletes
 * the selected element (can be a folder or a session)
 *
 * \param[in] button : Button clicked to launch this dialog box
 * \param[in] element : element to be deleted
*/
void launchDeleteElement(GtkWidget *button, DeleteElements *element){
    GtkWidget *dialog = NULL;
    GtkWidget *content_area = NULL;
    GtkWidget *title = NULL;
    GtkWidget *explanations = NULL;
    GtkWidget *elementName = NULL;
    GdkPixbuf *symbolPixbuf = NULL;
    GtkWidget *symbol = NULL;

    dialog = gtk_dialog_new_with_buttons ("Suppression d'un élément du dossier",NULL,GTK_DIALOG_MODAL,
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

    title = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(title), "<b><big>Attention, vous êtes sur le point de supprimer un élément.</big></b>");
    explanations = gtk_label_new("Toutes les informations relatives seront également supprimées.");
    symbolPixbuf = gdk_pixbuf_new_from_file_at_scale("../media/graphic-assets/delete_512.png", 128, 128, TRUE, NULL);
    if(element->isFolder){
        elementName = gtk_label_new(getFolder(element->folderID)->folderName);
    } else {
        elementName = gtk_label_new(getSession(element->sessionID)->sessionName);
    }
    symbol = gtk_image_new_from_pixbuf(symbolPixbuf);

    /* FILL THE GRID */
    gtk_grid_attach(GTK_GRID(grid_dialog), title, GTK_ALIGN_START, GTK_ALIGN_START, 5, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), explanations, title, GTK_POS_BOTTOM, 5,1);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), elementName, explanations, GTK_POS_BOTTOM, 5, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid_dialog), GTK_WIDGET(symbol), elementName, GTK_POS_BOTTOM, 5,1);

    /* SETUP THE VIEW PARAMETERS */
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 5);
    gtk_window_set_default_size(GTK_WINDOW(dialog), 300, 125);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT){
        if(element->isFolder){
            deleteFoler(element->folderID);
            gtk_widget_destroy(dialog);

            int fullScreen = 0;
            if(gtk_window_is_maximized(GTK_WINDOW(element->window))==TRUE) fullScreen = 1;
            gtk_widget_destroy(element->window);
            setWorkWindow(fullScreen, element->patientID, 0);

        } else {
            deleteSession(element->sessionID);
            gtk_notebook_remove_page(GTK_NOTEBOOK(element->notebook), gtk_notebook_get_current_page (GTK_NOTEBOOK(element->notebook)));
            gtk_widget_destroy(dialog);
            if(gtk_notebook_get_n_pages(GTK_NOTEBOOK(element->notebook)) == 0){
                int fullScreen = 0;
                if(gtk_window_is_maximized(GTK_WINDOW(element->window))==TRUE) fullScreen = 1;
                gtk_widget_destroy(element->window);
                setWorkWindow(fullScreen, element->patientID, element->folderID);
            }
        }

    } else {
        gtk_widget_destroy(dialog);
    }

}