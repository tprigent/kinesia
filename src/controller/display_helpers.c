/*!
* \file display_helpers.c
* \brief File with functions used to format data for display
*/

#include "display_helpers.h"

/*!
 * \brief Write an integer into a given char
 *
 * \param[in] str destination char pointer
 * \param[in] num source integer
*/
void tostring(char *str, int num){
    int i, rem, len = 0, n;
    n = num;
    while(n!=0){
        len++;
        n /= 10;
    }
    for(i=0; i<len; i++){
        rem = num % 10;
        num = num/10;
        str[len - (i+1)] = rem + '0';
    }
    str[len] = '\0';
}

/*!
 * \brief Concatenate firstname and surname in one char
 *
 * \param[in] patient Concerned Patient
 * \param[out] Char pointer combining at "Firstname Name" format
*/
char *get_name_UI(Patient *patient){
    char *name = (char*) malloc(sizeof(patient->firstname)+sizeof(patient->name)+8*sizeof(char));
    strcpy(name, "<b>");
    strcat(name, patient->firstname);
    strcat(name, " ");
    strcat(name, patient->name);
    strcat(name, "</b>\0");

    return name;
}

/*!
 * \brief Parse Date instance to char
 *
 * \param[in] date Involved Date
 * \param[out] Char pointer containing the date
*/
char *get_date_UI(Date *date){
    int length = (int) strlen("00/00/0000");
    char *stringDate = (char*) malloc(length*sizeof(char));
    char day[3];
    char month[3];
    char year[5];
    tostring(day, date->day);
    tostring(month, date->month);
    tostring(year, date->year);

    strcpy(stringDate, day);
    strcat(stringDate, "/");
    strcat(stringDate, month);
    strcat(stringDate, "/");
    strcat(stringDate, year);
    strcat(stringDate, "\0");

    return stringDate;
}

/*!
 * \brief Concatenate Patient height and weight in a single char for display
 *
 * \param[in] patient Concerned Patient
 * \param[out] Char pointer containing the Patient height and weight
*/
char *get_height_weight_UI(Patient *patient){
    char *height_weight = (char*) malloc(sizeof(patient->height)+sizeof(patient->weight)+12*sizeof(char));
    strcpy(height_weight, patient->height);
    strcat(height_weight, "     ;     ");
    strcat(height_weight, patient->weight);
    strcat(height_weight, "\0");

    return height_weight;
}

/*!
 * \brief Parse first consultation date from Date structure to char
 *
 * \param[in] patient Concerned Patient
 * \param[out] Char pointer containing the first consultation date
*/
char *get_first_consultation_UI(Patient *patient){

    char *first_consultation = (char*) malloc(40*sizeof(char));
    char day[3];
    char month[3];
    char year[5];
    tostring(day, patient->first_consultation.day);
    tostring(month, patient->first_consultation.month);
    tostring(year, patient->first_consultation.year);

    strcpy(first_consultation, "Première consultation : ");
    strcat(first_consultation, day);
    strcat(first_consultation, "/");
    strcat(first_consultation, month);
    strcat(first_consultation, "/");
    strcat(first_consultation, year);
    strcat(first_consultation, "\0");

    return first_consultation;
}

/*!
 * \brief Format Folder title
 *
 * \param[in] folder Concerned Folder
 * \param[out] Char pointer containing the formatted  title
*/
char *get_formatted_folder_title_UI(Folder *folder){
    char *start = "<big><b>         ";
    char *end = "</b></big>";
    int length = (int) strlen(folder->folderName);
    length += (int) strlen(start);
    length += (int) strlen(end);
    char *formattedTitle = (char*) malloc(length*sizeof(char));
    strcpy(formattedTitle, start);
    strcat(formattedTitle, folder->folderName);
    strcat(formattedTitle, end);
    return formattedTitle;
}


/*!
 * \brief Format Folder attachment counter display
 *
 * \param[in] folder Concerned Folder
 * \param[out] Char pointer containing the formatted counter
*/
char *get_indicator_files_UI(int patientID, int folderID){
    char *indicator = (char*) malloc(20*sizeof(char));
    char *buffer = (char*) malloc(5*sizeof(char));
    sprintf(buffer, "%d", getNbOfAttachments(patientID, folderID));
    strcpy(indicator, "   (");
    strcat(indicator, buffer);
    strcat(indicator, ")");
    return indicator;
}


/*!
 * \brief Get the birthdate and the age of a Patient
 *
 * \param[in] patient Patient concerned
 * \param[out] String containing the birthdate and age to the format "dd/mm/yyyy (xxx ans)"
*/
char *get_age_and_birthdate(Patient *patient){
    char *ageString = (char*) malloc(sizeof(char)*strlen("00/00/0000 (000 ans)"));
    int age = 0;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int birth_day= patient->birthdate.day;
    int birth_month = patient->birthdate.month;
    int birth_year = patient->birthdate.year;
    int now_day = tm.tm_mday;
    int now_month = tm.tm_mon + 1;
    int now_year = tm.tm_year + 1900;

    age = now_year - birth_year;
    if(birth_month>now_month) age --;
    if(birth_month == now_month && birth_day>now_day) age --;
    snprintf(ageString, sizeof(char)*strlen("00/00/0000 (000 ans)"), "%s (%d ans)",get_date_UI(&patient->birthdate) ,age);
    return ageString;
}

/*!
 * \brief Get the current date
 *
 * \param[out] String containing the current date in format "dd/mm/yyyy"
*/
char *get_current_date(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    Date *date_struct = (Date*) malloc(sizeof(Date));
    date_struct->day = tm.tm_mday;
    date_struct->month = tm.tm_mon + 1;
    date_struct->year = tm.tm_year + 1900;

    char *date = get_date_UI(date_struct);
    return date;
}

/*!
 * \brief Get the default name for a new session
 *
 * This functions returns a default name for a new session,
 * the name depends of the day (Séance du dd/mm/yyyy)
 *
 * \param[out] String containing the new session name
*/
char *get_new_session_name(){
    char *new_session_name = (char*) malloc(21*sizeof(char));
    char *date = get_current_date();

    strcpy(new_session_name, "Séance du ");
    strcat(new_session_name, date);
    strcat(new_session_name, "\0");

    return new_session_name;
}

/*!
 * \brief Parse string date to Date format
 *
 * \param[in] stringDate source string date
 * \param[out] destination Date structure
*/
Date *parseDate(char *stringDate){
    Date *date = (Date *) malloc(sizeof(Date));
    int yyyy;
    int mm;
    int dd;
    sscanf(stringDate, "%d/%d/%d", &dd, &mm, &yyyy);
    date->year = yyyy;
    date->month = mm;
    date->day = dd;
    return date;
}

/*!
 * \brief Free allocated char pointers
 *
 * \param[in] info Char to be freed
*/
void free_info_UI(char *info){
    free(info);
}
