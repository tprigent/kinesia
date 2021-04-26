//
// Created by julien on 26/04/2021.
//

#include <stdio.h>
#include <stdlib.h>
//#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "UTest_ext_files_manager.h"
#include "../src/controller/extern_files_manager.h"
#include "../src/controller/struct_to_BDD_patient.h"

static void test_getExtensionFromPath(){
    char *testPath = (char*) malloc(sizeof(char)*strlen("../media/graphic-assets/archive_512.png"));
    strcpy(testPath, "../media/graphic-assets/archive_512.png");
    char *temp = getExtensionFromPath(testPath);
    assert_string_equal("png", temp);
    free(testPath);
    free(temp);
}

static void test_getProfileExtension(){
    char *temp1 = (char*) malloc(sizeof(char)*10);
    strcpy(temp1, getProfileExtension(10));
    assert_string_equal(".error", temp1);
    char *temp2 = (char*) malloc(sizeof(char)*10);
    strcpy(temp2, getProfileExtension(11));
    assert_string_equal(".jpeg", temp2);
    char *temp3 = (char*) malloc(sizeof(char)*10);
    strcpy(temp3, getProfileExtension(12));
    assert_string_equal(".png", temp3);
    char *temp4 = (char*) malloc(sizeof(char)*10);
    strcpy(temp4, getProfileExtension(13));
    assert_string_equal(".jpg", temp4);
    free(temp1);
    free(temp2);
    free(temp3);
    free(temp4);
}

static void test_getProfilePhotoPath(){
    char *temp = getProfilePhotoPath(1);
    assert_string_equal("../media/patient-data/1/profil.jpeg", temp);
    free(temp);
}

static void test_getPatientMediaPath(){
    char *temp = getPatientMediaPath(1);
    assert_string_equal("../media/patient-data/1/", temp);
    free(temp);
}

static void test_getFolderMediaPath(){
    char *temp = getFolderMediaPath(1,1);
    assert_string_equal("../media/patient-data/1/1/", temp);
    free(temp);
}

static void test_getNbOfAttachments(){
    int count = getNbOfAttachments(1,1);
    assert_int_equal(0, count);
}

static void test_replaceWhitespaces(){
    char *testString = (char*) malloc(sizeof(char)*strlen("this is a test string"));
    strcpy(testString, "this is a test string");
    char *temp = (char*) malloc(sizeof(char)*strlen("this is a test string"));
    strcpy(temp, replaceWhitespaces(testString));
    assert_string_equal("this_is_a_test_string", temp);
    free(testString);
    free(temp);
}

static void test_mediaDeletion(){
    assert_int_equal(1, getNbOfAttachments(-1, -1));
    removeExistingProfilePicture("../media/patient-data/-1/jjjjjjjjjjjjj", "media/patient-data/-1/profil.", "/home/julien/Desktop/projet-logiciel-kine/media/media-for-tests/profil.jpg");
    //deleteMediaFolder(-1);
}


int main_ext_files_manager(void)
{
    const struct CMUnitTest tests_ext_files_manager[]=
            {
                    cmocka_unit_test(test_getExtensionFromPath),
                    cmocka_unit_test(test_getProfileExtension),
                    cmocka_unit_test(test_getProfilePhotoPath),
                    cmocka_unit_test(test_getPatientMediaPath),
                    cmocka_unit_test(test_getFolderMediaPath),
                    cmocka_unit_test(test_getNbOfAttachments),
                    cmocka_unit_test(test_replaceWhitespaces),
                    cmocka_unit_test(test_mediaDeletion),
            };
    return cmocka_run_group_tests_name("Test ext_files_manager module",tests_ext_files_manager,NULL,NULL);
}