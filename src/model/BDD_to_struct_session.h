/*!
* \file BDD_to_struct_session.h
* \brief File to take data from BDD about Sessions and fill Session structures
*/

#ifndef LOGICIEL_KINE_BDD_TO_STRUCT_SESSION_H
#define LOGICIEL_KINE_BDD_TO_STRUCT_SESSION_H

#include "structures.h"

Session * getSession(int idSession);
Session * getSession0(int idFolder);
int * getSessionId(int idFolder);
SessionList * getSessionList(int idF);
int getNbSession(int idFolder);
int getSessionsAtDate(Date *date, int *sessionID, int *folderID);

#endif //LOGICIEL_KINE_BDD_TO_STRUCT_SESSION_H
