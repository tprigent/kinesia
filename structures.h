//
// Created by julien on 09/02/2021.
//

#ifndef LOGICIEL_KINE_STRUCTURES_H
#define LOGICIEL_KINE_STRUCTURES_H

#define LG_MAX_INFO 100
#define LG_MAX_OTHERS 300

typedef struct{
    int day;
    int month;
    int year;
}Date;

typedef struct{
    /* Etat civil */
    char name[LG_MAX_INFO];
    char forename[LG_MAX_INFO];
    Date birthdate;
    char place_birth[LG_MAX_INFO];
    char sexe[LG_MAX_INFO];       // Structure pour sexe HOMME/FEMME ?
    char address[LG_MAX_INFO];
    int phone_number;
    char mail_address[LG_MAX_INFO];
    char num_secu[LG_MAX_INFO];     // Num de secu trop grand meme pour un long int

    /* Informations médicales */
    int weight;
    int height;
    char groupe_sanguin[LG_MAX_INFO];          // Vraiment utile pour un kiné ?
    Date first_consultation;
    char global_pathologies[LG_MAX_OTHERS];

    /* Autre */
    unsigned int id;

}Patient;

#endif //LOGICIEL_KINE_STRUCTURES_H
