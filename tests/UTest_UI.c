#include "../src/model/structures.h"
#include "../src/controler/struct_to_UI.h"
#include "../src/patient.h"

//#include "../src/structures.h"
//#include "../src/struct_to_UI.h"
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
    assert_string_equal("Claude Francois", get_name_UI(patient));
}

static void test_get_date_UI(void **state){
    Patient * patient = (Patient *) (*state);
    assert_string_equal("1/2/1939", get_date_UI(&patient->birthdate));
}


static void test_get_height_weight_UI(void **state){
    Patient * patient = (Patient *) (*state);
    assert_string_equal("1.70m     ;     59kg", get_height_weight_UI(patient));
}

static void test_get_first_consultation_UI(void **state){
    Patient * patient = (Patient *) (*state);
    assert_string_equal("Première consultation : 1/1/1962", get_first_consultation_UI(patient));
}

static void test_get_adress_UI(void **state){
    Patient * patient = (Patient *) (*state);
    assert_string_equal("2 Ruetintintin", get_adress_UI(patient));
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
            cmocka_unit_test_setup_teardown(test_get_height_weight_UI, setup_patient, teardown),
            cmocka_unit_test_setup_teardown(test_get_first_consultation_UI, setup_patient, teardown),
            cmocka_unit_test_setup_teardown(test_get_adress_UI, setup_patient, teardown),
    };
    return cmocka_run_group_tests_name("Test UI module",tests_UI,NULL,NULL);
}
