#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "CuTest/CuTest.h"

#include "lib/pile.h"

void test_pile_empiler(CuTest *tc)
{
  Pile *pile = NULL;

  pile_empiler(&pile, 1);
  pile_empiler(&pile, 2);
  pile_empiler(&pile, 3);


  CuAssertIntEquals(tc, 3, liste_taille(pile));

  CuAssertIntEquals(tc, 3, pile->val);
  CuAssertIntEquals(tc, 2, pile->suiv->val);
  CuAssertIntEquals(tc, 1, pile->suiv->suiv->val);

  CuAssertTrue(tc, NULL == pile->suiv->suiv->suiv);
}

CuSuite *Pile_get_suite()
{
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_pile_empiler);
  return suite;
}


