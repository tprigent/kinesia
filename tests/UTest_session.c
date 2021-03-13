#include "../src/model/structures.h"
#include "../src/controler/struct_to_UI.h"
#include "../src/patient.h"
#include "UTest_session.h"
#include "../src/seance.h"

#include <stdio.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static int setup_sessionList(void **state){
    SessionList *l = malloc(sizeof(SessionList));
    if(l == NULL) return -1;
    initList(l);
    assert_non_null(l);
    assert_null(l->current);
    assert_null(l->first);
    assert_null(l->last);
    *state = l;
    return 0;
}

static void test_isEmpty_insertFirst(void **state) {
    SessionList *l = *state;
    assert_int_equal(-1, isEmpty(l));
    /*insertFirst(l, "nom", "obs", 12, 3, 0, 0, 0, 0, 0, 1);
    assert_null(l->first->next);
    assert_string_equal("nom", l->first->session.sessionName);
    assert_string_equal("obs", l->first->session.observations);
    assert_int_equal(12, l->first->session.nextSessionDate.day);
    assert_int_equal(3, l->first->session.nextSessionDate.month);
    assert_int_equal(0, l->first->session.nextSessionDate.year);
    assert_int_equal(0, l->last->session.nextSessionDate.day);
    assert_int_equal(0, l->last->session.nextSessionDate.month);
    assert_int_equal(0, l->last->session.nextSessionDate.year);

    assert_int_equal(12, l->first->session.sessionDate.day);
    assert_int_equal(3, l->first->session.sessionDate.month);
    assert_int_equal(0, l->first->session.sessionDate.year);

    assert_int_equal(0, l->first->session.idSession);
    assert_int_equal(1, l->first->session.idFolder);

    assert_int_equal(0, isEmpty(l));*/
}

static int teardown(void **state) {
    SessionList *l = *state;
    freeList(l);
    return 0;
}

int main_session(void)
{

    const struct CMUnitTest tests_session[]=
            {
                    cmocka_unit_test_setup_teardown(test_isEmpty_insertFirst, setup_sessionList, teardown)
            };
    return cmocka_run_group_tests_name("Test session module",tests_session,NULL,NULL);
}
