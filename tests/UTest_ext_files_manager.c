/*!
* \file UTest_ext_files_manager.c
* \brief Functions to test the functions to manage external files
*/

#include <stdio.h>
#include <stdlib.h>
//#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "UTest_ext_files_manager.h"
#include "../src/controller/extern_files_manager.h"
#include "../src/controller/struct_to_BDD_patient.h"

/*!
 * \brief Test getExtensionFromPath function
 * Check if the right extension is returned from a given path.
*/
static void test_getExtensionFromPath(){
    char *testPath = (char*) malloc(sizeof(char)*strlen("../media/graphic-assets/archive_512.png"));
    strcpy(testPath, "../media/graphic-assets/archive_512.png");
    char *temp = getExtensionFromPath(testPath);
    assert_string_equal("png", temp);
    free(testPath);
    free(temp);
}

/*!
 * \brief Test getProfileExtension function
 *
 * Test every profile extension possibility
*/
static void test_getProfileExtension(){
    char *temp1 = (char*) malloc(sizeof(char)*10);
    strcpy(temp1, getProfileExtension(-2));
    assert_string_equal(".error", temp1);
    char *temp2 = (char*) malloc(sizeof(char)*10);
    strcpy(temp2, getProfileExtension(-3));
    assert_string_equal(".jpeg", temp2);
    char *temp3 = (char*) malloc(sizeof(char)*10);
    strcpy(temp3, getProfileExtension(-4));
    assert_string_equal(".png", temp3);
    char *temp4 = (char*) malloc(sizeof(char)*10);
    strcpy(temp4, getProfileExtension(-5));
    assert_string_equal(".jpg", temp4);
    free(temp1);
    free(temp2);
    free(temp3);
    free(temp4);
}

/*!
 * \brief Test getProfilePhotoPath function
*/
static void test_getProfilePhotoPath(){
    char *temp = getProfilePhotoPath(-3);
    assert_string_equal("../media/patient-data/-3/profil.jpeg", temp);
    free(temp);
}

/*!
 * \brief Test getPatientMediaPath function
*/
static void test_getPatientMediaPath(){
    char *temp = getPatientMediaPath(-2);
    assert_string_equal("../media/patient-data/-2/", temp);
    free(temp);
}

/*!
 * \brief Test getFolderMediaPath function
*/
static void test_getFolderMediaPath(){
    char *temp = getFolderMediaPath(-2,1);
    assert_string_equal("../media/patient-data/-2/1/", temp);
    free(temp);
}

/*!
 * \brief Test getNbOfAttachments function
*/
static void test_getNbOfAttachments(){
    int count = getNbOfAttachments(-2,1);
    assert_int_equal(2, count);
}

/*!
 * \brief Test getMediaDirectoryContent function
*/
static void test_getMediaDirectoryContent(){
    char **fileList = getMediaDirectoryContent(-2,1);
    if(strcmp(OS, "macOS") == 0){
        assert_string_equal("zyx.cba", fileList[0]);
        assert_string_equal("abc.xyz", fileList[1]);
    } else {
        assert_string_equal("abc.xyz", fileList[0]);
        assert_string_equal("zyx.cba", fileList[1]);
    }


}

/*!
 * \brief Test replaceWhitespaces function
*/
static void test_replaceWhitespaces(){
    char *testString = (char*) malloc(sizeof(char)*strlen("this is a test string"));
    strcpy(testString, "this is a test string");
    char *temp = (char*) malloc(sizeof(char)*strlen("this is a test string"));
    strcpy(temp, replaceWhitespaces(testString));
    assert_string_equal("this_is_a_test_string", temp);
    free(testString);
    free(temp);
}

/*!
 * \brief Test addMedia function
*/
static void test_addMedia(){
    int test;
    test = copyToMedia("../media/media-for-tests/profil.jpg", -1, -1, "profil");
    assert_int_equal(1, test);
    test = copyToMedia("../media/media-for-tests/attachment.png", -1, -1, "attachment");
    assert_int_equal(1, test);

    // The next ones have errors in path to cover codes in case of failure
    test = copyToMedia("", -1, -1, "attachment");
    assert_int_equal(0, test);
    test = copyToMedia("../media/media-for-tests/attachment.png", -10, -1, "attachment");
    assert_int_equal(0, test);
}

/*!
 * \brief Test mediaDeletion function
*/
static void test_mediaDeletion(){
    assert_int_equal(1, getNbOfAttachments(-1, -1));
    //removeExistingProfilePicture("../media/patient-data/-1/profil.");
    deleteMediaFolder(-1);
}

/*!
 * \brief Global function to launch tests for external files managers
*/
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
                    cmocka_unit_test(test_getMediaDirectoryContent),
                    cmocka_unit_test(test_addMedia),
                    cmocka_unit_test(test_mediaDeletion),
            };
    return cmocka_run_group_tests_name("Test ext_files_manager module",tests_ext_files_manager,NULL,NULL);
}