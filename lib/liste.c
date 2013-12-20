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

void liste_afficher(Liste *liste, Liste *fin)
{
  Liste *courant = liste;
  printf("[");
  while (courant && courant != fin)
    {
      printf("%d",courant->val);
      courant = courant->suiv;
      if(courant && courant != fin) printf(", ");
    }
  printf("]");
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
      liste_afficher(liste, NULL);
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
          free(supprimer);
        }
      else  courant = courant->suiv;
      liste_afficher(*liste, NULL);
    }
}

Liste* liste_min(Liste* liste)
{
  if(!liste) return NULL;
  if(!liste->suiv) return liste;

  Liste *min = liste, *courant;
  for(courant = liste->suiv; courant; courant = courant->suiv)
    if(min->val > courant->val) min = courant;
  return min;
}

void liste_tri_selection(Liste **liste)
{
  Liste *courant = *liste, *min;
  for(courant = *liste; courant && courant->suiv; courant = courant->suiv)
    {
      min = liste_min(courant);
      if(courant->val > min->val)
        echange_valeurs(&courant->val, &min->val);
      liste_afficher(*liste, NULL);
    }
}

void liste_tri_rapide(Liste **liste, Liste *fin)
{
  // Liste vide ou contient 1 élément
  if(!(*liste) || !(*liste)->suiv) return;

  Liste *pivot = *liste, *courant = pivot,
      *inf = NULL; // liste des éléments inférieur

  while(courant->suiv != fin)
    {
      if(courant->suiv->val <= pivot->val)
        {
          Liste *suppr = courant->suiv;
          courant->suiv = courant->suiv->suiv;

          //Insértion avant tete
          if(!inf) inf = suppr;
          else
            {
              Liste *courantInf = inf;
              while(courantInf->suiv != *liste)
                courantInf = courantInf->suiv;
              courantInf->suiv = suppr;
            }
          suppr->suiv = *liste;
        }
      else courant = courant->suiv;
    }

  // affichage de la trace de l'algorithme
  liste_afficher(inf, *liste);
  printf(" %d ", (*liste)->val);
  liste_afficher((*liste)->suiv, fin);
  printf("\n");

  // Faire la meme chose pour la liste des éléments inf et supérieur
  if(inf && inf->suiv != *liste) liste_tri_rapide(&inf, *liste);
  if((*liste)->suiv && (*liste)->suiv->suiv != NULL)
    liste_tri_rapide(&(*liste)->suiv, NULL);

  // changement de la tete de la liste
  if(inf) *liste = inf;
}

int min(int a, int b)
{
  return a < b ? a : b;
}

//Arbre *liste_arbre_tournoi(Liste *liste)
//{
//  Arbre *tete = NULL; // Tete de l'arbre
//  Liste *itr = liste; // élement courant

//  // Parcourir la liste
//  while(itr)
//    {
//      // Construire un arbre contenant le minimum de itr
//      // et itr->suiv
//      int minVal = itr->suiv? min(itr->val, itr->suiv->val) : itr->val;
//      Arbre *arbMin = arbre_creer(minVal);

//      if(itr->suiv)
//        {
//          arbMin->gauche = arbre_creer(itr->val);
//          arbMin->droit = arbre_creer(itr->suiv->val);
//        }

//      // Lier avec arbMin precedent
//      if(!tete) tete = arbMin;
//      else
//        {
//          Arbre *parent = arbre_creer(min(arbMin->val, tete->val));
//          parent->gauche = tete;
//          tete = parent;
//          tete->droit = arbMin;
//        }

//      // avancer
//      if(itr->suiv) itr = itr->suiv->suiv;
//      else break;
//    }

//  return tete;
//}

/* Nom de la fonction: plasser
 * Entrees: Tableau d'entiers
 *          Deux entiers
 * Sorties: Null
 * Description:
 *
 *    Cette fonction accepte comme argument un tableau d'entiers et
 *  remplace les valeurs des cases tableau de rang n par le sup des
 *  valeurs des cases 2n et 2n+1 (si elles sont superieurs), tant que
 *  2n+1 ne dépasse pas la taille du tableau
 */
void plasser(Liste *liste, int indice, int taille)
{
    int k, j;
    k = indice;
    j = 2 * k;
    while(j <= taille)
    {
        Liste *jElem = liste_acceder(liste, j);
        if((j < taille) && (jElem->val < jElem->suiv->val)) ++j;

        Liste *kElem = liste_acceder(liste, k);
        jElem = liste_acceder(liste, j);
        if(kElem->val < jElem->val)
        {
            echange_valeurs(&kElem->val, &jElem->val);
            k = j;
            j = 2 * k;
        }
        else break;
    }
}

void liste_tri_tas(Liste *liste)
{
    int i, taille = liste_taille(liste) - 1;
    for(i = taille / 2; i >= 0; --i) plasser(liste, i, taille);
    for(i = taille; i >= 1; --i)
    {
        echange_valeurs(&liste_acceder(liste, i)->val, &liste->val);
        plasser(liste, 0, i - 1);
    }
}
