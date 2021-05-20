/*!
* \file session_manager.c
* \brief File with functions to allocate, fill from model requests, and free Session structure
*/

#include "session_manager.h"
#include "structures.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "patient_manager.h"
#include "../controller/display_helpers.h"
#include "../controller/struct_to_BDD_session.h"

/*!
* This function creates a new session with default attributes in BDD.
*
* \param[in] idFolder, the folder id to attach the session.
*/
void createNewSession(int idFolder){
    /* ALLOCATION */
    Session *session = (Session*) malloc(sizeof(Session));
    session->idFolder = idFolder;
    session->idSession = 0;
    session->sessionName = (char*) malloc(LG_MAX_INFO*sizeof(char));
    session->observations = (char*) malloc(LG_MAX_OBSERVATIONS*sizeof(char));
    session->nextSessionHour = (char*) malloc(LG_MAX_INFO*sizeof(char));

    char *date = get_current_date();

    /* SESSION NAME */
    strcpy(session->sessionName, "Séance du ");
    strcat(session->sessionName, date);

    /* SESSION OBSERVATIONS */
    strcpy(session->observations, "Remarques");

    /*SESSION DATES */
    session->sessionDate = *parseDate(date);
    session->nextSessionDate = *parseDate(date);
    strcpy(session->nextSessionHour, "12:00");

    /* OTHER */
    session->isRealSession = 1;


    /* ADD SESSION IN BDD */
    addSession(session);

    /* FREE */
    free(date);
    freeSession(session);
}

/*!
 * \brief Create and allocate an empty session
 *
 * When a new session is created, this function allocates it
 * and fills it with the current date
 *
 * \param[in] idFolder : folder id to which the session has to be linked
 * \param[out] session : Empty session allocated
*/
Session *createEmptySession(int idFolder){
    Session *newSession = (Session*) malloc(sizeof(Session));
    newSession->sessionName = (char*) malloc(LG_MAX_INFO*sizeof(char));
    char *new_session_name = get_new_session_name();
    strcpy(newSession->sessionName, new_session_name);
    free_info_UI(new_session_name);
    newSession->observations = (char*) malloc(LG_MAX_OBSERVATIONS*sizeof(char));
    strcpy(newSession->observations, "Remarques");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    newSession->sessionDate.day = tm.tm_mday;
    newSession->sessionDate.month = tm.tm_mon + 1;
    newSession->sessionDate.year = tm.tm_year + 1900;

    newSession->nextSessionDate.day = tm.tm_mday;
    newSession->nextSessionDate.month = tm.tm_mon + 1;
    newSession->nextSessionDate.year = tm.tm_year + 1900;

    newSession->nextSessionHour = (char*) malloc(LG_MAX_INFO*sizeof(char));
    strcpy(newSession->nextSessionHour, "12:00");

    newSession->isRealSession = 1;

    newSession->idSession = 0;
    newSession->idFolder = idFolder;

    return newSession;
}

/*!
* This function frees the attributes of a session s.
*
* \param[in] Session s, the session to free.
*/
void freeSession(Session *s) {
    free((void *)s->observations);
    free((void *)s->sessionName);
    free((void *)s->nextSessionHour);
}

/*!
* This function initialises a Session s : allocates its attributes, and fills its attibutes.
*
* \param[in] Session *s, the pointer on the session to free.
* \param[in] char *sName, the string to fill in sessionName.
* \param[in] char *obs, the string to fill in observations.
* \param[in] int sdDay, the day of the session.
* \param[in] int sdMonth, the month of the session.
* \param[in] int sdYear, the year of the session.
* \param[in] int nsdDay, the day of the next session.
* \param[in] int nsdMonth, the month of the next session.
* \param[in] int nsdYear, the year of the next session.
* \param[in] int idS, the id of the session.
* \param[in] int idFolder, the id of the folder containing the session.
* \param[out] Session *, the pointer on the session initialized.
*/
Session * initSession(Session *newS, char *sName, char *obs, int sdDay, int sdMonth, int sdYear, int nsdDay, int nsdMonth, int nsdYear, char *nsHour, int isRealFolder, int idS, int idFolder) {

    newS->sessionName = (char *) malloc(sizeof(char)*LG_MAX_INFO + 1);
    newS->observations = (char *) malloc(sizeof(char)*LG_MAX_OBSERVATIONS + 1);
    newS->nextSessionHour = (char *) malloc(sizeof(char)*LG_MAX_INFO + 1);

    if(newS->sessionName !=NULL && newS->observations != NULL && newS->nextSessionHour != NULL) {
        if(sName == NULL) strcpy(newS->sessionName, "\0");
        else {
            strncpy(newS->sessionName, sName, LG_MAX_INFO);
            newS->sessionName[LG_MAX_INFO] = '\0';
        }

        if(obs == NULL) strcpy(newS->observations, "\0");
        else {
            strncpy(newS->observations, obs, LG_MAX_OBSERVATIONS);
            newS->observations[LG_MAX_OBSERVATIONS] = '\0';
        }

        if(nsHour == NULL) strcpy(newS->nextSessionHour, "\0");
        else {
            strncpy(newS->nextSessionHour, nsHour, LG_MAX_INFO);
            newS->nextSessionHour[LG_MAX_INFO] = '\0';
        }

        setDate(&(newS->nextSessionDate), nsdDay, nsdMonth, nsdYear);
        setDate(&(newS->sessionDate), sdDay, sdMonth, sdYear);

        newS->idFolder = idFolder;
        newS->idSession = idS;
        newS->isRealSession = isRealFolder;

    }

    else freeSession(newS);

    return newS;
}

