//
// Created by julien on 09/02/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "connect_struct_UI.h"

/* Create a function that change int to string */
void tostring(char str[], int num){
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

char *get_name_UI(Patient *patient){
    char *name = (char*) malloc(sizeof(patient->name)+sizeof(patient->forename)+sizeof(char));
    strcpy(name, patient->forename);
    strcat(name, " ");
    strcat(name, patient->name);

    return name;
}

void free_name_UI(char *name){
    free(name);
}


char *get_birthdate_UI(Patient *patient){
    char *birthdate = (char*) malloc(11*sizeof(char));
    char *day = (char*) malloc(2*sizeof(char));
    char *month = (char*) malloc(2*sizeof(char));
    char *year = (char*) malloc(4*sizeof(char));
    tostring(day, patient->birthdate.day);
    tostring(month, patient->birthdate.month);
    tostring(year, patient->birthdate.year);

    strcpy(birthdate, day);
    strcat(birthdate, "/");
    strcat(birthdate, month);
    strcat(birthdate, "/");
    strcat(birthdate, year);
    strcat(birthdate, "\0");

    free(day);
    free(month);
    free(year);

    return birthdate;
}

void free_birthdate_UI(char *birthdate){
    free(birthdate);
}

