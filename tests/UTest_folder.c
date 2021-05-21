/*!
* \file UTest_folder.c
* \brief Functions to test folder related functions
*/

#include <stdarg.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stddef.h>
#include <cmocka.h>
#include "../src/model/patient_manager.h"
#include "../src/model/folder_manager.h"
#include "../src/model/session_manager.h"
#include "../src/controller/BDD_to_struct_patient.h"
#include "../src/controller/struct_to_BDD_patient.h"
#include "../src/controller/struct_to_BDD_folder.h"
#include "../src/controller/BDD_to_struct_folder.h"
#include "../src/controller/BDD_to_struct_session.h"
#include "../src/model/structures.h"
#include "../src/controller/struct_to_BDD_session.h"

/*!
 * \brief Test getFolder function
 *
 * Check if all the values are well charged in folder structure.
*/
static void test_getFolder(){

    Folder *f;
    f = getFolder(1);

    assert_int_equal(1,f->idFolder);
    assert_string_equal("Entorse de la cheville",f->folderName);
    assert_string_equal("Entorse cheville droite",f->pathology);
    assert_string_equal("Traumatisme de la cheville droite en inversion\n"
                        "en jouant au basket",f->details);
    assert_int_equal(2021,f->startOfTreatment.year);
    assert_int_equal(3,f->startOfTreatment.month);
    assert_int_equal(22,f->startOfTreatment.day);
    assert_int_equal(1,f->numberOfFiles);
    assert_int_equal(1,f->idPatient);

}

/*!
 * \brief Test getIdFolder function
 *
 * Test if the folder ID corresponds to the right patient
*/
static void test_getIdFolder(){
    int *t;
    t = getIdFolder(1);
    assert_int_equal(1,t[0]);
    free(t);

}

/*!
 * \brief Test getNameFolder function
*/
static void test_getNameFolder(){
    assert_string_equal("Entorse de la cheville",getNameFolder(1));
}

/*!
 * \brief Test addFolder function
 *
 * Check if a given folder is properly added in DB
*/
static void test_addFolder(){

    Folder *folder;
    if(allocateFolder(&folder) == -1){
        fprintf(stderr,"Erreur alloc folder\n");
    }

    setFolder(folder,"Folder test","Test","Details",1,1,1,1,1,1);

    assert_int_equal(1,addFolder(folder));

    free(folder);

}

/*!
 * \brief Test modifyFolder function
 *
 * Check if modifications are taken into account by the DB.
*/
static void test_modifyFolder(){

    Folder *f;
    f = getFolder(1);
    char* c = f->details;
    f->details="New details";
    assert_int_equal(1,modifyFolder(f));
    f = getFolder(1);
    assert_string_equal("New details",f->details);
    f->details = c;
    assert_int_equal(1,modifyFolder(f));
    free(c);
    free(f);

}

/*!
 * \brief Test deleteFolder function
 *
 * Check the wanted folder is properly deleted in DB
*/
static void test_deleteFolder(){
    assert_int_equal(1,deleteFolder(100));
}

/*!
 * \brief Test getNbFolder function
 *
 * Check the number returned corresponds to the number of patient's folder
*/
static void test_getNbFolder(){
    assert_int_equal(2,getNbFolder(6));
}

/*!
 * \brief Test getFutureFolderID function
*/
static void test_getFutureFolderId(){
    assert_int_equal(getFutureFolderId(), 10);
}

/*!
 * \brief Test createEmptyFolder function
 *
 * Check if the folder is well created and filled by default infos.
*/
static void test_createEmptyFolder(){
    Folder *folder = createEmptyFolder(1);
    assert_string_equal("Nouveau dossier", folder->folderName);
    assert_string_equal("Détails", folder->details);
    assert_string_equal("Pathologie", folder->pathology);
    assert_int_equal(0, folder->numberOfFiles);
    assert_int_equal(1, folder->idPatient);
    free(folder);
}

/*!
 * \brief main function which runs the tests for folder related functions
 *
 * \param[out] An int to tell if tests are passed
*/
int main_folder(void)
{

    const struct CMUnitTest tests_folder[]=
            {
                    cmocka_unit_test(test_getFolder),
                    cmocka_unit_test(test_getIdFolder),
                    cmocka_unit_test(test_addFolder),
                    cmocka_unit_test(test_getNameFolder),
                    cmocka_unit_test(test_getNbFolder),
                    cmocka_unit_test(test_modifyFolder),
                    cmocka_unit_test(test_deleteFolder),
                    cmocka_unit_test(test_getFutureFolderId),
                    cmocka_unit_test(test_createEmptyFolder)
            };
    return cmocka_run_group_tests_name("Folder test module",tests_folder,NULL,NULL);
}