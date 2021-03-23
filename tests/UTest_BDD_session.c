#include <stdarg.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stddef.h>
#include <cmocka.h>
#include "../src/controller/BDD_to_struct_session.h"
#include "UTest_BDD_session.h"
#include "../src/model/session_manager.h"

static void test_getSession(void **state){
    Session * s = getSession(1);
    assert_non_null(s);
    assert_string_equal("Séance du 18/3/2021", s->sessionName);
    assert_int_equal(s->sessionDate.day, 18);
    assert_int_equal(s->nextSessionDate.day, 22);
    assert_int_equal(1, s->idSession);
    freeSession(s);
    free(s);
}

static void test_getSessionId(void **state){
    int* tab_id = getSessionId(1);
    assert_int_equal(2, tab_id[1]);
    assert_int_equal(1, tab_id[0]);
    free(tab_id);
}

static void test_getSessionList(void **state) {
    SessionList *l = getSessionList(1);
    assert_non_null(l);

    assert_string_equal("Séance du 18/3/2021", l->last->session.sessionName);
    assert_string_equal("Comme d'habitude, bonne progression", l->last->session.observations);
    assert_int_equal(22, l->last->session.nextSessionDate.day);
    assert_int_equal(18, l->last->session.sessionDate.day);
    assert_int_equal(1, l->last->session.idSession);

    assert_string_equal("Séance du 22/3/2021", l->first->session.sessionName);
    assert_string_equal("Comme d'habitude", l->first->session.observations);
    assert_int_equal(30, l->first->session.nextSessionDate.day);
    assert_int_equal(22, l->first->session.sessionDate.day);
    assert_int_equal(2, l->first->session.idSession);
    freeList(l);
}

int main_BDD_session(void) {
    const struct CMUnitTest tests_BDD_session[]=
            {
                    cmocka_unit_test(test_getSession),
                    cmocka_unit_test(test_getSessionId),
                    cmocka_unit_test(test_getSessionList)
            };
    return cmocka_run_group_tests_name("Test BDD_session module",tests_BDD_session,NULL,NULL);
}