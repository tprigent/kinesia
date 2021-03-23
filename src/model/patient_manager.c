/*!
* \file patient.c
* \brief File with functions to allocate, fill from database requests, and free Patient structure
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structures.h"
#include <sqlite3.h>
#include "patient_manager.h"

/*!
 * \brief [Debug] Print a given patient to the terminal
 *
 * \param[in] patient Patient to be displayed
 * \param[in] context Brief text to understand when the function has been called
*/
void printPatient(Patient *patient, char *context){
    printf("******* Displaying patient #%d *******\n", patient->id);

    printf("\033[0;31m");
    printf("-> Context: %s\n", context);
    printf("\033[0m");

    printf("Firstname: %s ", patient->firstname);
    printf("Name: %s\n", patient->name);
    printf("Gender: ");
    printGender(patient->gender);
    printf("\n");

    printf("Birthdate: %d/%d/%d\n", patient->birthdate.day, patient->birthdate.month, patient->birthdate.year);
    printf("Place of birth: %s\n", patient->place_birth);
    printf("Address: %s %s, %s %s (%s)\n", patient->address.number, patient->address.street, patient->address.postCode, patient->address.city, patient->address.other_info);
    printf("Phone: %s\n", patient->phone_number);
    printf("Mail: %s\n", patient->mail_address);
    printf("Job: %s\n", patient->job);

    printf("Social security number: %s\n", patient->ssn);
    printf("Global pathologies: %s\n", patient->global_pathologies);
    printf("Height: %s\n", patient->height);
    printf("Weight: %s\n", patient->weight);
    printf("First consultation: %d/%d/%d\n", patient->first_consultation.day, patient->first_consultation.month, patient->first_consultation.year);
    printf("Is archived: %d\n", patient->isArchived);

    printf("******* End of the patient display *******\n");
}

/*!
 * \brief [Debug] Print a Gender enum to the terminal
 *
 * \param[in] gender Gender to be displayed
*/
void printGender(Genre gender){
    if(gender == MAN) printf("man");
    else if(gender == WOMAN) printf("woman");
    else if(gender == OTHER) printf("other");
    else printf("error");
}


/*!
 * \brief This function allocates memory for a string of length lg
 *
 * \param[in] char ** string the address of the string to allocate
 * \param[in] int lg the length of the string
 *
 * \param[out] int 0 if the allocation went well, -1 otherwise
*/
int allocateStringPatient(char ** string, int lg) {
    *string = (char *) malloc(sizeof(char)*lg);
    if(*string == (char *) NULL) return -1;
    return 0;
}


/*!
 * \brief This function allocates memory for the attributes of an address
 *
 * \param[in] Address * a the address to allocate
 *
 * \param[out] int, 0 if the allocation went well, -1 otherwise
*/
int allocateAddress(Address * a) {

    /*allocation mémoire des chaînes de caractères de la structure Adresse*/
    if (allocateStringPatient(&(a->number), LG_MAX_INFO) !=0) return -1;
    if (allocateStringPatient(&(a->street), LG_MAX_INFO) !=0) return -1;
    if (allocateStringPatient(&(a->city), LG_MAX_INFO) !=0) return -1;
    if (allocateStringPatient(&(a->other_info), LG_MAX_OTHERS) !=0) return -1;
    if (allocateStringPatient(&(a->postCode), LG_MAX_INFO) !=0) return -1;
    return 0;
}



/*!
 * \brief This function allocates memory for an instance of Patient, and the attributes of the instance
 *
 * \param[in] Patient **p, the address of the pointer of Patient to allocate
 *
 * \param[out] int, 0 if the allocation went well, -1 otherwise
*/
int allocatePatient(Patient ** p) {
    *p = (Patient *) malloc(sizeof(Patient));

    /*test des allocations de chaque attribut de la structure patient qui ont besoin d'être alloués*/
    if((p == NULL) || (allocateStringPatient(&((*p)->firstname), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->name), LG_MAX_INFO) !=0)
    || (allocateAddress(&((*p)->address)) !=0)
    || (allocateStringPatient(&((*p)->global_pathologies), LG_MAX_OTHERS) !=0)
    || (allocateStringPatient(&((*p)->mail_address), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->job), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->ssn), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->phone_number), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->place_birth), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->height), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->weight), LG_MAX_INFO) !=0)) return -1;

    return 0;
}


