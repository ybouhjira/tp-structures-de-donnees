#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "CuTest/CuTest.h"

#include "lib/arbre.h"

// Helpers:
void CuAssertArbreOrdonnee(CuTest *tc, Arbre *arbre)
{
  if(arbre->droit)
    {
      CuAssertTrue(tc, arbre->val <= arbre->droit->val);
      CuAssertArbreOrdonnee(tc, arbre->droit);
    }
  if(arbre->gauche)
    {
      CuAssertTrue(tc, arbre->val >= arbre->gauche->val);
      CuAssertArbreOrdonnee(tc, arbre->gauche);
    }
}

// Tests:
void Test_Inserer_arbre_ordonnee(CuTest *tc)
{
  srand(time(NULL));
  Arbre *arbre = NULL;

  int i;
  for (i = 0; i < 1000; ++i) Inserer_arbre_ordnnee(&arbre, rand() % 10000);

  CuAssertArbreOrdonnee(tc, arbre);

}

void Test_Supprimer_arbre_ordonnee(CuTest *tc)
{
  srand(time(NULL));
  Arbre *arbre = NULL;

  int i;
  for (i = 0; i < 10000; ++i) Inserer_arbre_ordnnee(&arbre, rand() % 10000);

  // Etre sur que 100 existe
  Inserer_arbre_ordnnee(&arbre, 100);

  Supprimer_arbre_ordonnee(&arbre, 100);
  Supprimer_arbre_ordonnee(&arbre, 100);
  Supprimer_arbre_ordonnee(&arbre, 100);

  CuAssertArbreOrdonnee(tc, arbre);
}

void Test_Longueur_arbre(CuTest *tc)
{
  /*
   *   1
   *  / \
   * 2   3
   *    / \
   *   5   6
   *      / \
   *     8   7
   *      \
   *       9
   */
    Arbre *arbre = Creer_Arbre(1);
    CuAssertIntEquals(tc, 0, Longueur_arbre(arbre, 0));
    arbre->gauche = Creer_Arbre(2);
    CuAssertIntEquals(tc, 1, Longueur_arbre(arbre, 0));

    Arbre *a3 = arbre->droit = Creer_Arbre(3);
    a3->gauche = Creer_Arbre(5);
    a3->droit = Creer_Arbre(6);
    a3->droit->droit = Creer_Arbre(7);
    a3->droit->gauche = Creer_Arbre(8);

    CuAssertIntEquals(tc, 3, Longueur_arbre(arbre, 0));

    a3->droit->gauche->droit = Creer_Arbre(9);

    CuAssertIntEquals(tc, 4, Longueur_arbre(arbre, 0));

    Detruire_arbre(arbre);
}


CuSuite* Arbre_get_suite()
{
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, Test_Longueur_arbre);
  SUITE_ADD_TEST(suite, Test_Inserer_arbre_ordonnee);
  SUITE_ADD_TEST(suite, Test_Supprimer_arbre_ordonnee);
  return suite;
}
