//
// Created by julien on 26/04/2021.
//

#include "UTest_ext_files_manager.h"
#include "../src/model/structures.h"
#include "../src/controller/extern_files_manager.h"
#include "../src/controller/BDD_to_struct_patient.h"
#include "../src/controller/struct_to_BDD_patient.h"
#include "../src/model/patient_manager.h"

static void test_getExtensionFromPath(void **state){
    char *testPath = "../media/graphic-assets/archive_512.png"
    char *temp = get_name_UI(patient);
    assert_string_equal("png", temp);
    free(testPath);
    free(temp);
}

static void test_getProfileExtension(void **state){
    char *temp = getProfileExtension(1);
    assert_string_equal(".jpeg", temp);
    free(temp);
}

static void test_getProfilePhotoPath(void **state){
    char *temp = getProfilePhotoPath(1);
    assert_string_equal("../media/patient-data/1/profil.jpeg", temp);
    free(temp);
}

static void test_getPatientMediaPath(void **state){
    char *temp = getPatientMediaPath(1);
    assert_string_equal("../media/patient-data/1/", temp);
    free(temp);
}

static void test_getFolderMediaPath(void **state){
    char *temp = getFolderMediaPath(1,1);
    assert_string_equal("../media/patient-data/1/1/", temp);
    free(temp);
}

static void test_getNbOfAttachments(void **state){
    int count = getNbOfAttachments(1,1);
    assert_int_equal(0, temp);
}

static void test_replaceWhitespaces(void **state){
    char *testString = "this is a test string"
    char *temp = replaceWhitespaces(testString);
    assert_string_equal("this_is_a_test_string", temp);
    free(testString);
    free(temp);
}


int main_ext_files_manager(void)
{
    const struct CMUnitTest tests_UI[]=
            {
                    cmocka_unit_test(test_getExtensionFromPath),
                    cmocka_unit_test(test_getProfileExtension),
                    cmocka_unit_test(test_getProfilePhotoPath),
                    cmocka_unit_test(test_getPatientMediaPath),
                    cmocka_unit_test(test_getFolderMediaPath),
                    cmocka_unit_test(test_getNbOfAttachments),
                    cmocka_unit_test(test_replaceWhitespaces)
            };
    return cmocka_run_group_tests_name("Test ext_files_manager module",tests_UI,NULL,NULL);
}