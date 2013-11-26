#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <printf.h>

struct Liste
{
  unsigned int taille;
  ElementListe *premier;
};


Liste* Creer_liste()
{
  // Allocation de la mémoire
  Liste *liste = malloc(sizeof(Liste));

  // Initialisation
  liste->taille = 0;
  liste->premier = NULL;

  return liste;
}

unsigned int Taille_liste(Liste *liste)
{
  return liste->taille;
}

ElementListe* Premier_liste(Liste *liste)
{
  return liste->premier;
}

void Inserer_liste(Liste *liste, int val, unsigned int pos)
{
  // Conditions
  assert(pos <= liste->taille);

  // Nouvel élément pour la valeur
  ElementListe *element = calloc(1, sizeof(ElementListe));
  if(!element)
    {
      printf("Erreur d'allcation de mémoire\n");
      exit(1);
    }
  element->valeur = val;

  // Insértion
  if(pos == 0)
    {
      if(liste->premier)
        {
          ElementListe *ancienPremier = liste->premier;
          liste->premier = element;
          liste->premier->suivant = ancienPremier;
        }
      else
        liste->premier = element;
    }
  else
    {
      ElementListe *courant = liste->premier;
      unsigned int i;
      for(i = 0; i < pos; ++i) courant = courant->suivant;

      element->suivant = courant->suivant;
      courant->suivant = element;
    }

  // Incrémentation de la taille
  liste->taille++;
}
