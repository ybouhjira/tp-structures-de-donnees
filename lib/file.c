#include "file.h"
#include <stdio.h>

int file_defiler(File **file)
{
  int valeur = (*file)->val;
  liste_supprimer(file, 0);
  return valeur;
}

void file_afficher(File **file)
{
  File *copie = NULL;

  int i = 0;
  while(*file)
    {
      int valeur = file_defiler(file);
      printf("%d : %d \n", i++, valeur);
      file_enfiler(&copie, valeur);
    }

  while(copie) file_enfiler(file, file_defiler(&copie));
}

File* file_copier(File **file)
{
  File *copie = NULL, *file2 = NULL;

  while(*file)
    {
      int val = file_defiler(file);
      file_enfiler(&file2, val);
      file_enfiler(&copie, val);
    }

  *file = file2;
  return copie;
}
