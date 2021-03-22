//
// Created by salome on 22/03/2021.
//

#ifndef LOGICIEL_KINE_BDD_TO_STRUCT_PATIENT_H
#define LOGICIEL_KINE_BDD_TO_STRUCT_PATIENT_H

#include "../model/structures.h"

int getNbPatient();
char* getNameFirstnamePatient(int id);
Patient* getPatient(int id);
int* getIdPatientArchive ();
int* getIdPatientNonArchive ();

#endif //LOGICIEL_KINE_BDD_TO_STRUCT_PATIENT_H
