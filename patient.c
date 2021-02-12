//
// Created by salome on 10/02/2021.
//

#include "patient.h"
#include <stdio.h>
#include <stdlib.h>
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
}