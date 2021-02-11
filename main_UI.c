#include <gtk/gtk.h>
#include "main_UI.h"
#include "Structures.h"
#include "gtk_functions.h"



int main_UI(int argc, char **argv){

    /* Création patient pour tests sur la lecture de structure ********/
    Patient *patient = (Patient*) malloc(sizeof(Patient));
    //Name
    patient->name = (char*) malloc(10*sizeof(char));
    strcpy(patient->name, "François");
    patient->forename = (char*) malloc(10*sizeof(char));
    strcpy(patient->forename, "Claude");
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
    /* ****************************************************************/

    gtk_init(&argc, &argv);

    GtkWidget *window = NULL;
    //GtkWidget *table = NULL;
    GtkWidget *grid = NULL;

    /* create a new window, and set its attributes */

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    setMainWindow(window);

    /* Create a new table a place it in the window*/
    //table = gtk_table_new(4, 4, TRUE);
    //gtk_container_add(GTK_CONTAINER(window), table);
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Add 3 boxes to separate space */
    GtkWidget *boxPart[3];

    boxPart[0] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_grid_attach(GTK_GRID(grid), boxPart[0], GTK_ALIGN_START, GTK_ALIGN_START, 1, 6);
    gtk_widget_set_hexpand(boxPart[0], TRUE);
    gtk_widget_set_vexpand(boxPart[0], TRUE);

    boxPart[1] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid), boxPart[1],boxPart[0], GTK_POS_RIGHT, 4, 5);
    gtk_widget_set_hexpand(boxPart[1], TRUE);
    gtk_widget_set_vexpand(boxPart[1], TRUE);

    boxPart[2] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_grid_attach_next_to(GTK_GRID(grid), boxPart[2],boxPart[1], GTK_POS_BOTTOM, 4, 1);
    gtk_widget_set_hexpand(boxPart[2], TRUE);
    gtk_widget_set_vexpand(boxPart[2], TRUE);


    /* Call the functions which create the different parts of the window */
    createPatientInfoWindow(boxPart[0], patient);
    createFolderInfoWindow(boxPart[1]);
    createSessionInfoWindow(boxPart[2]);

    /* Display the window and begin the loop */
    gtk_widget_show_all(window);
    gtk_main();

    return EXIT_SUCCESS;
}