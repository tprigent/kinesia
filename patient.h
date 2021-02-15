//
// Created by salome on 10/02/2021.
//

#ifndef LOGICIEL_KINE_PATIENT_H
#define LOGICIEL_KINE_PATIENT_H

#include <stdio.h>
#include "structures.h"

/*A changer : faire une fonction d'allocation int allocate(Patient * p) où la structure et les attributs dans la structure sont alloués, et des fonctions de remplissage ensuite*/

/* fonctions d'allocation des structures*/
int allocatePatient(Patient ** p);
int allocateAdresse(Adresse * a);

/*fonction de remplissage/modification des attributs des structures*/
int setPatient(Patient * p, char * name, char * fn, Date bd, char * placeBirth, int g, Adresse ad, int pn, char * ma, char* metier, char * ns, int w, int h, Date fc, char * gp);
int setAdresse(Adresse * adr, char * numM, char * r, int cp, char * v, char * iC);
int setDate(Date * d, int j, int m, int a);


#endif //LOGICIEL_KINE_PATIENT_H
