#include <CuTest/CuTest.h>
#include <stdio.h>

CuSuite *Liste_get_suite();

void RunAllTests()
{
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    CuSuiteAddSuite(suite, Liste_get_suite());
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}

int main ()
{
    RunAllTests();
    return 0;
}
