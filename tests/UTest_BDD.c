/*!
* \file UTest_BDD.c
* \brief Functions to test the functions linking structure and BDD, and allocations
*/

#include <stdarg.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stddef.h>
#include <cmocka.h>
#include "UTest_BDD.h"
#include "../src/model/patient_manager.h"
#include "../src/controller/BDD_to_struct_patient.h"
#include "../src/controller/struct_to_BDD_patient.h"
#include "../src/controller/struct_to_BDD_folder.h"
#include "../src/controller/BDD_to_struct_folder.h"
#include "../src/model/patient_manager.h"
#include "../src/model/structures.h"

/*!
 * \brief Setup function which allocates a patient
 *
 * This function allocates a patient and puts it in *state
 *
 * \param[in] A pointer address to pass the allocated patient
 * \param[out] An int to know if patient is well allocated
*/
static int setup_patient(void **state) {
    Patient *patient = (Patient *) NULL;
    if(allocatePatient(&patient) != 0) return -1;

    assert_non_null(patient);
    assert_non_null(patient->global_pathologies);
    assert_non_null(patient->mail_address);
    assert_non_null(patient->phone_number);
    assert_non_null(patient->place_birth);
    assert_non_null(patient->firstname);
    assert_non_null(patient->name);
    assert_non_null(patient->ssn);
    assert_non_null(patient->job);
    *state = patient;
    return 0;
}
/*!
 * \brief Setup function which allocates an address
 *
 * This function allocates an address and puts it in *state
 *
 * \param[in] A pointer address to pass the allocated address
 * \param[out] An int to know if address is well allocated
*/
static int setup_address(void **state) {
    Address * address = malloc(sizeof(Address));
    if(allocateAddress(address) != 0) return -1;
    assert_non_null(address->street);
    assert_non_null(address->postCode);
    assert_non_null(address->city);
    assert_non_null(address->other_info);
    *state = address;
    return 0;
}

/*!
 * \brief Setup function which allocates a Date
 *
 * This function allocates a Date and puts it in *state
 *
 * \param[in] A pointer address to pass the allocated date
 * \param[out] An int to know if date is well allocated
*/
static int setup_date(void **state) {
    Date * date = malloc(sizeof(Date));
    assert_non_null(date);
    *state = date;
    return 0;
}

/*!
 * \brief function test_setPatient which runs a test for function setPatient()
 *
 * \param[in] A pointer address to pass the allocated patient
*/
static void test_setPatient(void **state) {
    Patient * patient = (Patient *) *state;
    Date date;
    setDate(&date, 12, 3, 2021);

    Address address = {"rue de la soif", "35000", "Rennes", "none"};

    assert_int_equal(0, setPatient(patient, "Claude", "Francois", date, "ici", 0, address, "0123456789", "mailAddress", "chanteur", "11111111", "68", "170", date, "test",1,0));
    assert_string_equal("Claude", patient->name);
    assert_string_equal("Francois", patient->firstname);
    assert_string_equal("ici", patient->place_birth);
    assert_string_equal("0123456789", patient->phone_number);
    assert_string_equal("mailAddress", patient->mail_address);
    assert_string_equal("chanteur", patient->job);
    assert_string_equal("11111111", patient->ssn);
    assert_string_equal("test", patient->global_pathologies);
    assert_int_equal(0, patient->gender);
    assert_int_equal(68, patient->weight);
    assert_int_equal(170, patient->height);
    assert_int_equal(1, patient->id);
}

/*!
 * \brief function test_setAddress which runs a test for function setAddress()
 *
 * \param[in] A pointer address to pass the allocated address
*/
static void test_setAddress(void **state) {
    Address * address = (Address *) *state;
    setAddress(address, "15 rue de la soif", "35000", "Rennes", "APPT 30");
    assert_string_equal("15 rue de la soif", address->street);
    assert_string_equal("35000", address->postCode);
    assert_string_equal("Rennes", address->city);
    assert_string_equal("APPT 30", address->other_info);
}

/*!
 * \brief function test_setDate which runs a test for function setDate()
 *
 * \param[in] A pointer address to pass the allocated date
*/
static void test_setDate(void **state) {
    Date * date = *state;
    setDate(date, 12, 3, 2021);
    assert_int_equal(12, date->day);
    assert_int_equal(3, date->month);
    assert_int_equal(2021, date->year);
}

static void test_getPatient(void **state){

    Patient *p = getPatient(-1);
    assert_null(p);

}

static void test_addPatient(void **state){

    Patient *p = NULL;
    Address adresse;
    Date birthDate;
    Date firtsConsDate;

    if(allocatePatient(&p) == -1 || allocateAddress(&adresse) == -1 ){
        fprintf(stderr,"Erreur d'allocation\n");
    }

    if(setDate(&birthDate,1,1,1) == -1 ){
        fprintf(stderr,"Erreur setDate birthdate\n");
    }
    if(setDate(&firtsConsDate,1,1,1) == -1 ){
        fprintf(stderr,"Erreur setDate first consultation\n");
    }

    setAddress(&adresse,"1","1","1","1");

    if(setPatient(p,"1","1",birthDate,"1",1,
                  adresse,"1",
                  "1","1",
                  "1","1",
                  "1",firtsConsDate,"1",0,1) != 0) {
        fprintf(stderr, "Erreur setPatient");
        p = NULL;
    }

    assert_int_equal(1,addPatient(p));

}

