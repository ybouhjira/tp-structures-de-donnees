#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

Liste* liste_creer(int val)
{
  Liste *liste = calloc(1, sizeof(Liste));
  if(!liste)
    {
      printf("Erreur d'allocation de mémoire\n");
      exit(1);
    }
  liste->val = val;
  return liste;
}

int liste_taille(Liste *liste)
{
  Liste *courant = liste;
  int taille = 0;
  for(taille = 0; courant; courant = courant->suiv, ++taille);
  return taille;
}

void liste_inserer(Liste **liste, int val, int pos)
{
  // Conditions
  assert(pos >= 0);

  // Nouvel élément pour la valeur
  Liste *nouveau = liste_creer(val);

  // Insértion
  if(!pos) liste_ajout_debut(liste, val);
  else
    {
      Liste *courant = *liste;
      int i;
      for(i = 0; i < pos - 1 && courant->suiv; ++i)
        courant = courant->suiv;
      if(i != pos - 1) assert(0); // pos > taille
      nouveau->suiv = courant->suiv;
      courant->suiv = nouveau;
    }
}

void liste_supprimer(Liste **liste, int pos)
{
  assert(pos >= 0);
  assert(*liste);

  Liste *elem;
  if(!pos)
    {
      elem = *liste;
      *liste = (*liste)->suiv;
    }
  else
    {
      int i;
      Liste *courant = *liste;
      for (i = 0; i < pos - 1 && courant->suiv; ++i)
        courant = courant->suiv;
      if(i != pos - 1) assert(0); // pos > taille - 1
      elem = courant->suiv;
      courant->suiv = courant->suiv->suiv;
    }

  // Suppression de la mémoire allouée
  free(elem);
}

void liste_detruire(Liste **liste)
{
  while(*liste) liste_supprimer(liste, 0);
  free(*liste);
  liste = NULL;
}

int liste_recherche(int val, Liste *liste)
{
  Liste *courant = liste;
  int pos;
  for(pos = 0; courant; ++pos, courant = courant->suiv)
    if(courant->val == val)
      return pos;
  return -1;
}

Liste* liste_acceder(Liste *liste, int pos)
{
  assert(pos >= 0);
  assert(pos < liste_taille(liste));

  Liste *courant = liste;
  int i;
  for(i = 0; i < pos ; ++i) courant = courant->suiv;

  return courant;
}

Liste* liste_intersection(Liste *l1, Liste *l2)
{
  if(!l1 && !l2) return NULL;
  Liste *intersect = NULL;

  Liste *courant;
  for(courant = l1; courant; courant = courant->suiv )
    {
      if(liste_recherche(courant->val, l2) >= 0)
        liste_ajout_fin(&intersect, courant->val);
    }

  return intersect;
}

void echange_valeurs(int *val1, int *val2)
{
  int sauvegarde = *val1;
  *val1 = *val2;
  *val2 = sauvegarde;
}

void liste_echange(Liste *liste, int pos1, int pos2)
{
  assert(pos1 >= 0);
  assert(pos1 < liste_taille(liste));
  assert(pos2 >= 0);
  assert(pos2 < liste_taille(liste));

  Liste *elem1 = liste_acceder(liste, pos1);
  Liste *elem2 = liste_acceder(liste, pos2);

  int sauvegarde = elem1->val;
  elem1->val = elem2->val;
  elem2->val = sauvegarde;
}

void liste_ajout_debut(Liste **liste, int val)
{
  Liste *nouveau = liste_creer(val);
  if(*liste)
    {
      Liste *tete = *liste;
      nouveau->suiv = tete;
    }
  *liste = nouveau;
}

void liste_ajout_fin(Liste **liste, int val)
{
  Liste *courant = *liste;
  Liste *nouveau = liste_creer(val);
  if(!(*liste)) *liste = nouveau;
  else
    {
      for(; courant->suiv; courant = courant->suiv);
      courant->suiv = nouveau;
    }
}

void liste_afficher(Liste *liste)
{
  Liste *courant = liste;
  printf("[");
  while (courant)
    {
      printf("%d",courant->val);
      courant = courant->suiv;
      if(courant) printf(", ");
      else printf("]");
    }
  printf("\n");
}

void liste_tri_bulles(Liste *liste)
{
  // Le dernier élément à tester dans une itération
  Liste *fin = NULL;

  // Si on fait pas d'échange dans une itération la liste est trié
  int echange = 0;

  while(fin != liste)
    {
      Liste *courant = liste;
      while(courant->suiv != fin)
        {
          if(courant->val > courant->suiv->val)
            {
              echange_valeurs(&(courant->val), &(courant->suiv->val));
              echange = 1;
            }
          courant = courant->suiv;
        }
      liste_afficher(liste);
      if(!echange) return;
      fin = courant;
    }
}

void liste_insertion_ordonnee(Liste** liste,  int val)
{
  Liste *courant = *liste, *nouveau = liste_creer(val);

  // Tete de liste vide ou supérieur à val
  if (!(*liste) || ((*liste)->val >= val))
    {
      nouveau->suiv = *liste;
      *liste = nouveau;
    }
  else
    {
      // Chercher l'élement avant la pos d'insertion
      while (courant->suiv && (courant->suiv->val < nouveau->val))
        courant = courant->suiv;

      nouveau->suiv = courant->suiv;
      courant->suiv = nouveau;
    }
}

void liste_tri_insertion(Liste **liste)
{
  // Vide ou contient 1 élément
  if(!(*liste) || !(*liste)->suiv) return;

  // Tete

  // Reste de la liste
  Liste *courant = *liste;
  while(courant->suiv)
    {
      if(courant->val > courant->suiv->val)
        {
          Liste *supprimer = courant->suiv;
          courant->suiv = courant->suiv->suiv;
          liste_insertion_ordonnee(liste, supprimer->val);
          liste_afficher(*liste);
          free(supprimer);
          continue;
        }
      liste_afficher(*liste);
      courant = courant->suiv;
    }
}
