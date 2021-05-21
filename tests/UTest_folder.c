
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

static void test_getIdFolder(){

    int *t;
    t = getIdFolder(1);
    assert_int_equal(1,t[0]);
    free(t);

}

static void test_getNameFolder(){

    assert_string_equal("Entorse de la cheville",getNameFolder(1));

}

static void test_addFolder(){

    Folder *folder;
    if(allocateFolder(&folder) == -1){
        fprintf(stderr,"Erreur alloc folder\n");
    }

    setFolder(folder,"Folder test","Test","Details",1,1,1,1,1,1);

    assert_int_equal(1,addFolder(folder));

    free(folder);

}

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

static void test_deleteFolder(){
    assert_int_equal(1,deleteFolder(100));
}

static void test_getNbFolder(){
    assert_int_equal(2,getNbFolder(6));
}

/*!
 * \brief main function which runs the tests for BDD
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
                    cmocka_unit_test(test_deleteFolder)
            };
    return cmocka_run_group_tests_name("Folder test module",tests_folder,NULL,NULL);
}