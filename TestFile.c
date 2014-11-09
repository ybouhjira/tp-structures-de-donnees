
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "CuTest/CuTest.h"

#include "lib/file.h"

void test_file_taille(CuTest *tc)
{
  File file = {NULL, NULL};

  CuAssertIntEquals(tc, 0, file_taille(&file));

  file_enfiler(&file, 1);
  file_enfiler(&file, 2);
  file_enfiler(&file, 3);
  file_enfiler(&file, 4);

  CuAssertIntEquals(tc, 4, file_taille(&file));
}

void test_file_copier(CuTest *tc)
{
  File file = {NULL, NULL};

  // Copier une file vide doit retourner une pile vide
  CuAssertTrue(tc, file_copier(&file).tete == NULL);

  int i;
  for(i = 5; i < 50; i++)
    file_enfiler(&file, i);

  File copie = file_copier(&file);

  while(file.tete)
    {
      CuAssertTrue(tc, copie.tete != NULL);

      CuAssertIntEquals(tc, file_defiler(&file), file_defiler(&copie));
    }
}

void test_file_enfiler(CuTest *tc)
{
  File file = {NULL, NULL};

  file_enfiler(&file, 1);
  file_enfiler(&file, 2);
  file_enfiler(&file, 3);

  CuAssertIntEquals(tc, 3, file_taille(&file));

  CuAssertIntEquals(tc, 1, file.tete->val);
  CuAssertIntEquals(tc, 2, file.tete->suiv->val);
  CuAssertIntEquals(tc, 3, file.tete->suiv->suiv->val);

  CuAssertTrue(tc, NULL == file.tete->suiv->suiv->suiv);
}

void test_file_defiler(CuTest *tc)
{
  File file = {NULL, NULL};

  // Remplire la file
  int i;
  for(i = 0; i < 10; ++i) file_enfiler(&file, i);

  // tester la taille
  CuAssertIntEquals(tc, 10, file_taille(&file));

  for(i = 0; i <= 9; ++i)
    {
      int valeur = file_defiler(&file);
      CuAssertIntEquals(tc, 10 - i - 1, file_taille(&file));
      CuAssertIntEquals(tc, i, valeur);
    }

  CuAssertTrue(tc, file.tete == NULL);
  CuAssertTrue(tc, file.queue == NULL);
}

CuSuite *File_get_suite()
{
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_file_enfiler);
  SUITE_ADD_TEST(suite, test_file_defiler);
  SUITE_ADD_TEST(suite, test_file_copier);
  return suite;
}
