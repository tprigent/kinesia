/*!
* \file BDD_to_struct_patient.h
* \brief File with functions to take data from BDD, and put it in Patient structures
*/

#ifndef LOGICIEL_KINE_BDD_TO_STRUCT_PATIENT_H
#define LOGICIEL_KINE_BDD_TO_STRUCT_PATIENT_H

#include "../model/structures.h"

int getNbPatient();
char* getNameFirstnamePatient(int id);
Patient* getPatient(int id);
int* getArchivedPatientID();
int* getActivePatientID();
int getNbArchivedPatient();
int getNbActivePatient();
int getNameFirstnameIdActivePatient(int* tabId, char** nom,int nbP);
int getNameFirstnameIdArchivedPatient(int* tabId, char** nom,int nbP);

#endif //LOGICIEL_KINE_BDD_TO_STRUCT_PATIENT_H
