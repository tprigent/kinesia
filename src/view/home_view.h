/*!
* \file home_view.h
* \brief File to initiate the homepage view (calendar, patient list, ...)
*/

#ifndef LOGICIEL_KINE_PATIENT_VIEW_H
#define LOGICIEL_KINE_PATIENT_VIEW_H

#include <gtk/gtk.h>
#include "../model/structures.h"

/**
 * \brief Structure to pass a Session and a Patient to the callback
 *
 * This structure is used to pass many arguments in a callback function which has only
 * one argument.
*/
typedef struct {
    GtkWidget *window;      /**< Parent window to be reload after changes */
    int patientID;          /**< ID of the Patient to be edited */
    int folderID;           /**< ID of the Folder to be edited */
}Window_id;

/**
 * \brief Structure for all the work window parameters
 *
 * Useful to free all allocated elements at once.
*/
typedef struct {
    GtkWidget *window;         /**< Current window to allow work window to close it */
    Patient * patient;         /**< Patient selected */
    SessionList *sessionList;  /**< List containing all the recent Sessions of the Patient */
    Folder *folder;            /**< Folder to be open */
}WorkWindow;

/**
 * \brief Structure for search function
 *
 * This structure is used to pass many arguments in a callback function which has only
 * one argument.
*/
typedef struct {
    GtkWidget *notebook;    /**< Notebook to enable callback to add one tab */
    GtkWidget *entry;       /**< Search entry to process user request */
    GtkWidget *window;      /**< Parent window to be refreshed */
}SearchParam;

/**
 * \brief Structure for appointments
 *
 * This structure is used to pass many arguments in a callback function which has only
 * one argument.
*/
typedef struct {
    GtkWidget *vbox;        /**< Calendar grid (left part of the view) which is going to be updated */
    GtkWidget *title;       /**< Title to which the next elements will be attached */
    GtkWidget *window;      /**< Current window to allow child window to close it */
    GtkWidget *grid;        /**< Grid to which the calendar elements are going to be attached */
    int atLoad;             /**< Boolean parameter to determine which is the selected date: 1 = current, 0 = custom */
}CalendarView;

/**
 * \brief Structure for all the sorting parameters
 *
 * This structure is used to pass many arguments in a callback function which has only
 * one argument.
*/
typedef struct {
    GtkWidget *window;      /**< Current window to allow child window to close it */
    GtkWidget *notebook;    /**< Notebook to be updated */
    GtkWidget *sortButton;  /**< Button to choose the sort type */
    int sortType;           /**< Indicator of which sort type is requested */
}NotebookFill;

GtkWidget *setHomeWindow(int firstLoad, int fullScreen, int cssMode);
void setHomeEnvironment(GtkWidget *window, int cssMode);
void launchHomeView(GtkWidget *but, WorkWindow * workwindow);
void freeWorkWindow(WorkWindow * workwindow);

void fillPatientNotebook(GtkWidget *button, NotebookFill *param);
void processSearch(GtkWidget *button, SearchParam *search);
void seeAppointmentsAtDate(GtkCalendar *calendar, CalendarView *params);

#endif //LOGICIEL_KINE_PATIENT_VIEW_H
