//
// Created by salome on 22/03/2021.
//

#ifndef LOGICIEL_KINE_STRUCT_TO_BDD_SESSION_H
#define LOGICIEL_KINE_STRUCT_TO_BDD_SESSION_H

#include "../model/structures.h"

int addSession(Session *session);
int modifySession(Session *session);
int deleteSession(int id);


#endif //LOGICIEL_KINE_STRUCT_TO_BDD_SESSION_H
