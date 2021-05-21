/*!
* \file UTest_folder_manager.c
* \brief Functions to test the functions to manage external files
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "UTest_manager.h"
#include "../src/model/folder_manager.h"
#include "../src/model/patient_manager.h"
#include "../src/model/session_manager.h"
#include "../src/controller/display_helpers.h"
#include "../src/controller/BDD_to_struct_session.h"


static void test_createEmptyFolder(){
    Folder *folder = createEmptyFolder(1);
    assert_string_equal("Nouveau dossier", folder->folderName);
    assert_string_equal("Détails", folder->details);
    assert_string_equal("Pathologie", folder->pathology);
    assert_int_equal(0, folder->numberOfFiles);
    assert_int_equal(1, folder->idPatient);
    free(folder);
}

static void test_createEmptySession(){
    Session *session = createEmptySession(1);
    assert_string_equal(get_new_session_name(), session->sessionName);
    assert_string_equal("Remarques", session->observations);
    assert_int_equal(1, session->isRealSession);
    assert_int_equal(0, session->idSession);
    assert_int_equal(1, session->idFolder);
    free(session);
}

static void test_createNewSession(){
    int i = getFutureSessionId();
    createNewSession(1);
    Session *newSession = getSession(i);
    assert_string_equal(newSession->observations, "Remarques");
    assert_int_equal(newSession->isRealSession, 1);
    assert_int_equal(newSession->idFolder, 1);
}

static void test_getFutureFolderId(){
    assert_int_equal(getFutureFolderId(), 10);
}

static void test_getFuturePatientId(){
    assert_int_equal(getFuturePatientId(), 13);
}

static void test_getFutureSessionId(){
    assert_int_equal(getFutureSessionId(), 37);
}

int main_manager(void)
{
    const struct CMUnitTest tests_manager[]=
            {

                    cmocka_unit_test(test_createEmptyFolder),
                    cmocka_unit_test(test_getFutureFolderId),
                    cmocka_unit_test(test_getFuturePatientId),
                    cmocka_unit_test(test_getFutureSessionId),
                    cmocka_unit_test(test_createEmptySession),
                    cmocka_unit_test(test_createNewSession)
            };
    return cmocka_run_group_tests_name("Test ext_files_manager module",tests_manager,NULL,NULL);
}