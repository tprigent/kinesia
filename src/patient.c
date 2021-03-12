/*!
* \file patient.c
* \brief File with functions to allocate, fill from model requests, and free Patient structure
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "patient.h"

/*!
 * \brief [Debug] Print a given patient to the terminal
 *
 * \param[in] patient Patient to be displayed
 * \param[in] context Brief text to understand when the function has been called
*/
void printPatient(Patient *patient, char *context){
    printf("******* Displaying patient #%d *******\n", patient->id);

    printf("\033[0;31m");
    printf("-> Context: %s\n", context);
    printf("\033[0m");

    printf("Name: %s ", patient->name);
    printf("Firstname: %s\n", patient->firstname);
    printf("Gender: ");
    printGender(patient->gender);
    printf("\n");

    printf("Birthdate: %d/%d/%d\n", patient->birthdate.day, patient->birthdate.month, patient->birthdate.year);
    printf("Place of birth: %s\n", patient->place_birth);
    printf("Address: %s %s, %s %s (%s)\n", patient->address.number, patient->address.street, patient->address.postCode, patient->address.city, patient->address.other_info);
    printf("Phone: %s\n", patient->phone_number);
    printf("Mail: %s\n", patient->mail_address);
    printf("Job: %s\n", patient->job);

    printf("Social security number: %s\n", patient->ssn);
    printf("Global pathologies: %s\n", patient->global_pathologies);
    printf("Height: %s\n", patient->height);
    printf("Weight: %s\n", patient->weight);
    printf("First consultation: %d/%d/%d\n", patient->first_consultation.day, patient->first_consultation.month, patient->first_consultation.year);

    printf("******* End of the patient display *******\n");
}

/*!
 * \brief [Debug] Print a Gender enum to the terminal
 *
 * \param[in] gender Gender to be displayed
*/
void printGender(Genre gender){
    if(gender == MAN) printf("man");
    else if(gender == WOMAN) printf("woman");
    else if(gender == OTHER) printf("other");
    else printf("error");
}


/*allocation d'une chaîne de caractère de longueur lg*/
static int allocateStringPatient(char ** string, int lg) {
    *string = (char *) malloc(sizeof(char)*lg);
    if(*string == (char *) NULL) return -1;
    return 0;
}

/*allocation mémoire des attributs d'une structure Adresse*/
int allocateAddress(Address * a) {

    /*allocation mémoire des chaînes de caractères de la structure Adresse*/
    if (allocateStringPatient(&(a->number), LG_MAX_INFO) !=0) return -1;
    if (allocateStringPatient(&(a->street), LG_MAX_INFO) !=0) return -1;
    if (allocateStringPatient(&(a->city), LG_MAX_INFO) !=0) return -1;
    if (allocateStringPatient(&(a->other_info), LG_MAX_OTHERS) !=0) return -1;
    if (allocateStringPatient(&(a->postCode), LG_MAX_INFO) !=0) return -1;
    return 0;
}


/*allocation mémoire d'un patient*/
int allocatePatient(Patient ** p) {
    *p = (Patient *) malloc(sizeof(Patient));

    /*test des allocations de chaque attribut de la structure patient qui ont besoin d'être alloués*/
    if((p == NULL) || (allocateStringPatient(&((*p)->name), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->firstname), LG_MAX_INFO) !=0)
    || (allocateAddress(&((*p)->address)) !=0)
    || (allocateStringPatient(&((*p)->global_pathologies), LG_MAX_OTHERS) !=0)
    || (allocateStringPatient(&((*p)->mail_address), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->job), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->ssn), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->phone_number), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->place_birth), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->height), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->weight), LG_MAX_INFO) !=0)) return -1;

    return 0;
}

/*désallocation d'une instance d'Address*/
void freeAddress(Address * a) {
    free((void *) a->number);
    free((void *) a->street);
    free((void *) a->postCode);
    free((void *) a->city);
    free((void *) a->other_info);
}