/*!
 * \brief This function frees the memory of the attributes of an Address instance
 *
 * \param[in] Address *a the pointer of an address to free.
*/
void freeAddress(Address * a) {
    free((void*)a->number);
    free((void*)a->street);
    free((void*)a->postCode);
    free((void*)a->city);
    free((void*)a->other_info);
}


/*!
 * \brief This function frees the memory of an instance of Patient
 *
 * \param[in] Patient **p the address of the pointer of Patient to free
*/
void freePatient(Patient ** p) {
    free((void *) (*p)->phone_number);
    free((void *) (*p)->name);
    free((void *) (*p)->global_pathologies);
    free((void *) (*p)->place_birth);
    free((void *) (*p)->firstname);
    free((void *) (*p)->mail_address);
    free((void *) (*p)->job);
    free((void *) (*p)->ssn);
    free((void *) (*p)->height);
    free((void *) (*p)->weight);
    freeAddress(&((*p)->address));
    free((void *) *p);
}

/*!
 * \brief This function fills the attributes of an instance of address with the in parameters
 *
 * \param[in] Address * a the pointer of the instance of address to fill
 * \param[in] char * numM the number in the street
 * \param[in] char * r the street
 * \param[in] char * cp the post code
 * \param[in] char * v the city
 * \param[in] char * iC the other info
 *
 * \param[out] int 0 if it went well, -1 otherwise
*/
int setAddress(Address * a, char * numM, char * r, char * cp, char * v, char * iC) {

    if(a == NULL) return -1;

    /*attribution des paramètres aux attributs de a*/
    /*ajout des 0 terminaux aux chaînes précédemment copiées par sécurité*/
    if(numM == NULL )
        strcpy(a->number, "\0");
    else {
        strncpy(a->number, numM, LG_MAX_INFO);
        a->number[LG_MAX_INFO] = '\0';
    }
    if(r == NULL)
        strcpy(a->street, "\0");
    else {
        strncpy(a->street, r, LG_MAX_INFO);
        a->street[LG_MAX_INFO] = '\0';
    }
    if(cp == NULL)
        strcpy(a->postCode, "\0");
    else {
        strncpy(a->postCode, cp, LG_MAX_INFO);
        a->postCode[LG_MAX_INFO] = '\0';
    }
    if(v == NULL)
        strcpy(a->city, "\0");
    else{
        strncpy(a->city, v, LG_MAX_INFO);
        a->city[LG_MAX_INFO] = '\0';
    }
    if(iC == NULL)
        strcpy(a->other_info, "\0");
    else {
        strncpy(a->other_info, iC, LG_MAX_OTHERS);
        a->other_info[LG_MAX_OTHERS] = '\0';
    }

    return 0;
}

/*!
 * \brief This function fills a Date with the in parameters
 *
 * \param[in] Date * d the pointer of the date to fill
 * \param[in] int j the day
 * \param[in] int m the month
 * \param[in] int a the year
 *
 * \param[out] int, 0 if it went well, -1 otherwise
*/
int setDate(Date * d, int j, int m, int a) {
    d->day = j;
    d->month = m;
    d->year = a;
    return 0;
}

