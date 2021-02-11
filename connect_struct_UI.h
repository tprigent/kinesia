//
// Created by julien on 09/02/2021.
//

#ifndef LOGICIEL_KINE_CONNECT_STRUCT_UI_H
#define LOGICIEL_KINE_CONNECT_STRUCT_UI_H

#include "structures.h"
#include <string.h>

char *get_name_UI(Patient *patient);
void free_name_UI(char *name);

char *get_birthdate_UI(Patient *patient);
void free_birthdate_UI(char *birthdate);

char *get_job_UI(Patient *patient);

char *get_height_weight_UI(Patient *patient);
void free_height_weight_UI(char *height_weight);

char *get_global_pathologies_UI(Patient *patient);

char *get_first_consultation_UI(Patient *patient);
void free_first_consultation_UI(char *first_consultation);

#endif //LOGICIEL_KINE_CONNECT_STRUCT_UI_H
