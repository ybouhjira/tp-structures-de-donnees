#include <stdio.h>
#include <stdlib.h>

#include "CuTest/CuTest.h"

#include "lib/liste.h"

void Test_Inserer_Liste(CuTest *tc)
{
  CuAssertTrue(tc, 0);

}

void Test_Supprimer_Liste(CuTest *tc)
{
  CuAssertTrue(tc, 0);
}

void Test_Taille_Liste(CuTest *tc)
{
  CuAssertTrue(tc, 0);
}

void Test_Premier_liste(CuTest *tc)
{
  CuAssertTrue(tc, 0);
}


CuSuite* Liste_get_suite()
{
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, Test_Inserer_Liste);
  SUITE_ADD_TEST(suite, Test_Premier_liste);
  SUITE_ADD_TEST(suite, Test_Supprimer_Liste);
  SUITE_ADD_TEST(suite, Test_Taille_Liste);
  return suite;
}
