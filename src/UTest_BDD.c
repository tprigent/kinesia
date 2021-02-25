#include <stdio.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>


int main_BDD(void)
{

    const struct CMUnitTest tests_BDD[]=
            {

            };
    return cmocka_run_group_tests_name("Test counter module",tests_BDD,NULL,NULL);
}