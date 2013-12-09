#include <stdio.h>
#include <stdlib.h>

#include "CuTest/CuTest.h"

#include "lib/liste.h"

// Tests
void Test_Inserer_Liste(CuTest *tc)
{
  // Test 1:
  Liste *liste = liste_creer();
  int val5 = 5;
  liste_inserer(liste, &val5, 0);

  CuAssertIntEquals(tc, 1, liste_taille(liste));
  CuAssertTrue(tc, 5 == *(int *) liste_premier(liste)->val);
  CuAssertTrue(tc, NULL == liste_premier(liste)->suivant);

  // Test 2:
  // insértion de plusieurs valeurs
  int nbr = 10;
  Liste *liste2 = liste_creer();
  int i;
  for (i = 0; i < nbr; ++i)
    {
      int i2 = i * 2;
      liste_inserer(liste2, &i2, 0);
    }
  // test des valeurs
  ElementListe *courant = liste_premier(liste2);
  for (i = 0; i < nbr; ++i, courant = courant->suivant)
    CuAssertIntEquals(tc, 2 * (nbr - i - 1), *(int*) courant->val);
  CuAssertTrue(tc, NULL == courant);

  // Test 3:
  Liste *liste3 = liste_creer();
  for(i = 0; i < 10; ++i)
    liste_inserer(liste3, &i, liste_taille(liste3));
  CuAssertIntEquals(tc, 10, liste_taille(liste3));
}

void Test_Supprimer_Liste(CuTest *tc)
{
  Liste *liste = liste_creer();
  int i;
  for(i = 0; i < 4; ++i) liste_inserer(liste, &i, liste_taille(liste));

  liste_supprimer(liste, 0);
  CuAssertIntEquals(tc, 3, liste_taille(liste));

  liste_supprimer(liste, liste_taille(liste) - 1);
  CuAssertIntEquals(tc, 1, *(int*) liste_premier(liste)->val);
  CuAssertIntEquals(tc, 2, *(int*) liste_premier(liste)->suivant->val);

  CuAssertIntEquals(tc, 2, liste_taille(liste));

  // Vider la liste
  while(liste_taille(liste)) liste_supprimer(liste, 0);


  CuAssertIntEquals(tc, 0, liste_taille(liste));
}

void Test_Taille_Liste(CuTest *tc)
{
  Liste *liste = liste_creer();
  CuAssertIntEquals(tc, liste_taille(liste), 0);
}

void Test_Premier_liste(CuTest *tc)
{
  Liste *liste = liste_creer();
  int i;
  for (i = 0; i < 10; ++i) liste_inserer(liste, &i, liste_taille(liste));

  CuAssertIntEquals(tc, 0, *(int*) liste_premier(liste)->val);
  CuAssertIntEquals(tc, 1, *(int*) liste_premier(liste)->suivant->val);
}

void test_liste_pos(CuTest *tc)
{
  Liste *liste = liste_creer();
  int i;
  for(i = 0; i < 19; ++i)
    liste_inserer(liste, &i, liste_taille(liste));

  int val = 3;
  CuAssertIntEquals(tc, 3, liste_pos_val(&val, liste));
  val = 44;
  CuAssertIntEquals(tc, -1, liste_pos_val(&val, liste));
  liste_detruire(&liste);
}

CuSuite* Liste_get_suite()
{
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, Test_Inserer_Liste);
  SUITE_ADD_TEST(suite, Test_Premier_liste);
  SUITE_ADD_TEST(suite, Test_Supprimer_Liste);
  SUITE_ADD_TEST(suite, Test_Taille_Liste);
  SUITE_ADD_TEST(suite, test_liste_pos);
  return suite;
}


