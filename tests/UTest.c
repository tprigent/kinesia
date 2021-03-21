/*!
* \file UTest.c
* \brief Functions to run CMocka tests
*/

#include "UTest_UI.h"
#include "UTest_BDD.h"
#include "UTest_session.h"


int main(void){
    int i = main_session();
    return i;
}