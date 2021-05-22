/*!
* \file UTest_patient.c
* \brief Functions to test patient related functions
*/

#include <stdarg.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stddef.h>
#include <cmocka.h>
#include "../src/model/patient_manager.h"
#include "../src/controller/BDD_to_struct_patient.h"
#include "../src/controller/struct_to_BDD_patient.h"
#include "../src/controller/BDD_to_struct_folder.h"


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
    assert_string_equal("68", patient->weight);
    assert_string_equal("170", patient->height);
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

/*!
 * \brief test getPatient function
*/
static void test_getPatient(){

    Patient *patient = getPatient(-1);
    assert_null(patient);
    patient=getPatient(1);
    assert_string_equal("François", patient->name);
    assert_string_equal("Claude", patient->firstname);
    freePatient(&patient);

}

/*!
 * \brief test getPatient function
 * Check if the patient is properly added in database
*/
static void test_addPatient(){

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

    freePatient(&p);

}

/*!
 * \brief test getNameFirstnameIdPatient function
 * Check if all infos are well found in DB
*/
static void test_getNameFirstnameIdPatient(){

    int i,nbArchivedPatient;
    int *idArchivePatient;
    char** nomArchivePatient;

    nbArchivedPatient = getNbPatient(ARCHIVED);

    idArchivePatient = (int*)calloc(2,sizeof(int));
    nomArchivePatient = (char**)calloc(2,sizeof(void *));

    assert_int_equal(1,getNameFirstnameIdPatient(idArchivePatient,nomArchivePatient,ARCHIVED,NAME_ASC));
    assert_string_equal("Claude François",nomArchivePatient[1]);
    assert_int_equal(1,getNameFirstnameIdPatient(idArchivePatient,nomArchivePatient,ARCHIVED,NAME_DESC));
    assert_string_equal("Claude François",nomArchivePatient[0]);
    assert_int_equal(1,getNameFirstnameIdPatient(idArchivePatient,nomArchivePatient,ARCHIVED,FIRSTNAME_DESC));
    assert_string_equal("Claude François",nomArchivePatient[0]);
    assert_int_equal(1,getNameFirstnameIdPatient(idArchivePatient,nomArchivePatient,ARCHIVED,FIRSTNAME_ASC));
    assert_string_equal("Claude François",nomArchivePatient[1]);
    free(idArchivePatient);

    for(i=0;i<nbArchivedPatient;i++)
        free(nomArchivePatient[i]);

    free(nomArchivePatient);

}

/*!
 * \brief test getNameFirstname function
*/
static void test_getNameFirstnamePatient(){

    char * c;
    c=getNameFirstnamePatient(1);
    assert_string_equal("Claude François",c);
    free(c);

}

/*!
 * \brief test getNbPatient function
 * Check if the number of active and archived patients is correct
*/
static void test_getNbPatient(){

    assert_int_equal(10,getNbPatient(ACTIVE));
    assert_int_equal(2,getNbPatient(ARCHIVED));

}

/*!
 * \brief test deletePatient function
 * Check if the concerned patient is properly deleted in DB
*/
static void test_deletePatient(){
    assert_int_equal(1,deletePatient(5));
}

/*!
 * \brief test searchPatient function
 * Check if a patient in DB is well found by the function
*/
static void test_searchPatient(){

    int i;
    int *idPatient;
    char** nomPatient;

    idPatient = (int*)calloc(10,sizeof(int));
    nomPatient = (char**)calloc(10,sizeof(void *));

    assert_int_equal(1,searchPatient("Priam",nomPatient,idPatient,10));

    free(idPatient);
    for(i=0;i<10;i++)
        free(nomPatient[i]);

    free(nomPatient);

}

/*!
 * \brief test modifyPatient function
 * Check if the property modified is well taken into account by DB
*/
static void test_modifyPatient(){
    Patient *patient = getPatient(1);
    patient->birthdate.day = 2;
    assert_int_equal(1, modifyPatient(patient));
    patient = getPatient(1);
    assert_int_equal(2, patient->birthdate.day);
}

/*!
 * \brief test getPatientIDFromFolder function
*/
static void test_getPatientIDFromFolder(){
    assert_int_equal(1, getPatientIDFromFolder(1));
}

/*!
 * \brief test getFuturePatientId function
*/
static void test_getFuturePatientId(){
    assert_int_equal(getFuturePatientId(), 13);
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
 * \brief Function to run all tests for patient related functions
*/
int main_patient(void)
{

    const struct CMUnitTest tests_patient[]=
            {
                    cmocka_unit_test_setup_teardown(test_setPatient, setup_patient, teardown_patient),
                    cmocka_unit_test_setup_teardown(test_setAddress, setup_address, teardown_address),
                    cmocka_unit_test_setup_teardown(test_setDate, setup_date, teardown_date),
                    cmocka_unit_test(test_getPatient),
                    cmocka_unit_test(test_addPatient),
                    cmocka_unit_test(test_modifyPatient),
                    cmocka_unit_test(test_getNbPatient),
                    cmocka_unit_test(test_getNameFirstnameIdPatient),
                    cmocka_unit_test(test_getNameFirstnamePatient),
                    cmocka_unit_test(test_searchPatient),
                    cmocka_unit_test(test_deletePatient),
                    cmocka_unit_test(test_getPatientIDFromFolder),
                    cmocka_unit_test(test_getFuturePatientId)
            };
    return cmocka_run_group_tests_name("Patient test module",tests_patient,NULL,NULL);
}