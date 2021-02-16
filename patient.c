//
// Created by salome on 10/02/2021.
//

#include "patient.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



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
    || (allocateStringPatient(&((*p)->place_birth), LG_MAX_INFO) !=0)) return -1;

    return 0;
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
int setPatient(Patient * p, char * name, char * fn, Date bd, char * placeBirth, int g, Address ad, int pn, char * ma, char* job, char * ns, int w, int h, Date fc, char * gp) {

    static int idPatient = 0;

    if (p == NULL) return -1; //si l'instance de patient à remplir est vide, erreur

    /*copie des chaînes de caractères en paramètres dans les attributs de l'instance p)*/
    strncpy(p->place_birth, placeBirth, LG_MAX_INFO);
    strncpy(p->ssn, ns, LG_MAX_INFO);
    strncpy(p->job, job, LG_MAX_INFO);
    strncpy(p->mail_address, ma, LG_MAX_INFO);
    strncpy(p->global_pathologies, gp, LG_MAX_OTHERS);
    strncpy(p->firstname, fn, LG_MAX_INFO);
    strncpy(p->name, name, LG_MAX_INFO);

    /*ajout de 0 terminaux par sécurité*/
    p->place_birth[strlen(placeBirth)] = '\0';
    p->ssn[strlen(ns)] = '\0';
    p->job[strlen(job)] = '\0';
    p->mail_address[strlen(ma)] = '\0';
    p->global_pathologies[strlen(gp)] = '\0';
    p->firstname[strlen(fn)] = '\0';
    p->name[strlen(name)] = '\0';

    /*attribution des autres attributs*/
    p->address = ad;
    p->first_consultation = fc;
    p->birthdate = bd;
    p->height = h;
    p->phone_number = pn;
    p->weight = w;

    if (g > 2 || g < 0) return -1;
    p->gender = g;

    /*attribution d'un id unique par patient*/
    p->id = idPatient;

    idPatient++;

    return 0;
}

#include "structures.h"
#include "sqlite3.h"

//Modification d'un patient
int modifyPatient(Patient *gen){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;

    //Ouverture de la bdd
    rc = sqlite3_open("/BaseDeDonnee/Bdd.db", &db);

    //Test de l'ouverture
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr,"Opened database successfully\n");
    }

    //Creation de la requête
    sql = "UPDATE patient SET name=?,forename=?,birthdate_year=?,birthdate_month=?,"
          "birthdate_day=?,place_birth=?,"
          "genre=?,adress=?,phone_number=?,mail_adress=?,num_secu=?,weight=?,"
          "height=?,groupe_sanguin=?,first_consultation_year=?,global_pathologies,"
          "first_consultation_month=?,first_consultation_day=?,"
          "numMaison=?,rue=?,codePostal=?,ville=?,infocomp=?,job=? WHERE id=?";

    //Préparation de la requête
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    //Ajout des valeurs dans la requête
    int i;
    i=0;
    sqlite3_bind_text(stmt,i++,gen->name,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->forename,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i++,gen->birthdate.year);
    sqlite3_bind_int(stmt,i++,gen->birthdate.month);
    sqlite3_bind_int(stmt,i++,gen->birthdate.day);
    sqlite3_bind_text(stmt,i++,gen->place_birth,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i++,gen->genre);
    sqlite3_bind_int(stmt,i++,gen->phone_number);
    sqlite3_bind_text(stmt,i++,gen->mail_address,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->num_secu,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i++,gen->weight);
    sqlite3_bind_int(stmt,i++,gen->height);
    sqlite3_bind_int(stmt,i++,gen->first_consultation.year);
    sqlite3_bind_int(stmt,i++,gen->first_consultation.month);
    sqlite3_bind_int(stmt,i++,gen->first_consultation.day);
    sqlite3_bind_text(stmt,i++,gen->global_pathologies,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.numMaison,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.rue,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i++,gen->address.codePostal);
    sqlite3_bind_text(stmt,i++,gen->address.ville,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.infoComp,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->job,-1,SQLITE_TRANSIENT);

    sqlite3_bind_int(stmt,25,(int)gen->id);

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
    rc = sqlite3_open("/BaseDeDonnee/Bdd.db", &db);

    //Test de l'ouverture
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr,"Opened database successfully\n");
    }

    //Creation de la requête
    sql = "INSERT INTO patient (name,forename,birthdate_year,birthdate_month"
          ",birthdate_day,place_birth"
          ",genre,adress,phone_number,mail_adress,num_secu,weight,"
          "height,first_consultation_year,first_consultation_month,"
          "first_consultation_day,global_pathologies,"
          "numMaison,rue,codePostal,ville,infocomp,job) VALUES (?,?,?,?,?,"
          "?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";

    //Préparation de la requête
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    //Ajout des valeurs dans la requête
    int i;
    i=0;
    sqlite3_bind_text(stmt,i++,gen->name,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->forename,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i++,gen->birthdate.year);
    sqlite3_bind_int(stmt,i++,gen->birthdate.month);
    sqlite3_bind_int(stmt,i++,gen->birthdate.day);
    sqlite3_bind_text(stmt,i++,gen->place_birth,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i++,gen->genre);
    sqlite3_bind_int(stmt,i++,gen->phone_number);
    sqlite3_bind_text(stmt,i++,gen->mail_address,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->num_secu,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i++,gen->weight);
    sqlite3_bind_int(stmt,i++,gen->height);
    sqlite3_bind_int(stmt,i++,gen->first_consultation.year);
    sqlite3_bind_int(stmt,i++,gen->first_consultation.month);
    sqlite3_bind_int(stmt,i++,gen->first_consultation.day);
    sqlite3_bind_text(stmt,i++,gen->global_pathologies,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.numMaison,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.rue,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i++,gen->address.codePostal);
    sqlite3_bind_text(stmt,i++,gen->address.ville,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.infoComp,-1,SQLITE_TRANSIENT);
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