/*!
* \file UTest.c
* \brief Functions to run CMocka tests
*/

#include "UTest_UI.h"
#include "UTest_BDD.h"


int main(void){
    int i = main_UI()*main_BDD();
    return i;
}