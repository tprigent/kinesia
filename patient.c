//
// Created by salome on 10/02/2021.
//

#include "patient.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
<<<<<<< HEAD



/*allocation d'une chaîne de caractère de longueur lg*/
static int allocateStringPatient(char ** string, int lg) {
    *string = (char *) malloc(sizeof(char)*lg);
    if(*string == (char *) NULL) return -1;
    return 0;
}

/*allocation mémoire des attributs d'une structure Adresse*/
int allocateAdresse(Adresse * a) {

    /*allocation mémoire des chaînes de caractères de la structure Adresse*/
    if (allocateStringPatient(&(a->numMaison), LG_MAX_INFO) !=0) return -1;
    if (allocateStringPatient(&(a->rue), LG_MAX_INFO) !=0) return -1;
    if (allocateStringPatient(&(a->ville), LG_MAX_INFO) !=0) return -1;
    if (allocateStringPatient(&(a->infoComp), LG_MAX_OTHERS) !=0) return -1;
    return 0;
}


/*allocation mémoire d'un patient*/
int allocatePatient(Patient ** p) {
    *p = (Patient *) malloc(sizeof(Patient));

    /*test des allocations de chaque attribut de la structure patient qui ont besoin d'être alloués*/
    if((p == NULL) || (allocateStringPatient(&((*p)->name), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->forename), LG_MAX_INFO) !=0)
    || (allocateAdresse(&((*p)->address)) !=0)
    || (allocateStringPatient(&((*p)->global_pathologies), LG_MAX_OTHERS) !=0)
    || (allocateStringPatient(&((*p)->mail_address), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->metier), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->num_secu), LG_MAX_INFO) !=0)
    || (allocateStringPatient(&((*p)->place_birth), LG_MAX_INFO) !=0)) return -1;

    return 0;
}

/*remplissage/modification des attributs d'une adresse déjà créée et allouée*/
int setAdresse(Adresse * a, char * numM, char * r, int cp, char * v, char * iC) {

    if(a == NULL) return -1;
    /*attribution des paramètres aux attributs de a*/
    strncpy(a->numMaison, numM, LG_MAX_INFO);
    strncpy(a->rue, r, LG_MAX_INFO);
    strncpy(a->ville, v, LG_MAX_INFO);
    strncpy(a->infoComp, iC, LG_MAX_OTHERS);
    a->codePostal = cp;

    /*ajout des 0 terminaux aux chaînes précédemment copiées par sécurité*/
    a->numMaison[strlen(numM)] = '\0';
    a->rue[strlen(r)] = '\0';
    a->ville[strlen(v)] = '\0';
    a->infoComp[strlen(iC)] = '\0';
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
int setPatient(Patient * p, char * name, char * fn, Date bd, char * placeBirth, int g, Adresse ad, int pn, char * ma, char* metier, char * ns, int w, int h, Date fc, char * gp) {

    static int idPatient = 0;

    if(p == NULL) return -1; //si l'instance de patient à remplir est vide, erreur

    /*copie des chaînes de caractères en paramètres dans les attributs de l'instance p)*/
    strncpy(p->place_birth, placeBirth, LG_MAX_INFO);
    strncpy(p->num_secu, ns, LG_MAX_INFO);
    strncpy(p->metier, metier, LG_MAX_INFO);
    strncpy(p->mail_address, ma, LG_MAX_INFO);
    strncpy(p->global_pathologies, gp, LG_MAX_OTHERS);
    strncpy(p->forename, fn, LG_MAX_INFO);
    strncpy(p->name, name, LG_MAX_INFO);

    /*ajout de 0 terminaux par sécurité*/
    p->place_birth[strlen(placeBirth)] = '\0';
    p->num_secu[strlen(ns)] = '\0';
    p->metier[strlen(metier)] = '\0';
    p->mail_address[strlen(ma)] = '\0';
    p->global_pathologies[strlen(gp)] = '\0';
    p->forename[strlen(fn)] = '\0';
    p->name[strlen(name)] = '\0';

    /*attribution des autres attributs*/
    p->address = ad;
    p->first_consultation = fc;
    p->birthdate = bd;
    p->height = h;
    p->phone_number = pn;
    p->weight = w;

    if(g>2 || g<0) return -1;
    p->genre = g;

    /*attribution d'un id unique par patient*/
    p->id = idPatient;

    idPatient++;

    return 0;
=======
#include "Structures.h"
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
        fprintf("Opened database successfully\n");
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
    sqlite3_bind_text(stmt,1,gen->name,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,2,gen->forename,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,3,gen->birthdate.year,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,4,gen->birthdate.month,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,5,gen->birthdate.day,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,6,gen->place_birth,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,7,gen->genre,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,8,gen->adress,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,9,gen->phone_number,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,10,gen->mail_address,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,11,gen->num_secu,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,12,gen->weight,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,13,gen->height,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,14,gen->groupe_sanguin,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,15,gen->first_consultation.year,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,16,gen->first_consultation.month,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,17,gen->first_consultation.day,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,18,gen->global_pathologies,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,19,gen->numMaison,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,20,gen->rue,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,21,gen->codePostal,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,22,gen->ville,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,23,gen->infoComp,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,24,gen->job,-1,SQLITE_TRANSIENT);

    sqlite3_bind_int(stmt,25,gen->id,-1,SQLITE_TRANSIENT);

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
        fprintf("Opened database successfully\n");
    }

    //Creation de la requête
    sql = "INSERT INTO patient (name,forename,birthdate_year,birthdate_month"
          ",birthdate_day,place_birth"
          ",genre,adress,phone_number,mail_adress,num_secu,weight,"
          "height,groupe_sanguin,first_consultation_year,first_consultation_month,"
          "first_consultation_day,global_pathologies,"
          "numMaison,rue,codePostal,ville,infocomp,job) VALUES (?,?,?,?,?,"
          "?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";

    //Préparation de la requête
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    //Ajout des valeurs dans la requête
    sqlite3_bind_text(stmt,1,gen->name,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,2,gen->forename,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,3,gen->birthdate.year,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,4,gen->birthdate.month,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,5,gen->birthdate.day,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,6,gen->place_birth,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,7,gen->genre,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,8,gen->adress,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,9,gen->phone_number,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,10,gen->mail_address,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,11,gen->num_secu,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,12,gen->weight,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,13,gen->height,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,14,gen->groupe_sanguin,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,15,gen->first_consultation.year,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,16,gen->first_consultation.month,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,17,gen->first_consultation.day,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,18,gen->global_pathologies,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,19,gen->numMaison,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,20,gen->rue,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,21,gen->codePostal,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,22,gen->ville,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,23,gen->infoComp,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,24,gen->job,-1,SQLITE_TRANSIENT);

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
>>>>>>> 26133fe21b63012188e5072afc34ac39c9ed5c11
}