/*!
 * \brief This function fills an instance of Patient, with the in parameters
 *
 * \param[in] Patient *p, the pointer of Patient to fill
 * \param[in] char * name, the name of the Patient
 * \param[in] char * fn, the firstname of the Patient
 * \param[in] Date bd, the birthdate of the Patient
 * \param[in] char * placeBirth, the birth place of the Patient
 * \param[in] int g, the gender of the Patient
 * \param[in] Address ad, the address of the Patient
 * \param[in] char * pn, the phone number of the Patient
 * \param[in] char * ma, the mail address of the Patient
 * \param[in] char * job, the job of the Patient
 * \param[in] char * ns, the ssn of the Patient
 * \param[in] int w, the weight of the Patient
 * \param[in] int h, the height of the Patient
 * \param[in] Date fc, the date of the first consultation of the Patient
 * \param[in] char * gp, the global pathologies or medical informations of the Patient
 * \param[in] unsigned int idPatient, the id of the Patient
 *
 * \param[out] int, 0 if it went well, -1 otherwise
*/
int setPatient(Patient * p, char * name, char * fn, Date bd, char * placeBirth, int g, Address ad, char* pn, char * ma, char* job, char * ns, char* w, char* h, Date fc, char * gp,unsigned int idPatient,int isArchived) {

    if (p == NULL) return -1; //si l'instance de patient à remplir est vide, erreur

    /*copie des chaînes de caractères en paramètres dans les attributs de l'instance p)*/
    /*ajout de 0 terminaux par sécurité*/
    if(placeBirth == NULL )
        strcpy(p->place_birth, "\0");
    else {
        strncpy(p->place_birth, placeBirth, LG_MAX_INFO);
        p->place_birth[LG_MAX_INFO] = '\0';
    }
    if(ns == NULL)
        strcpy(p->ssn, "\0");
    else {
        strncpy(p->ssn, ns, LG_MAX_INFO);
        p->ssn[LG_MAX_INFO] = '\0';
    }
    if(job == NULL)
        strcpy(p->job, "\0");
    else {
        strncpy(p->job, job, LG_MAX_INFO);
        p->job[LG_MAX_INFO] = '\0';
    }
    if(ma == NULL)
        strcpy(p->mail_address, "\0");
    else{
        strncpy(p->mail_address, ma, LG_MAX_INFO);
        p->mail_address[LG_MAX_INFO] = '\0';
    }
    if(gp == NULL)
        strcpy(p->global_pathologies, "\0");
    else {
        strncpy(p->global_pathologies, gp, LG_MAX_OTHERS);
        p->global_pathologies[LG_MAX_OTHERS] = '\0';
    }
    if(fn == NULL)
        strcpy(p->firstname, "\0");
    else {
        strncpy(p->firstname, fn, LG_MAX_INFO);
        p->firstname[LG_MAX_INFO] = '\0';
    }
    if(pn == NULL)
        strcpy(p->phone_number, "\0");
    else {
        strncpy(p->phone_number,pn,LG_MAX_INFO);
        p->phone_number[LG_MAX_INFO] = '\0';
    }
    if(h == NULL) {
        strcpy(p->height, "\0");
    }
    else {
        strncpy(p->height, h, LG_MAX_INFO);
        p->height[LG_MAX_INFO] = '\0';
    }
    if(w == NULL) {
        strcpy(p->weight, "\0");
    }
    else {
        strncpy(p->weight, w, LG_MAX_INFO);
        p->weight[LG_MAX_INFO] = '\0';
    }
    if(name == NULL) {
        strcpy(p->name, "\0");
        return -1;
    }
    else {
        strncpy(p->name, name, LG_MAX_INFO);
        p->name[LG_MAX_INFO] = '\0';
    }

    /*attribution des autres attributs*/
    if(ad.number == NULL) strcpy(p->address.number, "\0");
    else {
        strncpy(p->address.number, ad.number, LG_MAX_INFO);
        p->address.number[LG_MAX_INFO] = '\0';
    }

    if(ad.street == NULL) strcpy(p->address.street, "\0");
    else {
        strncpy(p->address.street, ad.street, LG_MAX_INFO);
        p->address.street[LG_MAX_INFO] = '\0';
    }

    if(ad.city == NULL) strcpy(p->address.city, "\0");
    else {
        strncpy(p->address.city, ad.city, LG_MAX_INFO);
        p->address.city[LG_MAX_INFO] = '\0';
    }

    if(ad.postCode == NULL) strcpy(p->address.postCode, "\0");
    else {
        strncpy(p->address.postCode, ad.postCode, LG_MAX_INFO);
        p->address.postCode[LG_MAX_INFO] = '\0';
    }

    if(ad.other_info == NULL) strcpy(p->address.other_info, "\0");
    else {
        strncpy(p->address.other_info, ad.other_info, LG_MAX_OTHERS);
        p->address.other_info[LG_MAX_OTHERS] = '\0';
    }

    p->first_consultation = fc;
    p->birthdate = bd;

    if (g > 2 || g < 0) return -1;
    p->gender = g;

    /*attribution d'un id unique par patient*/
    p->id = idPatient;
    p->isArchived = isArchived;

    return 0;
}

