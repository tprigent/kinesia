//
// Created by julien on 09/02/2021.
//

#include <stdio.h>
#include <stdlib.h>
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

void free_date_UI(char *date){
    free(date);
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
    int length = (int) strlen("00/00/0000");
    char *first_consultation = (char*) malloc(length*sizeof(char));
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

void free_formatted_folder_title_UI(char *folder_title){
    free(folder_title);
}

char *get_formatted_folder_infos_UI(Folder *folder){    //TODO: insert breakline every n char
    /*int length = (int) strlen(folder->details);
    int i = 0;
    int c = 0;
    char *formattedInfos = (char*) malloc(600*sizeof(char));
    while(c < length){
        strcat(&formattedInfos[c+i], &folder->details[c]);
        if(length % 50 == 0){
            strcat(formattedInfos, "\n");
            i+=3;
        }
        c++;
    }
    return formattedInfos;*/
    return folder->details;
}

void free_folder_infos_UI(char *infos){
    free(infos);
}

char *get_indicator_files_UI(Folder *folder){
    char *indicator = (char*) malloc(20*sizeof(char));
    char *buffer = (char*) malloc(5*sizeof(char));
    sprintf(buffer, "%d", folder->numberOfFiles);
    strcpy(indicator, "   (");
    strcat(indicator, buffer);
    strcat(indicator, ")");
    return indicator;
}

void free_indicator_files_UI(char *indicator){
    free(indicator);
}