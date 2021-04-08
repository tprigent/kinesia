/*!
* \file struct_to_BDD_patient.h
* \brief File to put data in BDD from Patient's structures.
*/

#include "../model/structures.h"

#ifndef LOGICIEL_KINE_STRUCT_TO_BDD_PATIENT_H
#define LOGICIEL_KINE_STRUCT_TO_BDD_PATIENT_H

int modifyPatient(Patient *gen);
int addPatient(Patient *gen);
int deletePatient(int id);

#endif //LOGICIEL_KINE_STRUCT_TO_BDD_PATIENT_H
