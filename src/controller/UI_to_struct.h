/*!
* \file UI_to_struct.h
* \brief File with functions used to parse data from UI entries to structures
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../model/structures.h"


#ifndef LOGICIEL_KINE_CONNECT_UI_STRUCT_H
#define LOGICIEL_KINE_CONNECT_UI_STRUCT_H

Date *parseDate(char *stringDate);
int convertToInt(char *stringNumber);
void parseAddress(char *stringAddress, Address *result);

#endif //LOGICIEL_KINE_CONNECT_UI_STRUCT_H
