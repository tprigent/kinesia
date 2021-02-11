//
// Created by salome on 10/02/2021.
//

#include "patient.h"
#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"

int modifyPatient(modifiable_item item,void *val){
    
}

//Ajout d'un patient dans la table patient à partir d'une instance de la struct Patient
int addPatient(Patient *gen){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;
    int dataInt;

    rc = sqlite3_open("/BaseDeDonnee/Bdd.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf("Opened database successfully\n");
    }

    sql = "INSERT INTO patient (name,forename,birthdate,place_birth"
          ",genre,adress,phone_number,mail_adress,num_secu,weight,"
          "height,groupe_sanguin,first_consultation,global_pathologies,"
          "numMaison,rue,codePostal,ville,infocomp) VALUES (?,?,?,?,?,"
          "?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }
    sqlite3_bind_int(stmt,1,gen->id,-1,SQLITE_TRANSIENT)
    sqlite3_bind_text(stmt,2,gen->name,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,3,gen->forename,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,4,gen->birthdate.year,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,5,gen->birthdate.month,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,6,gen->birthdate.day,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,7,gen->place_birth,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,8,gen->genre,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,9,gen->adress,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,10,gen->phone_number,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,11,gen->mail_address,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,12,gen->num_secu,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,13,gen->weight,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,14,gen->height,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,15,gen->groupe_sanguin,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,16,gen->first_consultation.year,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,17,gen->first_consultation.month,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,18,gen->first_consultation.day,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,19,gen->global_pathologies,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,20,gen->numMaison,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,21,gen->rue,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,22,gen->codePostal,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,23,gen->ville,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,24,gen->infoComp,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,24,gen->job,-1,SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if( rc != SQLITE_DONE ){
        fprintf(stderr, "Step error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }
    sqlite3_finalize(stmt);

    sqlite3_close(db);
    return 1;
}