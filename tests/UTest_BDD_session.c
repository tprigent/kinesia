#include <stdarg.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stddef.h>
#include <cmocka.h>
#include "../src/controller/BDD_to_struct_session.h"
#include "../src/controller/struct_to_BDD_session.h"
#include "UTest_BDD_session.h"
#include "../src/model/session_manager.h"

static void test_getSession(void **state){
    Session * s = getSession(8);
    assert_non_null(s);
    assert_string_equal("TestS1", s->sessionName);
    assert_int_equal(s->sessionDate.day, 3);
    assert_int_equal(s->nextSessionDate.day, 5);
    assert_int_equal(8, s->idSession);
    freeSession(s);
    free(s);
}

static void test_getSessionId(void **state){
    int* tab_id = getSessionId(3);
    assert_int_equal(8, tab_id[0]);
    assert_int_equal(9, tab_id[1]);
    free(tab_id);
}

static void test_getSessionList(void **state) {
    SessionList *l = getSessionList(3);
    assert_non_null(l);

    assert_string_equal("TestS1", l->last->session.sessionName);
    assert_string_equal("NoObs", l->last->session.observations);
    assert_int_equal(5, l->last->session.nextSessionDate.day);
    assert_int_equal(3, l->last->session.sessionDate.day);
    assert_int_equal(8, l->last->session.idSession);

    assert_string_equal("TestS2", l->first->session.sessionName);
    assert_string_equal("NoObs2", l->first->session.observations);
    assert_int_equal(15, l->first->session.nextSessionDate.day);
    assert_int_equal(5, l->first->session.sessionDate.day);
    assert_int_equal(9, l->first->session.idSession);
    freeList(l);
}

static void test_getNbSession(void **state) {
    assert_int_equal(2, getNbSession(3));
}

static void test_modifySession(void **state){

    Session *s;
    s = getSession(1);
    s->sessionName = "New name";
    assert_int_equal(1,modifySession(s));
    s = getSession(s->idSession);
    assert_string_equal("New name",s->sessionName);

}

int main_BDD_session(void) {
    const struct CMUnitTest tests_BDD_session[]=
            {
                    cmocka_unit_test(test_getSession),
                    cmocka_unit_test(test_getSessionId),
                    cmocka_unit_test(test_getSessionList),
                    cmocka_unit_test(test_getNbSession),
                    cmocka_unit_test(test_modifySession)
            };
    return cmocka_run_group_tests_name("Test BDD_session module",tests_BDD_session,NULL,NULL);
}