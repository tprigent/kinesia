/*!
* \file UTest_display_helpers.c
* \brief Functions to test the functions for displaying infos on interface
*/

#include "../src/model/structures.h"
#include "../src/controller/display_helpers.h"
#include "../src/model/BDD_to_struct_patient.h"
#include "../src/model/BDD_to_struct_folder.h"
#include "../src/controller/struct_to_BDD_patient.h"
#include "../src/model/patient_manager.h"


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

/** ********************************************** PATIENT HELPERS TESTS ***********************************************/

/*!
 * \brief Setup function which allocates a patient
 *
 * This function get the patient with id 1 (Claude Francois)
 * and pass its address in *state for the next tests
 *
 * \param[in] state A pointer address to pass the allocated patient
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
 * and pass its address in *state for the next tests
 *
 * \param[in] state A pointer address to pass the allocated patient
 * \param[out] An int to know if patient is well allocated
*/
static void test_get_name_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char * temp = get_name_UI(patient);
    assert_string_equal("<b>Claude François</b>", temp);
    free_info_UI(temp);
}

/*!
 * \brief test get_date_UI function
 * This function tests get_date_UI which returns a char* "xx/xx/xxxx" passing a patient Birthdate
 *
 * \param[in] state A pointer address to pass the allocated patient
*/
static void test_get_date_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char *temp = get_date_UI(&patient->birthdate);
    assert_string_equal("1/2/1939", temp);
    free_info_UI(temp);
}

/*!
 * \brief test get_height_weight_UI function
 * This function tests get_height_weight_UI which returns a char* "xxkg   ;   x.xxm" passing a patient
 *
 * \param[in] state A pointer address to pass the allocated patient
*/
static void test_get_height_weight_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char *temp = get_height_weight_UI(patient);
    assert_string_equal("1.70m     ;     59kg", temp);
    free_info_UI(temp);
}

/*!
 * \brief test get_first_consultation_UI function
 * This function tests get_first_consultation_UI which returns a char* "Première consultation  : xx/xx/xxxx" passing a patient
 *
 * \param[in] state A pointer address to pass the allocated patient
*/
static void test_get_first_consultation_UI(void **state){
    Patient * patient = (Patient *) (*state);
    char *temp = get_first_consultation_UI(patient);
    assert_string_equal("Première consultation : 1/1/1962", temp);
    free_info_UI(temp);
}

/*!
 * \brief test get_age_and_birthdate function
 *
 * This function tests get_age_and_birthdate which returns the birthdate of
 * a patient and his age
 *
 * \param[in] state A pointer addressto pass the allocated patient
*/
static void test_get_age_and_birthdate(void **state){
    Patient * patient = (Patient *) (*state);
    char * age = get_age_and_birthdate(patient);
    assert_string_equal("1/2/1939 (82 ans)", age);
    free_info_UI(age);
}

/*!
 * \brief test get_current_date function
 * This function tests get_current_date which returns the date of the day
 *
 * \param[in] state A pointer address to pass the allocated patient
*/
static void test_get_current_date(){
    char * date = get_current_date();
    assert_string_equal("27/4/2021", date);
    free_info_UI(date);
}

/*!
 * \brief test get_new_session_name function
 *
 * This function tests get_new_session_name which returns a formatted name for
 * a new session (Séance du dd/mm/yyyy)
 *
 * \param[in] state A pointer address to pass the allocated patient
*/
static void test_get_new_session_name(){
    char * session_name = get_new_session_name();
    char * new_session_name = (char*) malloc(sizeof(char) * strlen("Séance du xx/xx/xxxx"));
    strcpy(new_session_name, "Séance du ");
    strcat(new_session_name, get_current_date());
    assert_string_equal(new_session_name, session_name);
    free_info_UI(session_name);
    free_info_UI(new_session_name);
}


/*!
 * \brief Teardown function which deallocates the patient
 *
 * This function desallocates the patient allocated by setup function
 *
 * \param[in] state A pointer address to pass the allocated patient
 * \param[out] An int to tell if deallocation worked
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


/** ********************************************** FOLDER HELPERS TESTS ************************************************/

/*!
 * \brief Setup function which allocates a folder
 *
 * This function get the folder with id 1
 * and pass its address in *state for the next tests
 *
 * \param[in] state A pointer address to pass the allocated folder
 * \param[out] An int to know if folder is well allocated
*/
static int setup_folder(void **state){
    Folder *folder = getFolder(1);
    if(folder == NULL) return -1;

    assert_non_null(folder);
    *state = folder;
    return 0;
}

/*!
 * \brief test get_formatted_folder_title_UI function
 * Check if the title corresponds to the right format: spaces to be centered and big+bold
 *
 * \param[in] state A pointer address to pass the allocated patient
*/
static void test_get_formatted_folder_title_UI(void **state){
    Folder * folder = (Folder *) (*state);
    char * temp = get_formatted_folder_title_UI(folder);
    assert_string_equal("<big><b>         Entorse de la cheville</b></big>", temp);
    free_info_UI(temp);
}

/*!
 * \brief test get_indicator_files_UI function
 *
 * Check if the number returned by the function corresponds
 * to the number of files in the folder.
*/
static void test_get_indicator_files_UI(){
    char * temp = get_indicator_files_UI(1, 1);
    assert_string_equal("   (1)", temp);
    free_info_UI(temp);
}

/*!
 * \brief Teardown function which deallocates the folder
 *
 * This function deallocates the patient allocated by setup function
 *
 * \param[in] state A pointer address to pass the allocated patient
 * \param[out] An int to tell that deallocation worked
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


/** ********************************************** OTHER HELPERS TESTS *************************************************/

/*!
 * \brief test tostring function
 *
 * Check if a number passed in the function is welled
 * converted to string containing this number.
*/
static void test_tostring(){
    char *temp = (char*) malloc(3*sizeof(char));
    tostring(temp, 18);
    assert_string_equal("18", temp);
    free_info_UI(temp);
}

/*!
 * \brief test parseDate function
 *
 * Check if a string date is well translated in a date structure.
*/
static void test_parseDate(){
    char *temp = (char*) malloc(11*sizeof(char));
    strcpy(temp, "26/04/2021");
    Date date = *parseDate(temp);
    assert_int_equal(26, date.day);
    assert_int_equal(4, date.month);
    assert_int_equal(2021, date.year);
    free_info_UI(temp);
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