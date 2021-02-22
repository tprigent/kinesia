/*!
* \file structures.h
* \brief File with custom structures declaration
*/

#ifndef LOGICIEL_KINE_STRUCTURES_H
#define LOGICIEL_KINE_STRUCTURES_H

#define LG_MAX_INFO 100
#define LG_MAX_OTHERS 300

typedef struct{
    int day;
    int month;
    int year;
}Date;

/*enum pour genre d'une personne*/
typedef enum {MAN, WOMAN, OTHER}Genre;


/*Structure adresse*/
typedef struct {
    char * number; //la personne doit ajouter bis ou ter si maison bis ou ter (à préciser dans l'interface)
    char * street; //Rue ou avenue ou autre
    char * postCode; //code postal
    char * city;
    char * other_info; //num batiment, num appartement...
}Address;

typedef struct{
    /* Etat civil */
    char * name;
    char * firstname;
    Date birthdate;
    char * place_birth;
    Genre gender;       // Enum HOMME, FEMME, AUTRE
    Address address;
    char * phone_number;
    char * mail_address;
    char * job;
    char * ssn;     // Num de secu trop grand meme pour un long int

    /* Informations médicales */
    int weight;
    int height;
    Date first_consultation;
    char * global_pathologies;

    /* Autre */
    unsigned int id;

}Patient;


typedef struct{
    /*Informations relatives à la séance*/
    char * sessionName; //Titre de la séance
    Date sessionDate; //Date de la séance actuelle
    Date nextSessionDate; //Date de la prochaine séance
    char * observations; //observations faites lors de la séance

    /*id Séance (je sais pas si ce sera utile mais il paraît qu'il faut toujours faire ça*/
    unsigned int idSession;

    /*lien à un dossier*/
    unsigned int idFolder;
}Session;

typedef struct{
    char *folderName;           //Name of the folder
    char *pathology;            //Reason for consultation
    char *details;              //Important things to know about the pathology
    Date startOfTreatment;      //Date of the beginning of the treatment
    unsigned int numberOfFiles; //To count the attached files
    unsigned int idFolder;      //Unique number for a folder
}Folder;

#endif //LOGICIEL_KINE_STRUCTURES_H