/*!
* This function allocates and creates a Nodelist, and fills the session in this Nodelist.
*
* \param[in] char *sName, the string to fill in sessionName.
* \param[in] char *obs, the string to fill in observations.
* \param[in] int sdDay, the day of the session.
* \param[in] int sdMonth, the month of the session.
* \param[in] int sdYear, the year of the session.
* \param[in] int nsdDay, the day of the next session.
* \param[in] int nsdMonth, the month of the next session.
* \param[in] int nsdYear, the year of the next session.
* \param[in] int idS, the id of the session.
* \param[in] int idFolder, the id of the folder containing the session.
* \param[in] NodeList * nextNode, the next NodeList in the list.
* \param[in] NodeList * prevNode, the previous NodeList in the list.
* \param[out] NodeList *, the Nodelist created.
*/
static NodeList * newNodeList(char *sName, char *obs, int sdDay, int sdMonth, int sdYear, int nsdDay, int nsdMonth, int nsdYear, char *nsHour, int isRealFolder, int idS, int idFolder, NodeList *nextNode, NodeList *prevNode) {
    NodeList *newNode = (NodeList *) malloc(sizeof(NodeList));

    if(newNode == NULL) return NULL;
    newNode->session = *initSession(&newNode->session, sName, obs, sdDay, sdMonth, sdYear, nsdDay, nsdMonth, nsdYear, nsHour, isRealFolder, idS, idFolder);

    newNode->next = nextNode;
    newNode->previous = prevNode;
    return newNode;
}

/*!
* This function frees the attributes of a NodeList, and frees this NodeList.
*
* \param[in] NodeList * node, the NodeList to free.
*/
static void freeNodeList(NodeList *node) {
    freeSession(&(node->session));
    free(node);
}

/*!
* This function initializes the attributes of an allocated SessionList.
*
* \param[in] SessionList *l, the list to initialize.
*/
void initList(SessionList *l) {
    l->first = NULL;
    l->last = NULL;
    l->current = l->first;
}

/*!
* This function tells if the list is empty or not.
*
* \param[in] SessionList *l, the list to test.
* \param[out] int, 0 if the list isn't empty, -1 otherwise.
*/
int isEmpty(SessionList *l) {
    if(l->first == NULL) return -1;
    return 0;
}


/*!
* This function creates and inserts a NodeList on the first position of the list.

* \param[in] SessionList * l, the list where the NodeList has to be inserted.
* \param[in] char *sName, the string to fill in sessionName.
* \param[in] char *obs, the string to fill in observations.
* \param[in] int sdDay, the day of the session.
* \param[in] int sdMonth, the month of the session.
* \param[in] int sdYear, the year of the session.
* \param[in] int nsdDay, the day of the next session.
* \param[in] int nsdMonth, the month of the next session.
* \param[in] int nsdYear, the year of the next session.
* \param[in] int idS, the id of the session.
* \param[in] int idFolder, the id of the folder containing the session.
* \param[out] int, 0 if the NodeList has been inserted, -1 otherwise.
*/
int insertFirst(SessionList *l, char *sName, char *obs, int sdDay, int sdMonth, int sdYear, int nsdDay, int nsdMonth, int nsdYear, char *nsHour, int isRealFolder, int idS, int idFolder) {
    setOnFirst(l);
    NodeList * newNode = newNodeList(sName, obs, sdDay, sdMonth, sdYear, nsdDay, nsdMonth, nsdYear, nsHour, isRealFolder, idS, idFolder, l->first, NULL);
    if(newNode == NULL) return -1;

    if(isEmpty(l) !=0) {

        l->last = newNode;
    }
    else l->first->previous = newNode;
    l->first = newNode;

    return 0;
}

