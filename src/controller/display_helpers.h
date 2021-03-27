/*!
* \file display_helpers.h
* \brief File with functions used to format data for display
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../model/structures.h"

#ifndef LOGICIEL_KINE_CONNECT_STRUCT_UI_H
#define LOGICIEL_KINE_CONNECT_STRUCT_UI_H


char *get_name_UI(Patient *patient);
char *get_date_UI(Date *date);
char *get_height_weight_UI(Patient *patient);
char *get_first_consultation_UI(Patient *patient);
char *get_formatted_folder_title_UI(Folder *folder);
char *get_formatted_folder_infos_UI(Folder *folder);
char *get_indicator_files_UI(Folder *folder);
char *get_age_and_birthdate(Patient *patient);
char *get_current_date();
char *get_new_session_name();
Date *parseDate(char *stringDate);
void free_info_UI(char *info);

#endif //LOGICIEL_KINE_CONNECT_STRUCT_UI_H
