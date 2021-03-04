/*!
* \file connect_UI_struct.c
* \brief File with functions used to parse data from UI entries to structure
*/

#include "connect_UI_struct.h"

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
 * \brief Convert string number to int
 *
 * \param[in] stringNumber source string number
 * \param[out] int result
*/
int convertToInt(char *stringNumber){
    int number;
    sscanf(stringNumber, "%d", &number);
    return number;
}

/*!
 * \brief Convert string address to Address struct (only number, type and street name)
 *
 * \param[in] stringAddress Source string typed by the user
 * \param[in] result Address resulting
*/
void parseAddress(char *stringAddress, Address *result){
    char *number = (char*) malloc(sizeof(Date));
    char *type = (char*) malloc(sizeof(Date));;
    char *street = (char*) malloc(sizeof(Date));;
    sscanf(stringAddress, "%s %s %s", number, type, street);
    strcpy(result->number, number);
    strcpy(result->street, type);
    strcat(result->street, street);
}