/*désallocation d'une instance de Patient*/
void freePatient(Patient ** p) {
    free((void *) (*p)->phone_number);
    free((void *) (*p)->firstname);
    free((void *) (*p)->global_pathologies);
    free((void *) (*p)->place_birth);
    free((void *) (*p)->name);
    free((void *) (*p)->mail_address);
    free((void *) (*p)->job);
    free((void *) (*p)->ssn);
    free((void *) (*p)->height);
    free((void *) (*p)->weight);
    freeAddress(&((*p)->address));
    free((void *) *p);
}

/*remplissage/modification des attributs d'une adresse déjà créée et allouée*/
int setAddress(Address * a, char * numM, char * r, char * cp, char * v, char * iC) {

    if(a == NULL) return -1;
    /*attribution des paramètres aux attributs de a*/
    strncpy(a->number, numM, LG_MAX_INFO);
    strncpy(a->street, r, LG_MAX_INFO);
    strncpy(a->city, v, LG_MAX_INFO);
    strncpy(a->other_info, iC, LG_MAX_OTHERS);
    strncpy(a->postCode, cp, LG_MAX_INFO);

    /*ajout des 0 terminaux aux chaînes précédemment copiées par sécurité*/
    a->number[strlen(numM)] = '\0';
    a->street[strlen(r)] = '\0';
    a->city[strlen(v)] = '\0';
    a->other_info[strlen(iC)] = '\0';
    a->postCode[strlen(cp)] = '\0';
    return 0;
}

/*remplissage/modification des attributs d'une adresse déjà créée et allouée*/
int setDate(Date * d, int j, int m, int a) {
    if(d == NULL || j>31 || j <=0 || m <= 0 || m > 12 || a<=0) return -1;
    d->day = j;
    d->month = m;
    d->year = a;
    return 0;
}

/*remplissage/modification des attributs d'une adresse déjà créée et allouée*/
int setPatient(Patient * p, char * name, char * fn, Date bd, char * placeBirth, int g, Address ad, char* pn, char * ma, char* job, char * ns, char * w, char * h, Date fc, char * gp,unsigned int idPatient) {

    if (p == NULL) return -1; //si l'instance de patient à remplir est vide, erreur

    /*copie des chaînes de caractères en paramètres dans les attributs de l'instance p)*/
    strncpy(p->place_birth, placeBirth, LG_MAX_INFO);
    strncpy(p->ssn, ns, LG_MAX_INFO);
    strncpy(p->job, job, LG_MAX_INFO);
    strncpy(p->mail_address, ma, LG_MAX_INFO);
    strncpy(p->global_pathologies, gp, LG_MAX_OTHERS);
    strncpy(p->firstname, fn, LG_MAX_INFO);
    strncpy(p->name, name, LG_MAX_INFO);
    strncpy(p->phone_number,pn,LG_MAX_INFO);
    strncpy(p->height,h,LG_MAX_INFO);
    strncpy(p->weight,w,LG_MAX_INFO);

    /*ajout de 0 terminaux par sécurité*/
    p->place_birth[strlen(placeBirth)] = '\0';
    p->ssn[strlen(ns)] = '\0';
    p->job[strlen(job)] = '\0';
    p->mail_address[strlen(ma)] = '\0';
    p->global_pathologies[strlen(gp)] = '\0';
    p->firstname[strlen(fn)] = '\0';
    p->name[strlen(name)] = '\0';
    p->phone_number[strlen(pn)] = '\0';
    p->height[strlen(h)] = '\0';
    p->weight[strlen(w)] = '\0';

    /*attribution des autres attributs*/
    p->address = ad;
    p->first_consultation = fc;
    p->birthdate = bd;

    if (g > 2 || g < 0) return -1;
    p->gender = g;

    /*attribution d'un id unique par patient*/
    p->id = idPatient;

    return 0;
}

