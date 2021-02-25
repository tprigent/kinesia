/*!
* \file structures.h
* \brief File with custom structures declaration
*/

#ifndef LOGICIEL_KINE_STRUCTURES_H
#define LOGICIEL_KINE_STRUCTURES_H

#define LG_MAX_INFO 100
#define LG_MAX_OTHERS 300


/**
 * \brief Structure to represent a Date
*/
typedef struct{
    int day;              /**< the day */
    int month;            /**< the month (1 to 12) */
    int year;             /**< the year (4-digits) */
}Date;



/**
 * \brief The enumeration of human genders
*/
typedef enum {MAN, WOMAN, OTHER}Genre;


/**
 * \brief Structure to represent an Address
*/
typedef struct {
    char * number;                  /**< street number (add bis or ter if necessary) */
    char * street;                  /**< name of the street, avenue, etc */
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
    char * firstname;              /**< Patient first */
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
    int weight;                   /**< Patient weight (in kg) */
    int height;                   /**< Patient height (in cm) */
    Date first_consultation;      /**< first consultation at this office */
    char * global_pathologies;    /**< pathologies that might be useful for a better understanding of some health issues */

    /**
      * \name Database information
    */
    unsigned int id;             /**< Patient unique identifier to select him in database */

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
    char * observations;        /**< Observations made during the session */
    /**
     * \name Database information
    */
   unsigned int idSession;      /**< Session unique identifier to select it in database */
    unsigned int idFolder;      /**< Related Folder identifier */
}Session;


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
    /**
     * \name Database information
    */
    unsigned int idFolder;      /**< Folder unique identifier to select it in database */
}Folder;

#endif //LOGICIEL_KINE_STRUCTURES_H
