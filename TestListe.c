#include <stdio.h>
#include <stdlib.h>

#include "CuTest/CuTest.h"

#include "lib/liste.h"

// Tests
void Test_Inserer_Liste(CuTest *tc)
{
  // Test 1:
  Liste *liste = creer_liste();
  int val5 = 5;
  inserer_liste(liste, &val5, 0);

  CuAssertIntEquals(tc, 1, taille_liste(liste));
  CuAssertTrue(tc, 5 == *(int *) premier_liste(liste)->val);
  CuAssertTrue(tc, NULL == premier_liste(liste)->suivant);

  // Test 2:
  // insértion de plusieurs valeurs
  int nbr = 10;
  Liste *liste2 = creer_liste();
  int i;
  for (i = 0; i < nbr; ++i)
    {
      int i2 = i * 2;
      inserer_liste(liste2, &i2, 0);
    }
  // test des valeurs
  ElementListe *courant = premier_liste(liste2);
  for (i = 0; i < nbr; ++i, courant = courant->suivant)
    CuAssertIntEquals(tc, 2 * (nbr - i - 1), *(int*) courant->val);
  CuAssertTrue(tc, NULL == courant);

  // Test 3:
    Liste *liste3 = creer_liste();
    for(i = 0; i < 10; ++i)
      inserer_liste(liste3, &i, taille_liste(liste3));
    CuAssertIntEquals(tc, 10, taille_liste(liste3));
}

void Test_Supprimer_Liste(CuTest *tc)
{
  Liste *liste = creer_liste();
  int i;
  for(i = 0; i < 4; ++i) inserer_liste(liste, &i, taille_liste(liste));

  supprimer_liste(liste, 0);
  CuAssertIntEquals(tc, 3, taille_liste(liste));

  supprimer_liste(liste, taille_liste(liste) - 1);
  CuAssertIntEquals(tc, 1, *(int*) premier_liste(liste)->val);
  CuAssertIntEquals(tc, 2, *(int*) premier_liste(liste)->suivant->val);

  CuAssertIntEquals(tc, 2, taille_liste(liste));

  // Vider la liste
  while(taille_liste(liste)) supprimer_liste(liste, 0);


  CuAssertIntEquals(tc, 0, taille_liste(liste));
}

void Test_Taille_Liste(CuTest *tc)
{
  Liste *liste = creer_liste();
  CuAssertIntEquals(tc, taille_liste(liste), 0);
}

void Test_Premier_liste(CuTest *tc)
{
  Liste *liste = creer_liste();
  int i;
  for (i = 0; i < 10; ++i) inserer_liste(liste, &i, taille_liste(liste));

  CuAssertIntEquals(tc, 0, *(int*) premier_liste(liste)->val);
  CuAssertIntEquals(tc, 1, *(int*) premier_liste(liste)->suivant->val);
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


