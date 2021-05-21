/*!
* \file UTest.c
* \brief Functions to run CMocka tests
*/

#include "UTest_display_helpers.h"
#include "UTest_ext_files_manager.h"
#include "UTest_session_list.h"
#include "UTest_session.h"
#include "UTest_manager.h"
#include "UTest_folder.h"
#include "UTest_patient.h"


int main(void){
    int i = patient_display_helpers_tests()
            *folder_display_helpers_tests()
            *other_display_helpers_tests()
            *main_ext_files_manager()
            *main_patient()
            *main_folder()
            *main_session()
            *main_session_list()
            *main_manager();
    return i;
}