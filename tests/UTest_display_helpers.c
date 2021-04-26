/*!
* \file UTest_UI.c
* \brief Functions to test the functions linking structure and UI
*/

#include "../src/model/structures.h"
#include "../src/controller/display_helpers.h"
#include "../src/controller/BDD_to_struct_patient.h"
#include "../src/controller/BDD_to_struct_folder.h"
#include "../src/controller/struct_to_BDD_patient.h"
#include "../src/model/patient_manager.h"


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
 * and pass its addressin *state for the next tests
 *
 * \param[in] A pointer addressto pass the allocated patient
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
 * and pass its addressin *state for the next tests
 *
 * \param[in] A pointer addressto pass the allocated patient
 * \param[out] An int to know if patient is well allocated
*/
static void test_get_name_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char * temp = get_name_UI(patient);
    assert_string_equal("<b>Claude François</b>", temp);
    free(temp);
}

/*!
 * \brief test get_date_UI function
 *
 * This function tests get_date_UI which returns a char* "xx/xx/xxxx" passing a patient Birthdate
 *
 * \param[in] A pointer addressto pass the allocated patient
*/
static void test_get_date_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char *temp = get_date_UI(&patient->birthdate);
    assert_string_equal("1/2/1939", temp);
    free(temp);
}

/*!
 * \brief test get_height_weight_UI function
 *
 * This function tests get_height_weight_UI which returns a char* "xxkg   ;   x.xxm" passing a patient
 *
 * \param[in] A pointer addressto pass the allocated patient
*/
static void test_get_height_weight_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char *temp = get_height_weight_UI(patient);
    assert_string_equal("1.70m     ;     59kg", temp);
    free(temp);
}

/*!
 * \brief test get_first_consultation_UI function
 *
 * This function tests get_first_consultation_UI which returns a char* "Première consultation  : xx/xx/xxxx" passing a patient
 *
 * \param[in] A pointer addressto pass the allocated patient
*/
static void test_get_first_consultation_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char *temp = get_first_consultation_UI(patient);
    assert_string_equal("Première consultation : 1/1/1962", temp);
    free(temp);
}

/*!
 * \brief test get_age_and_birthdate function
 *
 * This function tests get_age_and_birthdate which returns the birthdate of
 * a patient and his age
 *
 * \param[in] A pointer addressto pass the allocated patient
*/
static void test_get_age_and_birthdate(void **state){
    Patient * patient = (Patient *) (*state);
    char * age = get_age_and_birthdate(patient);
    assert_string_equal("1/2/1939 (82 ans)", age);
    free(age);
}

/*!
 * \brief test get_current_date function
 *
 * This function tests get_current_date which returns the date of the day
 *
 * \param[in] A pointer addressto pass the allocated patient
*/
static void test_get_current_date(void **state){
    char * date = get_current_date();
    assert_string_equal("26/4/2021", date);
    free(date);
}

/*!
 * \brief test get_new_session_name function
 *
 * This function tests get_new_session_name which returns a formatted name for
 * a new session (Séance du dd/mm/yyyy)
 *
 * \param[in] A pointer addressto pass the allocated patient
*/
static void test_get_new_session_name(void **state){
    char * session_name = get_new_session_name();
    assert_string_equal("Séance du 26/4/2021", session_name);
    free(session_name);
}


/*!
 * \brief Teardown function which desallocates the patient
 *
 * This function desallocates the patient allocated by setup function
 *
 * \param[in] A pointer addressto pass the allocated patient
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
int patient_display_helpers_tests(void)
{

    const struct CMUnitTest tests_patient_helpers[]=
    {
            cmocka_unit_test_setup_teardown(test_get_name_UI, setup_patient, teardown),
            cmocka_unit_test_setup_teardown(test_get_date_UI, setup_patient, teardown),
            cmocka_unit_test_setup_teardown(test_get_height_weight_UI, setup_patient, teardown),
            cmocka_unit_test_setup_teardown(test_get_first_consultation_UI, setup_patient, teardown),
            cmocka_unit_test_setup_teardown(test_get_age_and_birthdate, setup_patient, teardown),
            cmocka_unit_test_setup_teardown(test_get_current_date, setup_patient, teardown),
            cmocka_unit_test_setup_teardown(test_get_new_session_name, setup_patient, teardown),
    };
    return cmocka_run_group_tests_name("Test patient_helpers module",tests_patient_helpers,NULL,NULL);
}


/* *********************************************************************************************************************/

static int setup_folder(void **state){
    Folder *folder = getFolder(1);
    if(folder == NULL) return -1;

    assert_non_null(folder);
    *state = folder;
    return 0;
}

static void test_get_formatted_folder_title_UI(void **state){
    Folder * folder = (Folder *) (*state);
    char * formatted_folder = get_formatted_folder_title_UI(folder);
    assert_string_equal("<big><b>         Entorse de la cheville</b></big>", formatted_folder);
    free(formatted_folder);
}

static void test_get_indicator_files_UI(void **state){
    Folder * folder = (Folder *) (*state);
    char * indicator_files = get_indicator_files_UI(1, 1);
    assert_string_equal("   (0)", indicator_files);
    free(indicator_files);
}

/*!
 * \brief Teardown function which desallocates the patient
 *
 * This function desallocates the patient allocated by setup function
 *
 * \param[in] A pointer addressto pass the allocated patient
 * \param[out] An int to tell that desallocation worked
*/
static int teardown_folder(void **state){
    Folder * folder = (Folder *) (*state);
    //free(&folder);
    return 0;
}

/*!
 * \brief main function which runs the tests for UI
 *
 * \param[out] An int to tell if tests are passed
*/
int folder_display_helpers_tests(void)
{
    const struct CMUnitTest tests_folder_helpers[]=
            {
                    cmocka_unit_test_setup_teardown(test_get_formatted_folder_title_UI, setup_folder, teardown_folder),
                    cmocka_unit_test_setup_teardown(test_get_indicator_files_UI, setup_folder, teardown_folder),

            };
    return cmocka_run_group_tests_name("Test folder_helpers module",tests_folder_helpers,NULL,NULL);
}


/* *********************************************************************************************************************/

static void test_tostring(){
    char *number = (char*) malloc(3*sizeof(char));
    tostring(number, 18);
    assert_string_equal("18", number);
    free(number);
}

static void test_parseDate(){
    char *dateC = (char*) malloc(11*sizeof(char));
    strcpy(dateC, "26/04/2021");
    Date date = *parseDate(dateC);
    assert_int_equal(26, date.day);
    assert_int_equal(4, date.month);
    assert_int_equal(2021, date.year);
    free(dateC);
}

/*!
 * \brief main function which runs the tests for UI
 *
 * \param[out] An int to tell if tests are passed
*/
int other_display_helpers_tests(void)
{
    const struct CMUnitTest tests_other_helpers[]=
            {
                    cmocka_unit_test(test_tostring),
                    cmocka_unit_test(test_parseDate),
            };
    return cmocka_run_group_tests_name("Test folder_helpers module",tests_other_helpers,NULL,NULL);
}