#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct Liste
{
  int taille;
  ElementListe *premier;
};

Liste* liste_creer()
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

int liste_taille(Liste *liste)
{
  return liste->taille;
}

ElementListe* liste_premier(Liste *liste)
{
  return liste->premier;
}

void liste_inserer(Liste *liste, int val, int pos)
{
  // Conditions
  assert(pos >= 0);
  assert(pos <= liste->taille);

  // Nouvel élément pour la valeur
  ElementListe *element = calloc(1, sizeof(ElementListe));
  if(!element)
    {
      printf("Erreur d'allcation de mémoire\n");
      exit(1);
    }
  element->val = val;

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
      int i;
      for(i = 0; i < pos - 1; ++i) courant = courant->suivant;

      element->suivant = courant->suivant;
      courant->suivant = element;
    }

  // Incrémentation de la taille
  liste->taille++;
}

void liste_supprimer(Liste *liste, int pos)
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
      int i;
      ElementListe *courant = liste->premier;
      for (i = 0; i < pos - 1; ++i) courant = courant->suivant;

      elem = courant->suivant;
      courant->suivant = courant->suivant->suivant;
    }

  // Suppression de la mémoire allouée
  free(elem);

  // Décrementer la taille
  liste->taille--;
}

void liste_detruire(Liste **liste)
{
  while(liste_taille(*liste)) liste_supprimer(*liste, 0);
  free(*liste);
  liste = NULL;
}

int liste_recherche(int val, Liste *liste)
{
  ElementListe *courant = liste->premier;
  int pos;
  for(pos = 0; courant; ++pos, courant = courant->suivant)
    if(courant->val == val)
      return pos;
  return -1;
}

ElementListe* liste_acceder(Liste *liste, int pos)
{
  assert(pos >= 0);
  assert(pos < liste_taille(liste));

  ElementListe *courant = liste->premier;
  int i;
  for(i = 0; i < pos ; ++i) courant = courant->suivant;

  return courant;
}

Liste* liste_intersection(Liste *l1, Liste *l2)
{
  Liste *intersect = liste_creer();
  if(!l1 && !l2) return intersect;

  ElementListe *courant;
  for(courant = l1->premier; courant; courant = courant->suivant )
    {
      if(liste_recherche(courant->val, l2) >= 0)
        liste_inserer(intersect, courant->val, liste_taille(intersect));
    }

  return intersect;
}

void echange_valeurs(int *val1, int *val2)
{
  int sauvegarde = *val1;
  *val1 = *val2;
  *val2 = sauvegarde;
}

void liste_tri_bulles(Liste *liste)
{
  ElementListe *fin;

  while(fin != liste_premier(liste))
    {
      ElementListe *courant = liste_premier(liste);
      while(courant->suivant && courant->suivant != fin )
        {
          if(courant->val> courant->suivant->val)
            echange_valeurs(&(courant->val), &(courant->suivant->val));
          courant = courant->suivant;
        }
      fin = courant;
    }
}

void liste_echange(Liste *liste, int pos1, int pos2)
{
  assert(pos1 >= 0);
  assert(pos1 < liste_taille(liste));
  assert(pos2 >= 0);
  assert(pos2 < liste_taille(liste));

  ElementListe *elem1 = liste_acceder(liste, pos1);
  ElementListe *elem2 = liste_acceder(liste, pos2);

  int sauvegarde = elem1->val;
  elem1->val = elem2->val;
  elem2->val = sauvegarde;
}

void liste_ajout_debut(Liste *liste, int val)
{
  liste_inserer(liste, val, 0);
}

void liste_ajout_fin(Liste *liste, int val)
{
  liste_inserer(liste, val, liste_taille(liste));
}
