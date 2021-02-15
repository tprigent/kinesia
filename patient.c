//
// Created by salome on 10/02/2021.
//

#include "patient.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Structures.h"


/*allocation d'une chaîne de caractère de longueur lg*/
static int allocateStringPatient(char ** string, int lg) {
    *string = (char *) malloc(sizeof(char)*lg);
    if(*string == (char *) NULL) return -1;
    return 0;
}

/*allocation mémoire des attributs d'une structure Adresse*/
int allocateAdresse(Adresse * a) {

    /*allocation mémoire des chaînes de caractères de la structure Adresse*/
    if (allocateStringPatient(&(a->numMaison), LG_MAX_INFO) !=0) return -1;
    if (allocateStringPatient(&(a->rue), LG_MAX_INFO) !=0) return -1;
    if (allocateStringPatient(&(a->ville), LG_MAX_INFO) !=0) return -1;
    if (allocateStringPatient(&(a->infoComp), LG_MAX_OTHERS) !=0) return -1;
    return 0;
}


/*allocation mémoire d'un patient*/
int allocatePatient(Patient ** p) {
    *p = (Patient *) malloc(sizeof(Patient));

    /*test des allocations de chaque attribut de la structure patient qui ont besoin d'être alloués*/
    if((p == NULL) || (allocateStringPatient(&((*p)->name), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->forename), LG_MAX_INFO) !=0)
    || (allocateAdresse(&((*p)->address)) !=0)
    || (allocateStringPatient(&((*p)->global_pathologies), LG_MAX_OTHERS) !=0)
    || (allocateStringPatient(&((*p)->mail_address), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->metier), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->num_secu), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->place_birth), LG_MAX_INFO) !=0)) return -1;

    return 0;
}

/*remplissage/modification des attributs d'une adresse déjà créée et allouée*/
int setAdresse(Adresse * a, char * numM, char * r, int cp, char * v, char * iC) {

    if(a == NULL) return -1;
    /*attribution des paramètres aux attributs de a*/
    strncpy(a->numMaison, numM, LG_MAX_INFO);
    strncpy(a->rue, r, LG_MAX_INFO);
    strncpy(a->ville, v, LG_MAX_INFO);
    strncpy(a->infoComp, iC, LG_MAX_OTHERS);
    a->codePostal = cp;

    /*ajout des 0 terminaux aux chaînes précédemment copiées par sécurité*/
    a->numMaison[strlen(numM)] = '\0';
    a->rue[strlen(r)] = '\0';
    a->ville[strlen(v)] = '\0';
    a->infoComp[strlen(iC)] = '\0';
    return 0;
}

/*remplissage/modification des attributs d'une adresse déjà créée et allouée*/
int setDate(Date * d, int j, int m, int a) {
    if(d == NULL || j>31 || j <=0 || m <= 0 || m > 12 || a<=0) return -1;
    d->day = j;
    d->month = m;
    d->year = a;
    return 0;
}

/*remplissage/modification des attributs d'une adresse déjà créée et allouée*/
int setPatient(Patient * p, char * name, char * fn, Date bd, char * placeBirth, int g, Adresse ad, int pn, char * ma, char* metier, char * ns, int w, int h, Date fc, char * gp) {

    static int idPatient = 0;

    if(p == NULL) return -1; //si l'instance de patient à remplir est vide, erreur

    /*copie des chaînes de caractères en paramètres dans les attributs de l'instance p)*/
    strncpy(p->place_birth, placeBirth, LG_MAX_INFO);
    strncpy(p->num_secu, ns, LG_MAX_INFO);
    strncpy(p->metier, metier, LG_MAX_INFO);
    strncpy(p->mail_address, ma, LG_MAX_INFO);
    strncpy(p->global_pathologies, gp, LG_MAX_OTHERS);
    strncpy(p->forename, fn, LG_MAX_INFO);
    strncpy(p->name, name, LG_MAX_INFO);

    /*ajout de 0 terminaux par sécurité*/
    p->place_birth[strlen(placeBirth)] = '\0';
    p->num_secu[strlen(ns)] = '\0';
    p->metier[strlen(metier)] = '\0';
    p->mail_address[strlen(ma)] = '\0';
    p->global_pathologies[strlen(gp)] = '\0';
    p->forename[strlen(fn)] = '\0';
    p->name[strlen(name)] = '\0';

    /*attribution des autres attributs*/
    p->address = ad;
    p->first_consultation = fc;
    p->birthdate = bd;
    p->height = h;
    p->phone_number = pn;
    p->weight = w;

    if(g>2 || g<0) return -1;
    p->genre = g;

    /*attribution d'un id unique par patient*/
    p->id = idPatient;

    idPatient++;

    return 0;
}