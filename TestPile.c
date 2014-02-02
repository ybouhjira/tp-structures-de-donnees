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

void test_pile_depiler(CuTest *tc)
{
  Pile *pile = NULL;

  int i;
  for(i = 0; i < 10; ++i) pile_empiler(&pile, i);

  CuAssertIntEquals(tc, 10, liste_taille(pile));

  for(i = 9; i >= 0; --i)
    {
      int valeur = pile_depiler(&pile);
      CuAssertIntEquals(tc, i, liste_taille(pile));
      CuAssertIntEquals(tc, i, valeur);
    }

  CuAssertTrue(tc, pile == NULL);
}

void test_pile_afficher(CuTest *tc)
{
  Pile *pile = NULL;
  int i;
  for(i = 0; i < 10; ++i) pile_empiler(&pile, i);

  pile_afficher(&pile);

  CuAssertIntEquals(tc, 10, liste_taille(pile));
}

CuSuite *Pile_get_suite()
{
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_pile_empiler);
  SUITE_ADD_TEST(suite, test_pile_depiler);
  SUITE_ADD_TEST(suite, test_pile_afficher);
  return suite;
}


