/*!
* \file seance.h
* \brief File with functions to allocate, fill from model requests, and free Session structure
*/

#ifndef LOGICIEL_KINE_SESSION_MANAGER_H
#define LOGICIEL_KINE_SESSION_MANAGER_H

#include <stdio.h>
#include "structures.h"
#include <sqlite3.h>

/*session's allocation's functions*/
void freeSession(Session *s);

/*list gestion's functions*/
void initList(SessionList *l);
int isEmpty(SessionList *l);
int insertFirst(SessionList *l, char *sName, char *obs, int sdDay, int sdMonth, int sdYear, int nsdDay, int nsdMonth, int nsdYear, int idS, int idFolder);
int insertLast(SessionList *l, char *sName, char *obs, int sdDay, int sdMonth, int sdYear, int nsdDay, int nsdMonth, int nsdYear, int idS, int idFolder);
void deleteFirst(SessionList *l);
void deleteCurrent(SessionList *l);
int pointNthElement(SessionList *l, int n);
int deleteNthElement(SessionList *l, int n);
void setOnFirst(SessionList *l);
void setOnLast(SessionList *l);
void setOnNext(SessionList *l);
int isOutOfList(SessionList *l);
void freeList(SessionList *l);


//Ajout d'une seance avec un instance de struct seance
int addSession(Session *session);
//Recupération d'une séance
Session* getSession(int idSession);

#endif //LOGICIEL_KINE_SESSION_MANAGER_H