static void test_modifyPatient(void **state){

    Patient *p = NULL;
    Address adresse;
    Date birthDate;
    Date firtsConsDate;

    if(allocatePatient(&p) == -1 || allocateAddress(&adresse) == -1 ){
        fprintf(stderr,"Erreur d'allocation\n");
    }

    if(setDate(&birthDate,2,1,1) == -1 ){
        fprintf(stderr,"Erreur setDate birthdate\n");
    }
    if(setDate(&firtsConsDate,12,1,1) == -1 ){
        fprintf(stderr,"Erreur setDate first consultation\n");
    }

    setAddress(&adresse,"1","1","1","1");

    if(setPatient(p,"1","1",birthDate,"1",1,
                  adresse,"1",
                  "1","1",
                  "1",1,
                  1,firtsConsDate,"1",0,0) != 0) {
        fprintf(stderr, "Erreur setPatient");
        p = NULL;
    }

    p->id=2;

    assert_int_equal(1,modifyPatient(p));

}

static void test_getNameFirstnamePatient(void **state){

    assert_string_equal("Francois Claude",getNameFirstnamePatient(1));
    assert_null(getNameFirstnamePatient(-1));

}

static void test_getArchivedPatientID(void **state){

    assert_int_equal(1,getArchivedPatientID());

}

static void test_getActivePatientID(void **state){

    int *tab;
    tab = getActivePatientID();
    assert_int_equal(2,tab[1]);
    assert_int_equal(3,tab[2]);

}

static void test_getNbActivePatient(void **state){

    assert_int_equal(5,getNbActivePatient());

}

static void test_getNbarchivedPatient(void **state){

    assert_int_equal(1,getNbArchivedPatient());

}

static void test_getFolder(void **state){

    Folder *f;
    f = getFolder(1);

    assert_int_equal(1,f->idFolder);
    assert_string_equal("Entorse de la cheville",f->folderName);
    assert_string_equal("Entorse",f->pathology);
    assert_string_equal("Voir fichiers joints,  retour à la ligne automatique à gérer...",f->details);
    assert_int_equal(2021,f->startOfTreatment.year);
    assert_int_equal(3,f->startOfTreatment.month);
    assert_int_equal(1,f->startOfTreatment.day);
    assert_int_equal(1,f->numberOfFiles);
    assert_int_equal(1,f->idPatient);

}

static void test_getNameFolder(void **state){

    assert_string_equal("Entorse de la cheville",getNameFolder(1));

}

static void test_getIdFolder(1){

int *t;
t = getIdFolder(1);
assert_int_equal(1,t[0]);

}

static void test_addFolder(void **state){

    Folder *f;
    if(allocateFolder(&folder) == -1){
        fprintf(stderr,"Erreur alloc folder\n");
        return NULL;
    }

    setFolder(folder,"Folder test","Test","Details",1,1,1,1,1,1);

    assert_int_equal(1,addFolder(f));

}

static void test_modifyFolder(void **state){

    Folder *f;
    f = getFolder();


}

/*!
 * \brief Teardown function which desallocates the patient
 *
 * This function desallocates the patient allocated by setup function
 *
 * \param[in] A pointer addressto pass the allocated patient
 * \param[out] An int to tell that desallocation worked
*/
static int teardown_patient(void **state) {
    Patient * patient = (Patient *) *state;
    freePatient(&patient);
    return 0;
}

/*!
 * \brief Teardown function which desallocates the address
 *
 * This function desallocates the address allocated by setup function
 *
 * \param[in] A pointer addressto pass the allocated address
 * \param[out] An int to tell that desallocation worked
*/
static int teardown_address(void **state) {
    Address * address = (Address *) *state;
    freeAddress(address);
    free(address);
    return 0;
}

/*!
 * \brief Teardown function which desallocates the date
 *
 * This function desallocates the date allocated by setup function
 *
 * \param[in] A pointer address to pass the allocated date
 * \param[out] An int to tell that desallocation worked
*/
static int teardown_date(void **state) {
    Date * date = (Date *) *state;
    free(date);
    return 0;
}

/*!
 * \brief main function which runs the tests for BDD
 *
 * \param[out] An int to tell if tests are passed
*/
int main_BDD(void)
{

    const struct CMUnitTest tests_BDD[]=
            {
                    cmocka_unit_test_setup_teardown(test_setPatient, setup_patient, teardown_patient),
                    cmocka_unit_test_setup_teardown(test_setAddress, setup_address, teardown_address),
                    cmocka_unit_test_setup_teardown(test_setDate, setup_date, teardown_date),
                    cmocka_unit_test(test_getPatient),
                    cmocka_unit_test(test_addPatient),
                    cmocka_unit_test(test_modifyPatient),
                    cmocka_unit_test(test_getNameFirstnamePatient),
                    cmocka_unit_test(test_getArchivedPatientID),
                    cmocka_unit_test(test_getNbActivePatient),
                    cmocka_unit_test(test_getNbarchivedPatient),
                    cmocka_unit_test(test_getFolder),
                    cmocka_unit_test(test_getIdFolder),
                    cmocka_unit_test(test_getNameFolder),
                    cmocka_unit_test(test_addFolder),
                    cmocka_unit_test(test_modifyFolder)
            };
    return cmocka_run_group_tests_name("Test counter module",tests_BDD,NULL,NULL);
}
