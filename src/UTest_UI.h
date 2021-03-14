/*!
* \file UTest_UI.c
* \brief Functions to test the functions linking structure and UI
*/

#ifndef UTEST_UI_H
#define UTEST_UI_H

static int setup_patient(void **state);
static void test_get_name_UI(void **state);
static void test_get_date_UI(void **state);
static void test_get_height_UI(void **state);
static void test_get_weight_UI(void **state);
static void test_get_height_weight_UI(void **state);
static void test_get_first_consultation_UI(void **state);
static void test_get_adress_UI(void **state);
static int teardown(void **state);
int main_UI(void);


#endif //UTEST_UI_H
