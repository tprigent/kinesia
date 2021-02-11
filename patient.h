//
// Created by salome on 10/02/2021.
//

#ifndef LOGICIEL_KINE_PATIENT_H
#define LOGICIEL_KINE_PATIENT_H

#include <stdio.h>
#include "Structures.h"
#include "sqlite3.h"

//Modification d'un patient
int addPatient(Patient *gen);
//Ajout d'un patient dans la table patient à partir d'une instance de la struct Patient
int modifyPatient(Patient *gen);

#endif //LOGICIEL_KINE_PATIENT_H
