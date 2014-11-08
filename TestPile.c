#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "CuTest/CuTest.h"

#include "lib/pile.h"

void test_pile_copier(CuTest *tc)
{
  Pile *pile = NULL;

  // Doit retourner une pile vide si on copie une pile vide
  CuAssertTrue(tc, pile_copier(&pile) == NULL);

  int i;
  for(i = 3; i < 42; i++)
    pile_empiler(&pile, i);

  Pile *copie = pile_copier(&pile);

  while(pile)
    {
      CuAssertTrue(tc, copie != NULL); // pile etre de meme taille que copie
      CuAssertIntEquals(tc, pile_depiler(&pile), pile_depiler(&copie));
    }
}

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
  SUITE_ADD_TEST(suite, test_pile_copier);

  return suite;
}


