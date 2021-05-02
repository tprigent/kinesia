/*!
* \file patient_manager.h
* \brief File with functions to allocate, fill from model requests, and free Patient structure
*/

#ifndef LOGICIEL_KINE_PATIENT_H
#define LOGICIEL_KINE_PATIENT_H

#include <stdio.h>
#include "structures.h"

/*A changer : faire une fonction d'allocation int allocate(Patient * p) où la structure et les attributs dans la structure sont alloués, et des fonctions de remplissage ensuite*/


void printPatient(Patient *patient, char *context);
void printGender(Genre gender);


int allocateStringPatient(char **string, int lg);
int allocatePatient(Patient ** p);
int allocateAddress(Address * a);
void freePatient(Patient ** p);
void freeAddress(Address * a);


int setPatient(Patient * p, char * name, char * fn, Date bd, char * placeBirth, int g, Address ad, char* pn, char * ma, char* job, char * ns, char * w, char * h, Date fc, char * gp,unsigned int idPatient,int isArchived);
int setAddress(Address * adr, char * r, char * cp, char * v, char * iC);
int setDate(Date * d, int j, int m, int a);

int getFuturePatientId();

#endif //LOGICIEL_KINE_PATIENT_H
