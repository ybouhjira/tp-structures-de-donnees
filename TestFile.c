
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "CuTest/CuTest.h"

#include "lib/file.h"

void test_file_copier(CuTest *tc)
{
  File *file = NULL;

  // Copier une file vide doit retourner une pile vide
  CuAssertTrue(tc, file_copier(&file) == NULL);


  int i;
  for(i = 5; i < 50; i++)
    file_enfiler(&file, i);

  File *copie = file_copier(&file);

  while(file)
    {
      CuAssertTrue(tc, copie != NULL);

      CuAssertIntEquals(tc, file_defiler(&file), file_defiler(&copie));
    }
}

void test_file_enfiler(CuTest *tc)
{
  File *file = NULL;

  file_enfiler(&file, 1);
  file_enfiler(&file, 2);
  file_enfiler(&file, 3);

  CuAssertIntEquals(tc, 3, liste_taille(file));

  CuAssertIntEquals(tc, 1, file->val);
  CuAssertIntEquals(tc, 2, file->suiv->val);
  CuAssertIntEquals(tc, 3, file->suiv->suiv->val);

  CuAssertTrue(tc, NULL == file->suiv->suiv->suiv);
}

void test_file_defiler(CuTest *tc)
{
  File *file = NULL;

  int i;
  for(i = 0; i < 10; ++i) file_enfiler(&file, i);

  CuAssertIntEquals(tc, 10, liste_taille(file));

  for(i = 0; i <= 9; ++i)
    {
      int valeur = file_defiler(&file);
      CuAssertIntEquals(tc, 10 - i - 1, liste_taille(file));
      CuAssertIntEquals(tc, i, valeur);
    }

  CuAssertTrue(tc, file == NULL);
}

void test_file_afficher(CuTest *tc)
{
  File *file = NULL;
  int i;
  for(i = 0; i < 10; ++i) file_enfiler(&file, i);

  file_afficher(&file);

  CuAssertIntEquals(tc, 10, liste_taille(file));
}

CuSuite *File_get_suite()
{
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_file_enfiler);
  SUITE_ADD_TEST(suite, test_file_defiler);
  SUITE_ADD_TEST(suite, test_file_afficher);
  SUITE_ADD_TEST(suite, test_file_copier);
  return suite;
}
