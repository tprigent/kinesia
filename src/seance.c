/*!
* \file seance.c
* \brief File with functions to allocate, fill from model requests, and free Session structure
*/

#include "seance.h"
#include "model/structures.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "patient.h"

int allocateStringSession(char **string, int lg) {
    *string = malloc(sizeof(char)*lg+1);
    if(*string == NULL) return -1;
    return 0;
}

int allocateSession(Session *s) {

    if(allocateStringSession(&(s->observations), LG_MAX_INFO) !=0
    || allocateStringSession(&(s->sessionName), LG_MAX_INFO) !=0) return -1;

    return 0;
}

void freeSession(Session *s) {
    free((void *)s->observations);
    free((void *)s->sessionName);
}

static NodeList * newNodeList(char *sName, char *obs, int sdDay, int sdMonth, int sdYear, int nsdDay, int nsdMonth, int nsdYear, int idS, int idFolder, NodeList *nextNode, NodeList *prevNode) {
    NodeList *newNode = malloc(sizeof(NodeList));
    if(newNode != NULL) {
        if(allocateSession(&(newNode->session)) !=0) return NULL;

        strncpy(newNode->session.sessionName, sName, LG_MAX_INFO);
        strncpy(newNode->session.observations, obs, LG_MAX_OTHERS);
        newNode->session.sessionName[LG_MAX_INFO] = '\0';
        newNode->session.observations[LG_MAX_OTHERS] = '\0';

        if(setDate(&(newNode->session.nextSessionDate), nsdDay, nsdMonth, nsdYear) !=0
        || setDate(&(newNode->session.sessionDate), sdDay, sdMonth, sdYear) !=0) return NULL;

        newNode->session.idFolder = idFolder;
        newNode->session.idSession = idS;
        newNode->next = nextNode;
        newNode->previous = prevNode;
    }
    return newNode;
}

static void freeNodeList(NodeList *node) {
    freeSession(&(node->session));
    free(node);
}

void initList(SessionList *l) {
    l->first = NULL;
    l->last = NULL;
    l->current = l->first;
}

int isEmpty(SessionList *l) {
    if(l->first == NULL) return -1;
    return 0;
}

int insertFirst(SessionList *l, char *sName, char *obs, int sdDay, int sdMonth, int sdYear, int nsdDay, int nsdMonth, int nsdYear, int idS, int idFolder) {
    setOnFirst(l);
    NodeList * newNode = newNodeList(sName, obs, sdDay, sdMonth, sdYear, nsdDay, nsdMonth, nsdYear, idS, idFolder, l->first, NULL);
    if(newNode == NULL) return -1;

    if(isEmpty(l)) {

        l->last = newNode;
    }
    l->first->previous = newNode;
    l->first = newNode;

    return -1;
}

int insertLast(SessionList *l, char *sName, char *obs, int sdDay, int sdMonth, int sdYear, int nsdDay, int nsdMonth, int nsdYear, int idS, int idFolder) {
    setOnLast(l);
    NodeList * newNode = newNodeList(sName, obs, sdDay, sdMonth, sdYear, nsdDay, nsdMonth, nsdYear, idS, idFolder, NULL, l->last);
    if(newNode == NULL) return -1;

    l->last->next = newNode;
    l->last = newNode;
    if(isEmpty(l)) {
        l->first = newNode;
    }

    return 0;
}

void deleteFirst(SessionList *l) {
    NodeList * ptr = l->first;
    l->first = l->first->next;
    freeNodeList(ptr);
}

void deleteCurrent(SessionList *l) {
    NodeList *ptr = l->current;
    l->current->next->previous = l->current->previous;
    l->current->previous->next = l->current->next;
    l->current = l->first;
    freeNodeList(ptr);
}

int pointNthElement(SessionList *l, int n) {
    int i;
    setOnFirst(l);
    for(i=1; i<n; i++) {
        setOnNext(l);
        if(isOutOfList(l)) return -1;
    }
    return 0;
}

int deleteNthElement(SessionList *l, int n) {
    if(pointNthElement(l, n) !=0) return -1;
    deleteCurrent(l);
    return 0;
}

void setOnFirst(SessionList *l) {
    l->current = l->first;
}

void setOnLast(SessionList *l) {
    l->current = l->last;
}

void setOnNext(SessionList *l) {
    l->current = l->current->next;
}

int isOutOfList(SessionList *l) {
    if(l->current == NULL) return -1;
    return 0;
}

void freeList(SessionList *l) {
    setOnFirst(l);
    while(!isEmpty(l)) {
        freeNodeList(l->current);
        setOnNext(l);
    }
    free(l);
}

//Ajout d'une seance avec un instance de struct seance
int addSession(Session *session){

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
    sqlite3_bind_int(stmt,1,session->idFolder);
    sqlite3_bind_int(stmt,2,session->sessionDate.year);
    sqlite3_bind_int(stmt,3,session->sessionDate.month);
    sqlite3_bind_int(stmt,4,session->sessionDate.day);
    sqlite3_bind_int(stmt,5,session->nextSessionDate.year);
    sqlite3_bind_int(stmt,6,session->nextSessionDate.month);
    sqlite3_bind_int(stmt,7,session->nextSessionDate.day);
    sqlite3_bind_text(stmt,8,session->observations,-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,9,session->sessionName,-1,SQLITE_TRANSIENT);

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

//Recupération d'une séance
Session * getSession(int idSession){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt=NULL;
    Session *session;

    //Ouverture de la bdd
    rc = sqlite3_open(DB_PATH, &db);

    //Test de l'ouverture
    if( rc ) {
        fprintf(stderr, "Can't open model: %s\n", sqlite3_errmsg(db));
        return NULL;
    } else {
        fprintf(stderr,"Opened model successfully\n");
    }

    //Creation de la requête
    sql = "SELECT * FROM seance WHERE idSeance=?";

    sqlite3_bind_int(stmt,-1,idSession);

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    while(sqlite3_step(stmt) == SQLITE_ROW){

    }
    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return session;

}