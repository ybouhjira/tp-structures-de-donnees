#include <stdio.h>
#include <stdlib.h>

#include "CuTest/CuTest.h"

#include "lib/arbre.h"

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
  return suite;
}
