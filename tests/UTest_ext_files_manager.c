//
// Created by julien on 26/04/2021.
//

#include "UTest_ext_files_manager.h"

static void getExtensionFromPath(void **state){
    char *testPath = "../media/graphic-assets/archive_512.png"
    char *temp = get_name_UI(patient);
    assert_string_equal("png", temp);
    free(temp);
}


int main_UI(void)
{
    const struct CMUnitTest tests_UI[]=
            {

            };
    return cmocka_run_group_tests_name("Test ext_files_manager module",tests_UI,NULL,NULL);
}