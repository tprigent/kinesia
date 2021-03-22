//
// Created by salome on 22/03/2021.
//

#include "BDD_to_struct_folder.h"
#include <sqlite3.h>
#include "../model/structures.h"
#include <stdlib.h>
#include <stdio.h>
#include "../model/folder_manager.h"

Folder* getFolder(int idFolder){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt=NULL;
    Folder *folder=NULL;

    if(allocateFolder(&folder) == -1){
        fprintf(stderr,"Erreur alloc folder\n");
        return NULL;
    }

    //Ouverture de la bdd
    rc = sqlite3_open(DB_PATH, &db);

    //Test de l'ouverture
    if( rc ) {
        fprintf(stderr, "Can't open model: %s\n", sqlite3_errmsg(db));
        return NULL;
    } else {
        fprintf(stderr,"Opened database successfully\n");
    }

    //Creation de la requête
    sql = "SELECT * FROM folder WHERE idFolder=?";

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_bind_int(stmt,1,idFolder);

    sqlite3_step(stmt);

    if(setFolder(folder,(char*)sqlite3_column_text(stmt,1),(char*)sqlite3_column_text(stmt,2),
                 (char*)sqlite3_column_text(stmt,3),sqlite3_column_int(stmt,6),
                 sqlite3_column_int(stmt,5),sqlite3_column_int(stmt,4),
                 sqlite3_column_int(stmt,7),sqlite3_column_int(stmt,0),
                 sqlite3_column_int(stmt,8)) == -1){

        fprintf(stderr,"Erreur set folder");
        return NULL;

    }

    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return folder;

}