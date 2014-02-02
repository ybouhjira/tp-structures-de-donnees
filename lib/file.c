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
