/*!
* \file UTest.c
* \brief Functions to run CMocka tests
*/

#include "UTest_display_helpers.h"
#include "UTest_ext_files_manager.h"
#include "UTest_BDD.h"
#include "UTest_session.h"
#include "UTest_BDD_session.h"


int main(void){
    //int i = main_BDD_session()*main_BDD()*main_UI()*main_session();
    int i = patient_display_helpers_tests()*folder_display_helpers_tests()*other_display_helpers_tests();
    return i;
}