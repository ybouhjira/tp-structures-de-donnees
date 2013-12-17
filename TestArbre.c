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
void test_inserer_arbre_ordonnee(CuTest *tc)
{
  srand(time(NULL));
  Arbre *arbre = NULL;

  int i;
  for (i = 0; i < 1000; ++i) Inserer_arbre_ordnnee(&arbre, rand() % 10000);

  CuAssertArbreOrdonnee(tc, arbre);

}

void test_supprimer_arbre_ordonnee(CuTest *tc)
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

void test_longueur_arbre(CuTest *tc)
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
  Arbre *arbre = arbre_creer(1);
  CuAssertIntEquals(tc, 0, Longueur_arbre(arbre, 0));
  arbre->gauche = arbre_creer(2);
  CuAssertIntEquals(tc, 1, Longueur_arbre(arbre, 0));

  Arbre *a3 = arbre->droit = arbre_creer(3);
  a3->gauche = arbre_creer(5);
  a3->droit = arbre_creer(6);
  a3->droit->droit = arbre_creer(7);
  a3->droit->gauche = arbre_creer(8);

  CuAssertIntEquals(tc, 3, Longueur_arbre(arbre, 0));

  a3->droit->gauche->droit = arbre_creer(9);

  CuAssertIntEquals(tc, 4, Longueur_arbre(arbre, 0));

  arbre_detruire(&arbre);
}

void test_arbre_egaux(CuTest *tc)
{
  Arbre *a1 = arbre_creer(1),
      *a2 = arbre_creer(2),
      *a3 = arbre_creer(3),
      *a4 = arbre_creer(4),
      *a5 = arbre_creer(5),
      *a6 = arbre_creer(6),
      *a7 = arbre_creer(7);

  a1->droit = a2;
  /**/a2->droit = a4;
  /*      */a4->droit = a5;
  /*      */a4->gauche = a6;
  /**/a2->gauche = a7;
  a1->gauche = a3;


  Arbre *b1 = arbre_creer(1),
      *b2 = arbre_creer(2),
      *b3 = arbre_creer(3),
      *b4 = arbre_creer(4),
      *b5 = arbre_creer(5),
      *b6 = arbre_creer(6),
      *b7 = arbre_creer(7);

  b1->droit = b2;
  /**/b2->droit = b4;
  /*      */b4->droit = b5;
  /*      */b4->gauche = b6;
  /**/b2->gauche = b7;
  b1->gauche = b3;

  CuAssertTrue(tc, arbre_egaux(a1, b1));

  arbre_detruire(&b7);

  CuAssertTrue(tc, !arbre_egaux(a1, b1));

  arbre_detruire(&a1);
  arbre_detruire(&b1);
}

CuSuite* Arbre_get_suite()
{
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_longueur_arbre);
  SUITE_ADD_TEST(suite, test_inserer_arbre_ordonnee);
  SUITE_ADD_TEST(suite, test_supprimer_arbre_ordonnee);
  SUITE_ADD_TEST(suite, test_arbre_egaux);
  return suite;
}
