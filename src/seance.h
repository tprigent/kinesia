/*!
* \file seance.h
* \brief File with functions to allocate, fill from model requests, and free Session structure
*/

#ifndef LOGICIEL_KINE_SEANCE_H
#define LOGICIEL_KINE_SEANCE_H

#include <stdio.h>
#include "model/structures.h"
#include <sqlite3.h>

/*allocation's functions*/
int allocateStringSession(Session **s);

//Ajout d'une seance avec un instance de struct seance
int addSeance(Seance *seance);
//Recupération d'une séance
Seance* getSeance(int idSeance);

#endif //LOGICIEL_KINE_SEANCE_H
