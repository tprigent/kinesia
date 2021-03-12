#include <stdarg.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stddef.h>
#include <cmocka.h>
#include "UTest_BDD.h"
#include "patient.h"
#include "structures.h"

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

static int setup_address(void **state) {
    Address * address = malloc(sizeof(Address));
    if(allocateAddress(address) != 0) return -1;
    assert_non_null(address->number);
    assert_non_null(address->street);
    assert_non_null(address->postCode);
    assert_non_null(address->city);
    assert_non_null(address->other_info);
    *state = address;
    return 0;
}

static int setup_date(void **state) {
    Date * date = malloc(sizeof(Date));
    assert_non_null(date);
    *state = date;
    return 0;
}

static void test_setPatient(void **state) {
    Patient * patient = (Patient *) *state;
    Date date;
    setDate(&date, 12, 3, 2021);
    Address address;
    allocateAddress(&address);
    setAddress(&address, "15", "rue de la soif", "35000", "Rennes", "APPT 30");
    assert_int_equal(0, setPatient(patient, "Claude", "Francois", date, "ici", 0, address, "0123456789", "mailAddress", "chanteur", "11111111", 68, 170, date, "test",1));
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

static void test_setAddress(void **state) {
    Address * address = (Address *) *state;
    setAddress(address, "15", "rue de la soif", "35000", "Rennes", "APPT 30");
    assert_string_equal("15", address->number);
    assert_string_equal("rue de la soif", address->street);
    assert_string_equal("35000", address->postCode);
    assert_string_equal("Rennes", address->city);
    assert_string_equal("APPT 30", address->other_info);
}

static void test_setDate(void **state) {
    Date * date = *state;
    setDate(date, 12, 3, 2021);
    assert_int_equal(12, date->day);
    assert_int_equal(3, date->month);
    assert_int_equal(2021, date->year);
}

static int teardown_patient(void **state) {
    Patient * patient = (Patient *) *state;
    freePatient(&patient);
    return 0;
}

static int teardown_address(void **state) {
    Address * address = (Address *) *state;
    freeAddress(address);
    free(address);
    return 0;
}

static int teardown_date(void **state) {
    Date * date = (Date *) *state;
    free(date);
    return 0;
}

int main_BDD(void)
{

    const struct CMUnitTest tests_BDD[]=
            {
                    cmocka_unit_test_setup_teardown(test_setPatient, setup_patient, teardown_patient),
                    cmocka_unit_test_setup_teardown(test_setAddress, setup_address, teardown_address),
                    cmocka_unit_test_setup_teardown(test_setDate, setup_date, teardown_date),
            };
    return cmocka_run_group_tests_name("Test counter module",tests_BDD,NULL,NULL);
}
