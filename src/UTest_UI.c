/*!
* \file UTest_UI.c
* \brief Functions to test the functions linking structure and UI
*/

#include "structures.h"
#include "connect_struct_UI.h"
#include "patient.h"

//#include "../src/structures.h"
//#include "../src/connect_struct_UI.h"
//#include "../src/patient.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

/*!
 * \brief Setup function which allocates and return a patient
 *
 * This function get the patient with id 1 (Claude Francois)
 * and pass its adress in *state for the next tests
 *
 * \param[in] A pointer adress to pass the allocated patient
 * \param[out] An int to know if patient is well allocated
*/
static int setup_patient(void **state){
    Patient *patient = getPatient(1);
    if(patient == NULL) return -1;

	assert_non_null(patient);
	*state = patient;
	return 0;
}

/*!
 * \brief Setup function which allocates and fill a patient
 *
 * This function gets the patient with id 1 (Claude Francois)
 * and pass its adress in *state for the next tests
 *
 * \param[in] A pointer adress to pass the allocated patient
 * \param[out] An int to know if patient is well allocated
*/
static void test_get_name_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char * temp = get_name_UI(patient);
    assert_string_equal("Francois Claude", temp);
    free(temp);
}

/*!
 * \brief test get_date_UI function
 *
 * This function tests get_date_UI which returns a char* "xx/xx/xxxx" passing a patient Birthdate
 *
 * \param[in] A pointer adress to pass the allocated patient
*/
static void test_get_date_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char *temp = get_date_UI(&patient->birthdate);
    assert_string_equal("1/2/1939", temp);
    free(temp);
}

/*!
 * \brief test get_height_UI function
 *
 * This function tests get_height_UI which returns a char* "x.xxm" passing a patient
 *
 * \param[in] A pointer adress to pass the allocated patient
*/
static void test_get_height_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char * temp = get_height_UI(patient);
    assert_string_equal("1.70m", temp);
    free((void *) temp);
}

/*!
 * \brief test get_weight_UI function
 *
 * This function tests get_weight_UI which returns a char* "xxkg" passing a patient
 *
 * \param[in] A pointer adress to pass the allocated patient
*/
static void test_get_weight_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char *temp = get_weight_UI(patient);
    assert_string_equal("59kg", temp);
    free(temp);
}

/*!
 * \brief test get_height_weight_UI function
 *
 * This function tests get_height_weight_UI which returns a char* "xxkg   ;   x.xxm" passing a patient
 *
 * \param[in] A pointer adress to pass the allocated patient
*/
static void test_get_height_weight_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char *temp = get_height_weight_UI(patient);
    assert_string_equal("59kg   ;   1.70m", temp);
    free(temp);
}

/*!
 * \brief test get_first_consultation_UI function
 *
 * This function tests get_first_consultation_UI which returns a char* "Première consultation  : xx/xx/xxxx" passing a patient
 *
 * \param[in] A pointer adress to pass the allocated patient
*/
static void test_get_first_consultation_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char *temp = get_first_consultation_UI(patient);
    assert_string_equal("Première consultation : 1/1/1962", temp);
    free(temp);
}

/*!
 * \brief test test_get_adress_UI function
 *
 * This function tests test_get_adress_UI which returns a char* "number street" passing a patient
 *
 * \param[in] A pointer adress to pass the allocated patient
*/
static void test_get_adress_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char * temp = get_adress_UI(patient);
    assert_string_equal("2 Rue tintintin", temp);
    free(temp);
}

/*!
 * \brief Teardown function which desallocates the patient
 *
 * This function desallocates the patient allocated by setup function
 *
 * \param[in] A pointer adress to pass the allocated patient
 * \param[out] An int to tell that desallocation worked
*/
static int teardown(void **state){
    Patient * patient = (Patient *) (*state);
    freePatient(&patient);
    return 0;
}

/*!
 * \brief main function which runs the tests for UI
 *
 * \param[out] An int to tell if tests are passed
*/
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
