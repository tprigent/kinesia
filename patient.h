//
// Created by salome on 10/02/2021.
//

#ifndef LOGICIEL_KINE_PATIENT_H
#define LOGICIEL_KINE_PATIENT_H

#include <stdio.h>
#include "Structures.h"
#include "sqlite3.h"

int addPatient(Patient gen);
int modifyPatient(modifiable_item item);
int addSeance(Patient gen, Seance seance);

#endif //LOGICIEL_KINE_PATIENT_H
