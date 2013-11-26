#include <stdio.h>
#include <stdlib.h>

#include "CuTest/CuTest.h"

#include "lib/liste.h"

// Helpers
void Debug_liste(Liste *liste)
{
  ElementListe *courant = Premier_liste(liste);
  printf("liste->permier = %p\n", courant);
  printf("liste->taille = %d\n", Taille_liste(liste));
  int i = 0;
  while(courant)
    {
      printf("\nliste[%d]->valeur = %d\n", i, courant->valeur);
      printf("liste[%d]->suivant = %p\n", i++, courant->suivant);
      courant = courant->suivant;
    }
}

// Tests
void Test_Inserer_Liste(CuTest *tc)
{

  // Test 1:
  Liste *liste = Creer_liste();
  Inserer_liste(liste, 5, 0);

  CuAssertIntEquals(tc, 1, Taille_liste(liste));
  CuAssertTrue(tc, 5 == Premier_liste(liste)->valeur);
  CuAssertTrue(tc, NULL == Premier_liste(liste)->suivant);

  // Test 2:
  // insértion de plusieurs valeurs
  int nbr = 10;
  Liste *liste2 = Creer_liste();
  int i;
  for (i = 0; i < nbr; ++i) Inserer_liste(liste2, 2 * i, 0);

  // test des valeurs
  ElementListe *courant = Premier_liste(liste2);
  for (i = 0; i < nbr; ++i, courant = courant->suivant)
    CuAssertIntEquals(tc, 2 * (nbr - i - 1), courant->valeur);
  CuAssertTrue(tc, NULL == courant);

  // Test 3:
    Liste *liste3 = Creer_liste();
    for(i = 0; i < 10; ++i) Inserer_liste(liste3, i, Taille_liste(liste3));
    CuAssertIntEquals(tc, 10, Taille_liste(liste3));
}

void Test_Supprimer_Liste(CuTest *tc)
{
//  Liste *liste = Creer_liste();
//  int i;
//  for(i = 0; i < 10; ++i) Inserer_liste(liste, i, Taille_liste(liste));

//  Supprimer_liste(liste, 0);
//  CuAssertIntEquals(tc, 9, Taille_liste(liste));
}

void Test_Taille_Liste(CuTest *tc)
{
  Liste *liste = Creer_liste();
  CuAssertIntEquals(tc, Taille_liste(liste), 0);

  // TODO : test after insertion & free liste
}

void Test_Premier_liste(CuTest *tc)
{
  Liste *liste = Creer_liste();
  int i;
  for (i = 0; i < 10; ++i) Inserer_liste(liste, i, Taille_liste(liste));

  CuAssertIntEquals(tc, 0, Premier_liste(liste)->valeur);
  CuAssertIntEquals(tc, 1, Premier_liste(liste)->suivant->valeur);
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

void Detruire_liste(Liste *liste)
{
  //
}
