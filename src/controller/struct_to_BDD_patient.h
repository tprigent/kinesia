//
// Created by salome on 22/03/2021.
//

#include "../model/structures.h"

#ifndef LOGICIEL_KINE_STRUCT_TO_BDD_PATIENT_H
#define LOGICIEL_KINE_STRUCT_TO_BDD_PATIENT_H

int modifyPatient(Patient *gen);
int addPatient(Patient *gen);
int deletePatient(int id);

#endif //LOGICIEL_KINE_STRUCT_TO_BDD_PATIENT_H
