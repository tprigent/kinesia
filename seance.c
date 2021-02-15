//
// Created by paul on 13/02/2021.
//

#include "seance.h"
#include "Structures.h"
#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>

//Ajoute une seance dans seance à partir de la struct seance et du patient associé
int addSeance(Seance *seance){

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
    sql = "INSERT INTO patient (idDossier,dateSeance_year,dateSeance_month"
          ",dateSeance_day,dateSeanceSuiv_year"
          ",dateSeanceSuiv_month,dateSeanceSuiv_day,observations,nomSeance) VALUES (?,?,?,?,?,"
          "?,?,?,?)";

    //Préparation de la requête
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    //Ajout des valeurs dans la requête
    sqlite3_bind_int(stmt,1,seance->idDossier,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,2,seance->dateSeance.year,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,3,seance->dateSeance.month,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,4,seance->dateSeance.day,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,5,seance->dateSeanceSuiv.year,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,6,seance->dateSeanceSuiv.month,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,7,seance->dateSeanceSuiv.day,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,8,seance->observations,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,9,seance->nomSeance,-1,SQLITE_TRANSIENT);

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