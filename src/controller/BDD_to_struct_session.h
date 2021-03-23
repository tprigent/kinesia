//
// Created by salome on 22/03/2021.
//

#ifndef LOGICIEL_KINE_BDD_TO_STRUCT_SESSION_H
#define LOGICIEL_KINE_BDD_TO_STRUCT_SESSION_H

#include "../model/structures.h"

Session * getSession(int idSession);
int * getSessionId(int idFolder);
SessionList * getSessionList(int idF);
int getNbSession(int idFolder);

#endif //LOGICIEL_KINE_BDD_TO_STRUCT_SESSION_H
