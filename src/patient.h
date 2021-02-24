/*!
* \file patient.h
* \brief File with functions to allocate, fill from database requests, and free Patient structure
*/

#ifndef LOGICIEL_KINE_PATIENT_H
#define LOGICIEL_KINE_PATIENT_H

#include <stdio.h>
#include "structures.h"

/*A changer : faire une fonction d'allocation int allocate(Patient * p) où la structure et les attributs dans la structure sont alloués, et des fonctions de remplissage ensuite*/

/* fonctions d'allocation des structures*/
int allocatePatient(Patient ** p);
int allocateAddress(Address * a);
void freePatient(Patient ** a);
void freeAddress(Address * a);

/*fonction de remplissage/modification des attributs des structures*/
int setPatient(Patient * p, char * name, char * fn, Date bd, char * placeBirth, int g, Address ad, char* pn, char * ma, char* metier, char * ns, int w, int h, Date fc, char * gp,unsigned int idPatient);
int setAddress(Address * adr, char * numM, char * r, char * cp, char * v, char * iC);
int setDate(Date * d, int j, int m, int a);

#include "sqlite3.h"

//Modification d'un patient
int addPatient(Patient *gen);
//Ajout d'un patient dans la table patient à partir d'une instance de la struct Patient
int modifyPatient(Patient *gen);
//Recuperation d'un patient
Patient* getPatient(int id);

#endif //LOGICIEL_KINE_PATIENT_H
