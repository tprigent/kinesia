//
// Created by julien on 09/02/2021.
//

#ifndef LOGICIEL_KINE_STRUCTURES_H
#define LOGICIEL_KINE_STRUCTURES_H

#define LG_MAX_NOM 20
#define LG_MAX_INFO 100
#define LG_MAX_OTHERS 300

typedef struct{
    int day;
    int month;
    int year;
}Date;

/*enum pour genre d'une personne*/
typedef enum {HOMME, FEMME, AUTRE}Genre;


/*Structure adresse*/
typedef struct {
    char * numMaison; //la personne doit ajouter bis ou ter si maison bis ou ter (à préciser dans l'interface)
    char * rue; //Rue ou avenue ou autre
    int codePostal; //code postal
    char * ville;
    char * infoComp; //num batiment, num appartement...
}Adresse;

typedef struct{
    /* Etat civil */
    char * name;
    char * forename;
    Date birthdate;
    char * place_birth;
    Genre genre;       // Enum HOMME, FEMME, AUTRE
    Adresse address;
    int phone_number;
    char * mail_address;
    char * job;
    char * num_secu;     // Num de secu trop grand meme pour un long int

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
    char * nomSeance; //Titre de la séance
    Date dateSeance; //Date de la séance actuelle
    Date dateSeanceSuiv; //Date de la prochaine séance
    char * observations; //observations faites lors de la séance

    /*id Séance (je sais pas si ce sera utile mais il paraît qu'il faut toujours faire ça*/
    unsigned int idSeance;

    /*lien à un dossier*/
    unsigned int idDossier;
}Seance;

typedef struct{
    char *folderName;           //Name of the folder
    char *pathology;            //Reason for consultation
    char *details;              //Important things to know about the pathology
    unsigned int numberOfFiles; //To count the attached files
    unsigned int idFolder;      //Unique number for a folder
}Folder;

#endif //LOGICIEL_KINE_STRUCTURES_H
