/*!
* \file structures.h
* \brief File with custom structures declaration
*/

#ifndef LOGICIEL_KINE_STRUCTURES_H
#define LOGICIEL_KINE_STRUCTURES_H

#define LG_MAX_INFO 100
#define LG_MAX_OTHERS 300
#define NB_MAX_SESSION 100

/**
 * \brief Structure to represent a Date
*/
typedef struct{
    int day;              /**< the day */
    int month;            /**< the month (1 to -4) */
    int year;             /**< the year (4-digits) */
}Date;


/**
 * \brief The enumeration of archived type
*/
typedef enum {ACTIVE,ARCHIVED,ALL}Archived;


/**
 * \brief The enumeration of sort
*/
typedef enum {NAME_ASC,NAME_DESC,FIRSTNAME_ASC,FIRSTNAME_DESC,HEIGHT}Sort;


/**
 * \brief The enumeration of human genders
*/
typedef enum {MAN, WOMAN, OTHER}Genre;


/**
 * \brief Structure to represent an Address
*/
typedef struct {
    char * street;                  /**< number and name of the street, avenue, etc */
    char * postCode;                /**< number of digit can depend */
    char * city;                    /**< city name */
    char * other_info;              /**< floor number, building number (if applicable) */
}Address;



/**
 * \brief Structure to represent a Patient
*/
typedef struct{
    /**
      * \name Civil status
    */
    char * name;                   /**< Patient name */
    char * firstname;              /**< Patient first name */
    Date birthdate;                /**< Patient birthdate */
    char * place_birth;            /**< Patient place of birth (city) */
    Genre gender;                  /**< Patient gender (enum) */
    Address address;               /**< Patient address */
    char * phone_number;           /**< Patient phone number */
    char * mail_address;           /**< Patient e-mail */
    char * job;                    /**< Patient job that might be useful for a better understanding of some health issues */
    char * ssn;                    /**< Patient social security number (too long for an int) */
    /**
      * \name Medical information
    */
    char * weight;                 /**< Patient weight (in kg) */
    char * height;                 /**< Patient height (in cm) */
    Date first_consultation;       /**< first consultation at this office */
    char * global_pathologies;     /**< pathologies that might be useful for a better understanding of some health issues */

    /**
      * \name Database information
    */
    unsigned int id;             /**< Patient unique identifier to select him in model */
    int isArchived;              /**< Boolean to know if the Patient is archived or not */

}Patient;


/**
 * \brief Structure to represent a Session
*/
typedef struct{
    /**
      * \name Session relative information
    */
    char * sessionName;         /**< Session title (eventually chosen by user) */
    Date sessionDate;           /**< Session date */
    Date nextSessionDate;       /**< Date of the next session */
    char * nextSessionHour;     /**< Hour of the next session */
    char * observations;        /**< Observations made during the session */
    int isRealFolder;           /**< Helper to display next appointments in Home view */

    /**
     * \name Database information
    */
    unsigned int idSession;      /**< Session unique identifier to select it in model */
    unsigned int idFolder;      /**< Related Folder identifier */
}Session;

typedef struct NodeList{
    Session session;
    struct NodeList *next;
    struct NodeList *previous;
}NodeList;

typedef struct{
    NodeList *first;
    NodeList *current;
    NodeList *last;
}SessionList;

/**
 * \brief Structure to represent a Folder
*/
typedef struct{
    /**
      * \name Folder relative information
    */
    char *folderName;           /**< Folder name */
    char *pathology;            /**< Reason for consultation */
    char *details;              /**< Important things to know about the pathology */
    Date startOfTreatment;      /**< Date of the beginning of the treatment */
    unsigned int numberOfFiles; /**< Attachment counter */

    SessionList *ListOfSessions;

    /**
     * \name Database information
    */
    unsigned int idFolder;      /**< Folder unique identifier to select it in model */
    unsigned int idPatient;
}Folder;

#endif //LOGICIEL_KINE_STRUCTURES_H
