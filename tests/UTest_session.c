/*!
* \file UTest_session.c
* \brief Functions to test session related functions
*/

#include <stdarg.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stddef.h>
#include <cmocka.h>
#include "../src/controller/BDD_to_struct_session.h"
#include "../src/controller/struct_to_BDD_session.h"
#include "UTest_session.h"
#include "../src/model/session_manager.h"
#include "../src/controller/BDD_to_struct_folder.h"
#include "../src/controller/display_helpers.h"

/*!
 * \brief test getSession function
*/
static void test_getSession(){
    Session * s = getSession(1);
    assert_non_null(s);
    assert_string_equal("Séance du 18/3/2021", s->sessionName);
    freeSession(s);
}

/*!
 * \brief test getSessionId function
 * Check if the array returned contains the session ID related to the fiven folder ID
*/
static void test_getSessionId(){
    int* tab_id = getSessionId(3);
    assert_int_equal(0x15, tab_id[0]);
    free(tab_id);
}

/*!
 * \brief test getSessionList function
 * Check if the content of the list is the same than in the DB
*/
static void test_getSessionList() {
    SessionList *l = getSessionList(1);
    assert_non_null(l);

    assert_string_equal("Séance du 25/3/2021", l->first->session.sessionName);
    assert_string_equal("Comme d'habitude, bonne progression", l->last->session.observations);
    assert_int_equal(25, l->first->session.nextSessionDate.day);
    assert_int_equal(25, l->first->session.sessionDate.day);
    assert_int_equal(4, l->first->session.idSession);

    setOnFirst(l);
    setOnNext(l);
    assert_string_equal("Séance du 22/3/2021", l->current->session.sessionName);
    assert_string_equal("Comme d'habitude", l->current->session.observations);
    assert_int_equal(30, l->current->session.nextSessionDate.day);
    assert_int_equal(22, l->current->session.sessionDate.day);
    assert_int_equal(2, l->current->session.idSession);

    freeList(l);
}

/*!
 * \brief test getNbSession function
 * Check if the number returned corresponds to the number of sessions of the folder
*/
static void test_getNbSession() {
    assert_int_equal(6, getNbSession(3));
}

/*!
 * \brief test modifySession function
 * Check if modifications are properly taken into account by DB
*/
static void test_modifySession(){

    Session *s;
    char* c;
    s = getSession(1);
    c = s->sessionName;
    s->sessionName = "New name";
    assert_int_equal(1,modifySession(s));
    s = getSession((int)s->idSession);
    assert_string_equal("New name",s->sessionName);
    s->sessionName=c;
    assert_int_equal(1,modifySession(s));

}

/*!
 * \brief test getSession0 function
 * Check if the function returns the right id of fake session
*/
static void test_getSession0(){
    assert_int_equal(0, getSession0(3)->idSession);
}

/*!
 * \brief test deleteSession function
 * Check if the deletion is properly done by DB function
*/
static void test_deleteSession(){
    assert_int_equal(1, deleteSession(1));
}

/*!
 * \brief test getSessionsAtDate function
 * Check if the session list for the date given is correct
*/
static void test_getSessionsAtDate(){
    Date *date = (Date*) malloc(sizeof(Date));
    int *sessionID = (int*) malloc(sizeof(int));
    int *folderID = (int*) malloc(sizeof(int));
    date->day = 22;
    date->month = 3;
    date->year = 2021;
    getSessionsAtDate(date, sessionID, folderID);
    assert_int_equal(sessionID[0], 1);
    assert_int_equal(folderID[0], 1);

    free(date);
    free(sessionID);
    free(folderID);
}

/*!
 * \brief test addSession function
 * Check if the session given is properly added
*/
static void test_addSession(){

    Session *s;
    int *t;
    t = getIdFolder(1);
    s = getSession(1);
    s->sessionName = "New session";
    s->idFolder = t[0];
    assert_int_equal(1,addSession(s));

}

/*!
 * \brief test getFutureSessionId function
*/
static void test_getFutureSessionId(){
    assert_int_equal(getFutureSessionId(), 37);
}

/*!
 * \brief Test createEmptySession function
 *
 * Check if the session is well created and filled by default infos.
*/
static void test_createEmptySession(){
    Session *session = createEmptySession(1);
    assert_string_equal(get_new_session_name(), session->sessionName);
    assert_string_equal("Remarques", session->observations);
    assert_int_equal(1, session->isRealSession);
    assert_int_equal(0, session->idSession);
    assert_int_equal(1, session->idFolder);
    free(session);
}

/*!
 * \brief Test createNewSession function
 *
 * Check a session filled with default infos is properly added in DB
*/
static void test_createNewSession(){
    int i = getFutureSessionId();
    createNewSession(1);
    Session *newSession = getSession(i);
    assert_string_equal(newSession->observations, "Remarques");
    assert_int_equal(newSession->isRealSession, 1);
    assert_int_equal(newSession->idFolder, 1);
}

/*!
 * \brief Function to launch all the tests related to session functions
*/
int main_session(void) {
    const struct CMUnitTest tests_session[]=
            {
                    cmocka_unit_test(test_getSession),
                    cmocka_unit_test(test_getSessionId),
                    cmocka_unit_test(test_getSessionList),
                    cmocka_unit_test(test_getNbSession),
                    cmocka_unit_test(test_modifySession),
                    cmocka_unit_test(test_getSession0),
                    cmocka_unit_test(test_getSessionsAtDate),
                    cmocka_unit_test(test_deleteSession),
                    cmocka_unit_test(test_addSession),
                    cmocka_unit_test(test_getFutureSessionId),
                    cmocka_unit_test(test_createEmptySession),
                    cmocka_unit_test(test_createNewSession)
            };
    return cmocka_run_group_tests_name("Session test module",tests_session,NULL,NULL);
}