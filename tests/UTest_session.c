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

static void test_getSession(){
    Session * s = getSession(1);
    assert_non_null(s);
    assert_string_equal("Séance du 18/3/2021", s->sessionName);
    freeSession(s);
}

static void test_getSessionId(){
    int* tab_id = getSessionId(3);
    assert_int_equal(0x15, tab_id[0]);
    free(tab_id);
}

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

static void test_getNbSession() {
    assert_int_equal(6, getNbSession(3));
}

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

static void test_getSession0(){
    assert_int_equal(0, getSession0(3)->idSession);
}

static void test_deleteSession(){
    assert_int_equal(1, deleteSession(1));
}

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

static void test_addSession(){

    Session *s;
    int *t;
    t = getIdFolder(1);
    s = getSession(1);
    s->sessionName = "New session";
    s->idFolder = t[0];
    assert_int_equal(1,addSession(s));

}

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
            };
    return cmocka_run_group_tests_name("Session test module",tests_session,NULL,NULL);
}