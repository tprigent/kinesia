/*!
* \file BDD_to_struct_patient.h
* \brief File with functions to take data from BDD, and put it in Patient structures
*/

#ifndef LOGICIEL_KINE_BDD_TO_STRUCT_PATIENT_H
#define LOGICIEL_KINE_BDD_TO_STRUCT_PATIENT_H

#include "../model/structures.h"

int getNbPatient(Archived a);
char* getNameFirstnamePatient(int id);
Patient* getPatient(int id);
int getNameFirstnameIdPatient(int* tabId, char** nom, Archived a,Sort s);

#endif //LOGICIEL_KINE_BDD_TO_STRUCT_PATIENT_H
