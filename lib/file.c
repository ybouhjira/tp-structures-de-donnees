#include "file.h"
#include <stdio.h>
#include <assert.h>

void file_enfiler(File *file, int val)
{
  FileElem *nouveau = calloc(1, sizeof(FileElem));
  nouveau->val = val;


  if(!file->tete)
    {
      file->tete = file->queue = nouveau;
    }
  else
    {
      file->queue->suiv = nouveau;
      file->queue = file->queue->suiv;
    }
}

int file_defiler(File *file)
{
  assert(file->tete);
  assert(file->queue);

  int valeur = file->tete->val;


  if(file->tete == file->queue)
    {
      free(file->queue);
      file->tete = file->queue = NULL;
    }
  else
    {
      FileElem *suppr = file->tete;
      file->tete = file->tete->suiv;
      free(suppr);
    }

  return valeur;
}

void file_afficher(File *file)
{
  File copie = {NULL, NULL};

  printf("[");
  while(file->tete)
    {
      int valeur = file_defiler(file);
      printf("%d", valeur);
      if(file->queue) printf(", ");
      file_enfiler(&copie, valeur);
    }

  printf("]");

  *file = copie;
}

File file_copier(File *file)
{
  File copie = {NULL, NULL}, file2 = {NULL, NULL};

  while(file->tete)
    {
      int val = file_defiler(file);
      file_enfiler(&file2, val);
      file_enfiler(&copie, val);
    }

  *file = file2;
  return copie;
}

int file_taille(File *f)
{
  File f2 = {NULL, NULL};
  int taille = 0;

  while(f->queue)
    {
      file_enfiler(&f2, file_defiler(f));
      taille++;
    }

  *f = f2;
  return taille;
}