/*!
* This function creates and inserts a NodeList on the last position of the list.

* \param[in] SessionList * l, the list where the NodeList has to be inserted.
* \param[in] char *sName, the string to fill in sessionName.
* \param[in] char *obs, the string to fill in observations.
* \param[in] int sdDay, the day of the session.
* \param[in] int sdMonth, the month of the session.
* \param[in] int sdYear, the year of the session.
* \param[in] int nsdDay, the day of the next session.
* \param[in] int nsdMonth, the month of the next session.
* \param[in] int nsdYear, the year of the next session.
* \param[in] int idS, the id of the session.
* \param[in] int idFolder, the id of the folder containing the session.
* \param[out] int, 0 if the NodeList has been inserted, -1 otherwise.
*/
int insertLast(SessionList *l, char *sName, char *obs, int sdDay, int sdMonth, int sdYear, int nsdDay, int nsdMonth, int nsdYear, char *nsHour, int isRealFolder, int idS, int idFolder) {
    setOnLast(l);
    NodeList * newNode = newNodeList(sName, obs, sdDay, sdMonth, sdYear, nsdDay, nsdMonth, nsdYear, nsHour, isRealFolder, idS, idFolder, NULL, l->last);
    if(newNode == NULL) return -1;

    if(isEmpty(l) !=0) {
        l->first = newNode;
    }
    else l->last->next = newNode;
    l->last = newNode;

    return 0;
}

/*!
* This function deletes and frees the first NodeList of the list.

* \param[in] SessionList * l, the list where the first NodeList has to be deleted.
*/
void deleteFirst(SessionList *l) {
    NodeList * ptr = l->first;
    l->first = l->first->next;
    freeNodeList(ptr);
}

/*!
* This function deletes and frees the current NodeList of the list.

* \param[in] SessionList * l, the list where the current NodeList has to be deleted.
*/
void deleteCurrent(SessionList *l) {
    NodeList *ptr = l->current;
    if(l->current == l->last) l->last = l->current->previous;
    if(l->current == l->first) l->first = l->current->next;
    l->current->next->previous = l->current->previous;
    l->current->previous->next = l->current->next;
    l->current = l->first;
    freeNodeList(ptr);
}

/*!
* This function puts the list current pointer on the Nth element of the list.

* \param[in] SessionList * l, the list where the Nth element has to become the current element.
* \param[in] int n, the position of the element.
* \param[out] int, 0 if the list has more than n elements, -1 otherwise.
*/
int pointNthElement(SessionList *l, int n) {
    int i;
    setOnFirst(l);
    for(i=1; i<n; i++) {
        setOnNext(l);
        if(isOutOfList(l)) return -1;
    }
    return 0;
}

/*!
* This function deletes the Nth element of the list.

* \param[in] SessionList * l, the list where the Nth element has to be deleted.
* \param[in] int n, the position of the element.
* \param[out] int, 0 if the list has more than n elements and if the Nth has been correctly deleted, -1 otherwise.
*/
int deleteNthElement(SessionList *l, int n) {
    if(pointNthElement(l, n) !=0) return -1;
    deleteCurrent(l);
    return 0;
}

/*!
* This function sets the list current pointer on the first node.

* \param[in] SessionList * l, the list.
*/
void setOnFirst(SessionList *l) {
    l->current = l->first;
}

/*!
* This function sets the list current pointer on the last node.

* \param[in] SessionList * l, the list.
*/
void setOnLast(SessionList *l) {
    l->current = l->last;
}

/*!
* This function sets the list current pointer on the next node.

* \param[in] SessionList * l, the list.
*/
void setOnNext(SessionList *l) {
    if(l->current == NULL) l->current = NULL;
    l->current = l->current->next;
}

/*!
* This function tells if the list current pointer is out of the list.

* \param[in] SessionList * l, the list to test.
* \param[out] int, -1 if the current pointer is out of the list, 0 otherwise.
*/
int isOutOfList(SessionList *l) {
    if(l->current == NULL) return -1;
    return 0;
}

/*!
* This function frees the NodeLists of the list in parameter.

* \param[in] SessionList * l, the list to free.
*/
void freeList(SessionList *l) {
    setOnFirst(l);
    while(isOutOfList(l) ==0) {
        NodeList *temp = l->current->next;
        freeNodeList(l->current);
        l->current = temp;
    }
}

int getFutureSessionId(){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt;
    int futureSessionId = 0;

    //Opening database
    rc = sqlite3_open(DB_PATH, &db);

    //Testing opening
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stdout,"Opened database successfully\n");
    }

    //Creating te request
    sql = "SELECT seq FROM sqlite_sequence WHERE name = 'seance'";

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error : %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }

    sqlite3_step(stmt);
    futureSessionId = sqlite3_column_int(stmt,0);

    sqlite3_finalize(stmt);

    //Closing database
    sqlite3_close(db);
    return futureSessionId + 1;
}