//Nombre de patients
int getNbPatient(){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;

    //Ouverture de la bdd
    rc = sqlite3_open(DB_PATH, &db);

    //Test de l'ouverture
    if( rc ) {
        fprintf(stderr, "Can't open model: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr,"Opened model successfully\n");
    }

    //Creation de la requête
    sql = "SELECT * FROM patient";

    //Préparation de la requête
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    //Execution de la requête
    rc=0;
    while(sqlite3_step(stmt) == SQLITE_ROW) {
        rc++;
    }

    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return rc;
}

//Nom et prenom d'un patient
char* getNameFirstnamePatient(int id){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;
    char* nom;

    //Ouverture de la bdd
    rc = sqlite3_open(DB_PATH, &db);

    //Test de l'ouverture
    if( rc ) {
        fprintf(stderr, "Can't open model: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr,"Opened model successfully\n");
    }

    //Creation de la requête
    sql = "SELECT name,firstname FROM patient WHERE id=?";

    //Préparation de la requête
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return NULL;
    }

    sqlite3_bind_int(stmt,1,id);

    //Execution de la requête
    rc = sqlite3_step(stmt);

    if(allocateStringPatient(&nom,LG_MAX_INFO*2)==-1){
        fprintf(stderr,"Erreur allocation getNomPrenom");
        return NULL;
    }

    strcpy(nom,(char*)sqlite3_column_text(stmt,0));
    char* space=" ";
    strcat(nom,space);
    strcat(nom,(char*)sqlite3_column_text(stmt,1));

    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return nom;

}

//Modification d'un patient
int modifyPatient(Patient *gen){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;

    //Ouverture de la bdd
    rc = sqlite3_open(DB_PATH, &db);

    //Test de l'ouverture
    if( rc ) {
        fprintf(stderr, "Can't open model: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr,"Opened model successfully\n");
    }

    //Creation de la requête
    sql = "UPDATE patient SET name=?,firstname=?,birthdate_year=?,birthdate_month=?,"
          "birthdate_day=?,place_birth=?,"
          "gender=?,phone_number=?,mail_adress=?,ssn=?,weight=?,"
          "height=?,first_consultation_year=?,"
          "first_consultation_month=?,first_consultation_day=?,global_pathologies=?,"
          "number=?,street=?,postCode=?,city=?,other_info=?,job=? WHERE id=?";

    //Préparation de la requête
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    //Ajout des valeurs dans la requête
    int i;
    i=1;
    sqlite3_bind_text(stmt,i++,gen->name,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->firstname,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i++,gen->birthdate.year);
    sqlite3_bind_int(stmt,i++,gen->birthdate.month);
    sqlite3_bind_int(stmt,i++,gen->birthdate.day);
    sqlite3_bind_text(stmt,i++,gen->place_birth,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i++,gen->gender);
    sqlite3_bind_text(stmt,i++,gen->phone_number,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->mail_address,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->ssn,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->weight,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->height,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i++,gen->first_consultation.year);
    sqlite3_bind_int(stmt,i++,gen->first_consultation.month);
    sqlite3_bind_int(stmt,i++,gen->first_consultation.day);
    sqlite3_bind_text(stmt,i++,gen->global_pathologies,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.number,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.street,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.postCode,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.city,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.other_info,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->job,-1,SQLITE_TRANSIENT);

    sqlite3_bind_int(stmt,i++,(int)gen->id);

    //Execution de la requête
    rc = sqlite3_step(stmt);
    if( rc != SQLITE_DONE ){
        fprintf(stderr, "Step error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }
    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return 1;
}

//Ajout d'un patient dans la table patient à partir d'une instance de la struct Patient
int addPatient(Patient *gen){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;

    //Ouverture de la bdd
    rc = sqlite3_open(DB_PATH, &db);

    //Test de l'ouverture
    if( rc ) {
        fprintf(stderr, "Can't open model: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr,"Opened model successfully\n");
    }

    //Creation de la requête
    sql = "INSERT INTO patient (name,firstname,birthdate_year,birthdate_month"
          ",birthdate_day,place_birth"
          ",gender,phone_number,mail_adress,ssn,weight,"
          "height,first_consultation_year,first_consultation_month,"
          "first_consultation_day,global_pathologies,"
          "number,street,postCode,city,other_info,job) VALUES (?,?,?,?,?,"
          "?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";

    //Préparation de la requête
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    //Ajout des valeurs dans la requête
    int i;
    i=1;
    sqlite3_bind_text(stmt,i++,gen->name,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->firstname,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i++,gen->birthdate.year);
    sqlite3_bind_int(stmt,i++,gen->birthdate.month);
    sqlite3_bind_int(stmt,i++,gen->birthdate.day);
    sqlite3_bind_text(stmt,i++,gen->place_birth,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i++,gen->gender);
    sqlite3_bind_text(stmt,i++,gen->phone_number,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->mail_address,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->ssn,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->weight,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->height,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i++,gen->first_consultation.year);
    sqlite3_bind_int(stmt,i++,gen->first_consultation.month);
    sqlite3_bind_int(stmt,i++,gen->first_consultation.day);
    sqlite3_bind_text(stmt,i++,gen->global_pathologies,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.number,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.street,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.postCode,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.city,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.other_info,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->job,-1,SQLITE_TRANSIENT);

    //Execution de la requête
    rc = sqlite3_step(stmt);
    if( rc != SQLITE_DONE ){
        fprintf(stderr, "Step error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }
    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return 1;
}


Patient* getPatient(int id){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;
    Patient *patient;
    Address adresse;
    Date birthDate;
    Date firstRdDdate;

    if(allocatePatient(&patient) == -1 || allocateAddress(&adresse) == -1 ){
        fprintf(stderr,"Erreur d'allocation\n");
    }

    //Ouverture de la bdd
    rc = sqlite3_open(DB_PATH, &db);

    //Test de l'ouverture
    if( rc ) {
        fprintf(stderr, "Can't open model: %s\n", sqlite3_errmsg(db));
        return NULL;
    } else {
        fprintf(stdout,"Opened model successfully\n");
    }

    //Creation de la requête
    sql = "SELECT * FROM patient WHERE id=?";

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return NULL;
    }

    sqlite3_bind_int(stmt,1,id);

    sqlite3_step(stmt);

    if(setDate(&birthDate,
               sqlite3_column_int(stmt,5),
               sqlite3_column_int(stmt,4),
               sqlite3_column_int(stmt,3)) == -1 ){
            fprintf(stderr,"Erreur setDate birthdate\n");
    }
    if(setDate(&firstRdDdate,
               sqlite3_column_int(stmt,15),
               sqlite3_column_int(stmt,14),
               sqlite3_column_int(stmt,13)) == -1 ){
            fprintf(stderr,"Erreur setDate first RDV\n");
    }

    if(setAddress(&adresse,(char*)sqlite3_column_text(stmt,17),
                  (char*)sqlite3_column_text(stmt,18),
                  (char*)sqlite3_column_text(stmt,19),
                  (char*)sqlite3_column_text(stmt,20),
                  (char*)sqlite3_column_text(stmt,21)) == -1 ) {
            fprintf(stderr, "Erreur set address\n");
    }

    if(setPatient(patient,(char*)sqlite3_column_text(stmt,1),(char*)sqlite3_column_text(stmt,2),birthDate,
                      (char*)sqlite3_column_text(stmt,6),sqlite3_column_int(stmt,7),
                      adresse,(char*)sqlite3_column_text(stmt,8),
                      (char*)sqlite3_column_text(stmt,9),(char*)sqlite3_column_text(stmt,22),
                      (char*)sqlite3_column_text(stmt,10),(char*)sqlite3_column_text(stmt,11),
                  (char*)sqlite3_column_text(stmt,12),firstRdDdate,(char*)sqlite3_column_text(stmt,16),(unsigned int)id) != 0)
        fprintf(stderr,"Erreur setPatient");

    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return patient;

}
