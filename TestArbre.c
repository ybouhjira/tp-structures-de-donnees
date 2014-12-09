#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "CuTest/CuTest.h"

#include "lib/arbre.h"

// Helpers:
void CuAssertArbreOrdonnee(CuTest *tc, Arbre *arbre)
{
  if(arbre->d)
    {
      CuAssertTrue(tc, arbre->val <= arbre->d->val);
      CuAssertArbreOrdonnee(tc, arbre->d);
    }
  if(arbre->g)
    {
      CuAssertTrue(tc, arbre->val >= arbre->g->val);
      CuAssertArbreOrdonnee(tc, arbre->g);
    }
}

// Tests:
void test_inserer_arbre_ordonnee(CuTest *tc)
{
  srand(time(NULL));
  Arbre *arbre = NULL;

  int i;
  for (i = 0; i < 1000; ++i) arbre_insertion_ordonnee(&arbre, rand() % 10000);

  CuAssertArbreOrdonnee(tc, arbre);
}

void test_supprimer_arbre_ordonnee(CuTest *tc)
{
  srand(time(NULL));
  Arbre *arbre = NULL;

  int i;
  for (i = 0; i < 1000; ++i) arbre_insertion_ordonnee(&arbre, i * 2);

  // Etre sur que 100 existe
  arbre_insertion_ordonnee(&arbre, 100);

  //arbre_supprimer_arbre_ordonnee(&arbre, 100);
  //CuAssertTrue(tc, arbre_contient(arbre, 100));

  arbre_supprimer_arbre_ordonnee(&arbre, 100);
  CuAssertTrue(tc, !arbre_contient(arbre, 100));

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
  CuAssertIntEquals(tc, 0, arbre_longueur(arbre, 0));
  arbre->g = arbre_creer(2);
  CuAssertIntEquals(tc, 1, arbre_longueur(arbre, 0));

  Arbre *a3 = arbre->d = arbre_creer(3);
  a3->g = arbre_creer(5);
  a3->d = arbre_creer(6);
  a3->d->d = arbre_creer(7);
  a3->d->g = arbre_creer(8);

  CuAssertIntEquals(tc, 3, arbre_longueur(arbre, 0));

  a3->d->g->d = arbre_creer(9);

  CuAssertIntEquals(tc, 4, arbre_longueur(arbre, 0));

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

  a1->d = a2;
  /**/a2->d = a4;
  /*      */a4->d = a5;
  /*      */a4->g = a6;
  /**/a2->g = a7;
  a1->g = a3;


  Arbre *b1 = arbre_creer(1),
      *b2 = arbre_creer(2),
      *b3 = arbre_creer(3),
      *b4 = arbre_creer(4),
      *b5 = arbre_creer(5),
      *b6 = arbre_creer(6),
      *b7 = arbre_creer(7);

  b1->d = b2;
  /**/b2->d = b4;
  /*      */b4->d = b5;
  /*      */b4->g = b6;
  /**/b2->g = b7;
  b1->g = b3;

  //arbre_afficher(a1);
  CuAssertTrue(tc, arbre_egaux(a1, b1));

  arbre_detruire(&b7);
  b2->g = NULL;

  CuAssertTrue(tc, !arbre_egaux(a1, b1));

  arbre_detruire(&a1);
  arbre_detruire(&b1);
}

void test_arbre_min(CuTest *tc)
{
  Arbre *arbre = arbre_creer(1);

  int vals[11] = {12, 23, 8, -1, 3, 0, -1, 33, 23, 34, -2}, i;
  for(i = 0; i < 11; i++)
      arbre_insertion_ordonnee(&arbre, vals[i]);

  CuAssertIntEquals(tc, -2, arbre_min(arbre));
}

void test_arbre_max(CuTest *tc)
{
  Arbre *arbre = arbre_creer(1);

  int vals[11] = {12, 23, 8, -1, 3, 0, -1, 33, 100, 34, -2}, i;
  for(i = 0; i < 11; i++)
      arbre_insertion_ordonnee(&arbre, vals[i]);

  CuAssertIntEquals(tc, 100, arbre_max(arbre));
}

void test_arbre_contient(CuTest *tc)
{
  Arbre *arb = NULL;

  CuAssertIntEquals(tc, 0, arbre_contient(arb, 12));

  int vals[11] = {12, 23, 8, -1, 3, 0, -1, 33, 100, 34, -2}, i;
  for(i = 0; i < 11; i++)
      arbre_insertion_ordonnee(&arb, vals[i]);

  for(i = 0; i < 11; i++)
     CuAssertIntEquals(tc, 1, arbre_contient(arb, vals[i]));

  CuAssertIntEquals(tc, 0, arbre_contient(arb, -11));
  CuAssertIntEquals(tc, 0, arbre_contient(arb, 999));
  CuAssertIntEquals(tc, 0, arbre_contient(arb, -23));
  CuAssertIntEquals(tc, 0, arbre_contient(arb, 44));

}

CuSuite* Arbre_get_suite()
{
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_longueur_arbre);
  SUITE_ADD_TEST(suite, test_inserer_arbre_ordonnee);
  SUITE_ADD_TEST(suite, test_supprimer_arbre_ordonnee);
  SUITE_ADD_TEST(suite, test_arbre_egaux);
  SUITE_ADD_TEST(suite, test_arbre_min);
  SUITE_ADD_TEST(suite, test_arbre_max);
  SUITE_ADD_TEST(suite, test_arbre_contient);
  return suite;
}
