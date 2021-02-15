//
// Created by julien on 09/02/2021.
//

#ifndef LOGICIEL_KINE_CONNECT_STRUCT_UI_H
#define LOGICIEL_KINE_CONNECT_STRUCT_UI_H

#include "structures.h"
#include <string.h>

char *get_name_UI(Patient *patient);
void free_name_UI(char *name);

char *get_date_UI(Date *date);
void free_date_UI(char *date);

char *get_job_UI(Patient *patient);

char *get_height_weight_UI(Patient *patient);
void free_height_weight_UI(char *height_weight);

char *get_global_pathologies_UI(Patient *patient);

char *get_first_consultation_UI(Patient *patient);
void free_first_consultation_UI(char *first_consultation);

char *get_formatted_folder_title_UI(Folder *folder);
void free_formatted_folder_title_UI(char *folder_title);

char *get_formatted_folder_infos_UI(Folder *folder);
void free_folder_infos_UI(char *infos);

char *get_indicator_files_UI(Folder *folder);
void free_indicator_files_UI(char *indicator);

#endif //LOGICIEL_KINE_CONNECT_STRUCT_UI_H
