/*!
* \file seance.c
* \brief File with functions to allocate, fill from model requests, and free Session structure
*/

#include "session_manager.h"
#include "structures.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "patient_manager.h"


void freeSession(Session *s) {
    if(s->observations!=NULL) free((void *)s->observations);
    if(s->sessionName!=NULL) free((void *)s->sessionName);
}

static Session * initSession(Session *newS, char *sName, char *obs, int sdDay, int sdMonth, int sdYear, int nsdDay, int nsdMonth, int nsdYear, int idS, int idFolder) {

    newS->sessionName = (char *) malloc(sizeof(char)*LG_MAX_INFO + 1);
    newS->observations = (char *) malloc(sizeof(char)*LG_MAX_OTHERS + 1);

    if(newS->sessionName !=NULL && newS->observations != NULL) {
        if(sName == NULL) strcpy(newS->sessionName, "\0");
        else {
            strncpy(newS->sessionName, sName, LG_MAX_INFO);
            newS->sessionName[LG_MAX_INFO] = '\0';
        }

        if(obs == NULL) strcpy(newS->observations, "\0");
        else {
            strncpy(newS->observations, obs, LG_MAX_OTHERS);
            newS->observations[LG_MAX_OTHERS] = '\0';
        }

        setDate(&(newS->nextSessionDate), nsdDay, nsdMonth, nsdYear);
        setDate(&(newS->sessionDate), sdDay, sdMonth, sdYear);

        newS->idFolder = idFolder;
        newS->idSession = idS;

    }

    else freeSession(newS);

    return newS;
}

static NodeList * newNodeList(char *sName, char *obs, int sdDay, int sdMonth, int sdYear, int nsdDay, int nsdMonth, int nsdYear, int idS, int idFolder, NodeList *nextNode, NodeList *prevNode) {
    NodeList *newNode = (NodeList *) malloc(sizeof(NodeList));

    if(newNode == NULL) return NULL;
    newNode->session = *initSession(&newNode->session, sName, obs, sdDay, sdMonth, sdYear, nsdDay, nsdMonth, nsdYear, idS, idFolder);

    newNode->next = nextNode;
    newNode->previous = prevNode;
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

    if(isEmpty(l) !=0) {

        l->last = newNode;
    }
    else l->first->previous = newNode;
    l->first = newNode;

    return 0;
}

int insertLast(SessionList *l, char *sName, char *obs, int sdDay, int sdMonth, int sdYear, int nsdDay, int nsdMonth, int nsdYear, int idS, int idFolder) {
    setOnLast(l);
    NodeList * newNode = newNodeList(sName, obs, sdDay, sdMonth, sdYear, nsdDay, nsdMonth, nsdYear, idS, idFolder, NULL, l->last);
    if(newNode == NULL) return -1;

    if(isEmpty(l) !=0) {
        l->first = newNode;
    }
    else l->last->next = newNode;
    l->last = newNode;

    return 0;
}

void deleteFirst(SessionList *l) {
    NodeList * ptr = l->first;
    l->first = l->first->next;
    freeNodeList(ptr);
}

void deleteCurrent(SessionList *l) {
    NodeList *ptr = l->current;
    if(l->current == l->last) l->last = l->current->previous;
    if(l->current == l->first) l->first = l->current->next;
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
    if(l->current == NULL) l->current = NULL;
    l->current = l->current->next;
}

int isOutOfList(SessionList *l) {
    if(l->current == NULL) return -1;
    return 0;
}

void freeList(SessionList *l) {
    setOnFirst(l);
    while(isOutOfList(l) ==0) {
        NodeList *temp = l->current->next;
        freeNodeList(l->current);
        l->current = temp;
    }
    free(l);
}
