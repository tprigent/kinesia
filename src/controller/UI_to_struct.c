/*!
* \file UI_to_struct.c
* \brief File with functions used to parse data from UI entries to structures
*/

#include "UI_to_struct.h"

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