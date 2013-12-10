#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

int compare_int(const void *elem1, const void *elem2)
{
  int *e1 = (int*) elem1;
  int *e2 = (int*) elem2;
  return *e1 - *e2;
}

void test_liste_pos(CuTest *tc)
{
  Liste *liste = liste_creer();
  int i;
  for(i = 0; i < 19; ++i)
    liste_inserer(liste, &i, liste_taille(liste));

  int val = 3;
  CuAssertIntEquals(tc, 3, liste_recherche(&val, liste, compare_int));
  val = 44;
  CuAssertIntEquals(tc, -1, liste_recherche(&val, liste, compare_int));
  liste_detruire(&liste);
}

void test_liste_acceder(CuTest *tc)
{
  Liste *liste = liste_creer();
  int i;
  for(i = 0; i < 10; ++i)
      liste_inserer(liste, &i, liste_taille(liste));

  CuAssertIntEquals(tc, 0, *(int*) liste_acceder(liste, 0)->val);

  liste_detruire(&liste);
}

void test_liste_intersection(CuTest *tc)
{
  Liste *liste1 = liste_creer(), *liste2 = liste_creer();

  int val = 1;
  liste_inserer(liste1, &val, 0);
  val = 2;
  liste_inserer(liste1, &val, 0);
  val = 3;
  liste_inserer(liste1, &val, 0);
  val = 4;
  liste_inserer(liste1, &val, 0);

  val = 3;
  liste_inserer(liste2, &val, 0);
  val = 4;
  liste_inserer(liste2, &val, 0);
  val = 5;
  liste_inserer(liste2, &val, 0);
  val = 6;
  liste_inserer(liste2, &val, 0);


  Liste *intersect = liste_intersection(liste1, liste2, compare_int);

  CuAssertIntEquals(tc, liste_taille(intersect), 2);
  val = 3;
  CuAssertTrue(tc, -1 != liste_recherche(&val, intersect, compare_int));
  val = 4;
  CuAssertTrue(tc, -1 != liste_recherche(&val, intersect, compare_int));
  liste_detruire(&liste1);
  liste_detruire(&liste2);
}

void test_liste_echange(CuTest *tc)
{
  Liste *liste = liste_creer();
  int i;
  for(i = 0; i < 10; ++i) liste_ajout_fin(liste, &i);
  liste_echange(liste, 4, 6);

  CuAssertIntEquals(tc, 6, *(int*)liste_acceder(liste, 4)->val);
  CuAssertIntEquals(tc, 4, *(int*)liste_acceder(liste, 6)->val);

  liste_echange(liste, 0, 9);
  CuAssertIntEquals(tc, 10, liste_taille(liste));
  CuAssertIntEquals(tc, 0, *(int*)liste_acceder(liste, 9)->val);
  CuAssertIntEquals(tc, 9, *(int*)liste_acceder(liste, 0)->val);

  liste_detruire(&liste);
}

void test_liste_tri_bulles(CuTest *tc)
{
  // Remplissage de liste avec des nombres aléatoires
  srand(time(NULL));
  Liste *liste = liste_creer();

  int i;
  for(i = 0; i < 10; ++i)
    {
      int val = rand() % 100;
      liste_ajout_fin(liste, &val);
    }

  liste_tri_bulles(liste, compare_int);
  CuAssertIntEquals(tc, 10, liste_taille(liste));

  // Test
  ElementListe *courant;
  for(courant = liste_premier(liste); courant->suivant;
      courant = courant->suivant)
    CuAssertTrue(tc, *(int*)courant->val <= *(int*)courant->suivant->val);

  liste_detruire(&liste);
}

CuSuite* Liste_get_suite()
{
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_liste_acceder);
  SUITE_ADD_TEST(suite, Test_Inserer_Liste);
  SUITE_ADD_TEST(suite, Test_Premier_liste);
  SUITE_ADD_TEST(suite, Test_Supprimer_Liste);
  SUITE_ADD_TEST(suite, Test_Taille_Liste);
  SUITE_ADD_TEST(suite, test_liste_pos);
  SUITE_ADD_TEST(suite, test_liste_intersection);
  SUITE_ADD_TEST(suite, test_liste_echange);
  SUITE_ADD_TEST(suite, test_liste_tri_bulles);
  return suite;
}


