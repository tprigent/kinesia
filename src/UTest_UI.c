#include "structures.h"
#include "connect_struct_UI.h"
#include "patient.h"

//#include "../src/structures.h"
//#include "../src/connect_struct_UI.h"
//#include "../src/patient.h"

#include <stdio.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static int setup_patient(void **state){
    Patient *patient = getPatient(1);
    if(patient == NULL) return -1;

	assert_non_null(patient);
	*state = patient;
	return 0;
}

static void test_get_name_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char * temp = get_name_UI(patient);
    assert_string_equal("Francois Claude", temp);
    free(temp);
}

static void test_get_date_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char *temp = get_date_UI(&patient->birthdate);
    assert_string_equal("1/2/1939", temp);
    free(temp);
}

static void test_get_height_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char * temp = get_height_UI(patient);
    assert_string_equal("1.70m", temp);
    free((void *) temp);
}

static void test_get_weight_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char *temp = get_weight_UI(patient);
    assert_string_equal("59kg", temp);
    free(temp);
}

static void test_get_height_weight_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char *temp = get_height_weight_UI(patient);
    assert_string_equal("59kg   ;   1.70m", temp);
    free(temp);
}

static void test_get_first_consultation_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char *temp = get_first_consultation_UI(patient);
    assert_string_equal("Première consultation : 1/1/1962", temp);
    free(temp);
}

static void test_get_adress_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char * temp = get_adress_UI(patient);
    assert_string_equal("2 Rue tintintin", temp);
    free(temp);
}

static int teardown(void **state){
    Patient * patient = (Patient *) (*state);
    freePatient(&patient);
    return 0;
}

int main_UI(void)
{

    const struct CMUnitTest tests_UI[]=
    {
            cmocka_unit_test_setup_teardown(test_get_name_UI, setup_patient, teardown),
            cmocka_unit_test_setup_teardown(test_get_date_UI, setup_patient, teardown),
            cmocka_unit_test_setup_teardown(test_get_height_UI, setup_patient, teardown),
            cmocka_unit_test_setup_teardown(test_get_weight_UI, setup_patient, teardown),
            cmocka_unit_test_setup_teardown(test_get_height_weight_UI, setup_patient, teardown),
            cmocka_unit_test_setup_teardown(test_get_first_consultation_UI, setup_patient, teardown),
            cmocka_unit_test_setup_teardown(test_get_adress_UI, setup_patient, teardown),
    };
    return cmocka_run_group_tests_name("Test UI module",tests_UI,NULL,NULL);
}
