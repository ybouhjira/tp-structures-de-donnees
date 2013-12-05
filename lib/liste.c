#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <printf.h>
#include <string.h>

struct Liste
{
  unsigned int taille;
  ElementListe *premier;
};

Liste* creer_liste()
{
  // Allocation de la mémoire
  Liste *liste = malloc(sizeof(Liste));
  if(!liste)
    {
      printf("Erreur d'allocation de mémoire\n");
      exit(1);
    }

  // Initialisation
  liste->taille = 0;
  liste->premier = NULL;

  return liste;
}

unsigned int taille_liste(Liste *liste)
{
  return liste->taille;
}

ElementListe* premier_liste(Liste *liste)
{
  return liste->premier;
}

void inserer_liste(Liste *liste, void *val, unsigned int pos)
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
  element->val = malloc(sizeof(*val));
  memcpy(element->val, val, sizeof(*val));

  // Insértion
  if(!pos)
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
      for(i = 0; i < pos - 1; ++i) courant = courant->suivant;

      element->suivant = courant->suivant;
      courant->suivant = element;
    }

  // Incrémentation de la taille
  liste->taille++;
}

void supprimer_liste(Liste *liste, unsigned int pos)
{
  assert(pos < liste->taille);

  ElementListe *elem;
  if(!pos)
    {
      elem = liste->premier;
      liste->premier = liste->premier->suivant;
    }
  else
    {
      unsigned int i;
      ElementListe *courant = liste->premier;
      for (i = 0; i < pos - 1; ++i) courant = courant->suivant;

      elem = courant->suivant;
      courant->suivant = courant->suivant->suivant;
    }

  // Suppression de la mémoire allouée
  free(elem->val);
  free(elem);

  // Décrementer la taille
  liste->taille--;
}

void detruire_liste(Liste **liste)
{
  while(taille_liste(*liste)) supprimer_liste(*liste, 0);
  free(*liste);
  liste = NULL;
}
