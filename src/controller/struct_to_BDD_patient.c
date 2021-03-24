//
// Created by salome on 22/03/2021.
//

#include "struct_to_BDD_patient.h"
#include "../model/structures.h"
#include "../model/patient_manager.h"
#include <sqlite3.h>

/*!
 * \brief This function makes an SQL request, modify a Patient entry in patient table from a Patient struct.
 *
 * \param[in] struct Patient to be modified
 *
 * \param[out] int, 0 if an error occurred, 1 otherwise.
*/
int modifyPatient(Patient *gen){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;

    //Opening database
    rc = sqlite3_open(DB_PATH, &db);

    //Testing opening
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr,"Opened database successfully\n");
    }

    //Creating the request
    sql = "UPDATE patient SET firstname=?,name=?,birthdate_year=?,birthdate_month=?,"
          "birthdate_day=?,place_birth=?,"
          "gender=?,phone_number=?,mail_adress=?,ssn=?,weight=?,"
          "height=?,first_consultation_year=?,"
          "first_consultation_month=?,first_consultation_day=?,global_pathologies=?,"
          "number=?,street=?,postCode=?,city=?,other_info=?,job=?,isArchived=? WHERE id=?";

    //Preparing the request
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    //Adding values to the request
    int i;
    i=1;
    sqlite3_bind_text(stmt,i++,gen->firstname,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->name,-1,SQLITE_TRANSIENT);
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
    sqlite3_bind_text(stmt,i++,"N/A",-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.street,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.postCode,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.city,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.other_info,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->job,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i++,gen->isArchived);

    sqlite3_bind_int(stmt,i++,(int)gen->id);

    //Executing the request
    rc = sqlite3_step(stmt);
    if( rc != SQLITE_DONE ){
        fprintf(stderr, "Step error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }
    sqlite3_finalize(stmt);

    //Closing database
    sqlite3_close(db);
    return 1;
}

/*!
 * \brief This function makes an SQL request, add a Patient entry in patient table from a Patient struct.
 * \brief Return 0 if an error occurred, 1 otherwise.
 *
 * \param[in] struct Patient to be add
 *
 * \param[out] int, 0 if an error occurred, 1 otherwise.
*/
int addPatient(Patient *gen){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;

    //Opening database
    rc = sqlite3_open(DB_PATH, &db);

    //Testing the opening
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr,"Opened database successfully\n");
    }

    //Creating the request
    sql = "INSERT INTO patient (firstname,name,birthdate_year,birthdate_month"
          ",birthdate_day,place_birth"
          ",gender,phone_number,mail_adress,ssn,weight,"
          "height,first_consultation_year,first_consultation_month,"
          "first_consultation_day,global_pathologies,"
          "number,street,postCode,city,other_info,job,isArchived) VALUES (?,?,?,?,?,"
          "?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";

    //Préparing the request
    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    //Adding values to the request
    int i;
    i=1;
    sqlite3_bind_text(stmt,i++,gen->firstname,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->name,-1,SQLITE_TRANSIENT);
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
    sqlite3_bind_text(stmt,i++,"N/A",-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.street,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.postCode,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.city,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->address.other_info,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,i++,gen->job,-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,i,gen->isArchived);

    //Executing the request
    rc = sqlite3_step(stmt);
    if( rc != SQLITE_DONE ){
        fprintf(stderr, "Step error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }
    sqlite3_finalize(stmt);

    //Closing database
    sqlite3_close(db);
    return 1;
}

/*!
 * \brief This function makes an SQL request, removes a patient and its related folders and sessions from the database.
 *
 * \param[in] a Folder struct.
 *
 * \param[out] int, 1 if an error occurred, 0 otherwise
*/
int deletePatient(int id){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc1,rc2,rc3;
    char *sql1;
    char *sql2;
    char *sql3;
    sqlite3_stmt *stmt1;
    sqlite3_stmt *stmt2;
    sqlite3_stmt *stmt3;

    //Opening database
    rc1 = sqlite3_open("/home/paul/Bdd/TestBdd.db", &db);

    //Testing the opening
    if( rc1 ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr,"Opened database successfully\n");
    }

//Creating the request
    sql1 = "DELETE FROM seance WHERE idFolder IN (SELECT idFolder FROM folder WHERE idPatient=?)";
    sql2 = "DELETE FROM folder WHERE idPatient=?";
    sql3 = "DELETE FROM gens WHERE id=?";

    //Préparing the requests
    rc1 = sqlite3_prepare_v2(db,sql1,-1,&stmt1,NULL);
    rc2 = sqlite3_prepare_v2(db,sql2,-1,&stmt2,NULL);
    rc3 = sqlite3_prepare_v2(db,sql3,-1,&stmt3,NULL);
    if( rc1 != SQLITE_OK || rc2 != SQLITE_OK || rc3 != SQLITE_OK ){
        fprintf(stderr, "Prepare error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    //Adding values to the requests
    sqlite3_bind_int(stmt1,1,id);
    sqlite3_bind_int(stmt2,1,id);
    sqlite3_bind_int(stmt3,1,id);

    //Executing the request
    while(sqlite3_step(stmt1) == SQLITE_ROW){}
    sqlite3_step(stmt2);
    sqlite3_step(stmt3);

    sqlite3_finalize(stmt1);
    sqlite3_finalize(stmt2);
    sqlite3_finalize(stmt3);

    //Closing database
    sqlite3_close(db);
    return 1;
}