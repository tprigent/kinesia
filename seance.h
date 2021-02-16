//
// Created by paul on 12/02/2021.
//

#ifndef LOGICIEL_KINE_SEANCE_H
#define LOGICIEL_KINE_SEANCE_H

#include <stdio.h>
#include "Structures.h"
#include "sqlite3.h"

//Ajout d'une seance avec un instance de struct seance
int addSeance(Seance *seance);
//Recupération d'une séance
Seance* getSeance(int idSeance);

#endif //LOGICIEL_KINE_SEANCE_H
