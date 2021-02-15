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
    char day[3];
    char month[3];
    char year[5];
    tostring(day, patient->birthdate.day);
    tostring(month, patient->birthdate.month);
    tostring(year, patient->birthdate.year);

    strcpy(birthdate, day);
    strcat(birthdate, "/");
    strcat(birthdate, month);
    strcat(birthdate, "/");
    strcat(birthdate, year);
    strcat(birthdate, "\0");

    return birthdate;
}

void free_birthdate_UI(char *birthdate){
    free(birthdate);
}

char *get_job_UI(Patient *patient){
    return patient->job;
}

char *get_height_weight_UI(Patient *patient){
    char *height_weight = (char*) malloc(40*sizeof(char));
    char height_m[2];
    char height_cm[3];
    char weight[4];
    int int_height_m = (int) patient->height/100;
    int int_height_cm = patient->height - int_height_m*100;

    tostring(height_m, int_height_m);
    tostring(height_cm, int_height_cm);
    tostring(weight, patient->weight);

    strcpy(height_weight, weight);
    strcat(height_weight, "kg   ;   ");
    strcat(height_weight, height_m);
    strcat(height_weight, ".");
    strcat(height_weight, height_cm);
    strcat(height_weight, "m");
    strcat(height_weight, "\0");

    return height_weight;
}

void free_height_weight_UI(char *height_weight){
    free(height_weight);
}

char *get_global_pathologies_UI(Patient *patient){
    return patient->global_pathologies;
}

char *get_first_consultation_UI(Patient *patient){
    char *first_consultation = (char*) malloc(35*sizeof(char));
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

void free_first_consultation_UI(char *first_consultation){
    free(first_consultation);
}