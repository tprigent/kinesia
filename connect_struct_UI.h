//
// Created by julien on 09/02/2021.
//

#ifndef LOGICIEL_KINE_CONNECT_STRUCT_UI_H
#define LOGICIEL_KINE_CONNECT_STRUCT_UI_H

#include "Structures.h"
#include <string.h>

char *get_name_UI(Patient *patient);
void free_name_UI(char *name);

char *get_birthdate_UI(Patient *patient);
void free_birthdate_UI(char *birthdate);

char *get_job_UI(Patient *patient);

#endif //LOGICIEL_KINE_CONNECT_STRUCT_UI_H
