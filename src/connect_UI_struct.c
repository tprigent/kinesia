/*!
* \file connect_UI_struct.c
* \brief File with functions used to parse data from UI entries to structure
*/

#include "connect_UI_struct.h"

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