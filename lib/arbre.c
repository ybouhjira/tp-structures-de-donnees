#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "arbre.h"

Arbre* arbre_creer(int val)
{
  // Allouer la mémoire
  Arbre *arbre = calloc(1, sizeof(Arbre));
  if(!arbre)
    {
      printf("Erreur d'allocation de mémoire\n");
      exit(1);
    }
  arbre->val = val;
  return arbre;
}

void arbre_detruire(Arbre **arbre)
{
  // Supprimer la mémoire allouer pour tout l'arbre
  if((*arbre)->g) arbre_detruire(&(*arbre)->g);
  if((*arbre)->d) arbre_detruire(&(*arbre)->d);
  free(*arbre);
  *arbre = NULL;
}

void arbre_afficher(Arbre *arbre, int indent)
{
  assert(arbre);
  int i;
  for(i = 0; i < indent; ++i) printf(" ");

  printf(" --> %d\n", arbre->val);

  int ajout = 4;

  // gauche
  if(arbre->g)
    {
      arbre_afficher(arbre->g, indent + ajout);
    }
  else if(arbre->d)
    {
      for(i = 0; i < indent + ajout; ++i) printf(" ");
      printf(" --> NULL\n");
    }

  // droit
  if(arbre->d)
    {
      arbre_afficher(arbre->d, indent + ajout);
    }
  else if(arbre->g)
    {
      for(i = 0; i < indent + ajout; ++i) printf(" ");
      printf(" --> NULL\n");
    }
}

int arbre_longueur(Arbre *arbre, int longeur)
{
  if(!arbre || (!arbre->d && !arbre->g)) //arbre vide ou pas de de fils
    {
      return longeur;
    }
  else
    {
      int lngGauche = arbre_longueur(arbre->g, longeur);
      int lngDroit = arbre_longueur(arbre->d, longeur);
      return (lngDroit > lngGauche ? lngDroit : lngGauche) + 1;
    }
}

void arbre_affichage_prefixe(Arbre *arbre)
{
  assert(arbre);
  printf("%d, ", arbre->val);
  if(arbre->g) arbre_affichage_prefixe(arbre->g);
  if(arbre->d) arbre_affichage_prefixe(arbre->d);
}

void arbre_affichage_infixe(Arbre *arbre)
{
  assert(arbre);

  if(!arbre->g && !arbre->d)
    printf("%d, ", arbre->val);
  else
    {
      if(arbre->g) arbre_affichage_infixe(arbre->g);
      printf("%d, ", arbre->val);
      if(arbre->d) arbre_affichage_infixe(arbre->d);
    }
}

void arbre_affichage_postfixe(Arbre *arbre)
{
  assert(arbre);

  if(arbre->g) arbre_affichage_postfixe(arbre->g);
  if(arbre->d) arbre_affichage_postfixe(arbre->d);
  printf("%d, ", arbre->val);
}

void arbre_insertion_ordonnee(Arbre **arbre, int val)
{
  if(!(*arbre))
    *arbre = arbre_creer(val);
  else
    {
      if(val >= (*arbre)->val)  arbre_insertion_ordonnee(&(*arbre)->d, val);
      else arbre_insertion_ordonnee(&(*arbre)->g, val);
    }
}

Arbre* arbre_fils_plus_a_droite(Arbre *arbre)
{
  if(!arbre->d) return arbre;
  else return arbre_fils_plus_a_droite(arbre->d);
}

void arbre_supprimer_arbre_ordonnee(Arbre **arb, int val)
{
  if(!(*arb)) return;

  if((*arb)->val == val) // trouvé
    {
      // Supprimer les autres occurences
      arbre_supprimer_arbre_ordonnee(&(*arb)->d, val);

      if(!(*arb)->d && !(*arb)->g) // 0 fils
        {
          free(*arb);
          *arb = NULL;
        }
      else if(((*arb)->d && !(*arb)->g) || ((*arb)->g && !(*arb)->d)) // 1 fils
        {
          Arbre *fs = (*arb)->d? (*arb)->d : (*arb)->g;
          Arbre *ancien_arb = *arb;
          *arb = fs;
          free(ancien_arb);
        }
    else
        {
          Arbre *ancien_arb = *arb;
          *arb = arbre_fils_plus_a_droite((*arb)->g);
          (*arb)->d = ancien_arb->d;
          free(ancien_arb);
        }
    }
  else
    {
      if(val >= (*arb)->val)
        arbre_supprimer_arbre_ordonnee(&(*arb)->d, val);
      if(val < (*arb)->val)
        arbre_supprimer_arbre_ordonnee(&(*arb)->g, val);
    }
}

int arbre_egaux(Arbre *arbre1, Arbre *arbre2)
{
  if(!arbre1 || !arbre2) return arbre1 == NULL && arbre2 == NULL;
  return arbre1->val == arbre2->val
      && arbre_egaux(arbre1->d, arbre2->d)
      && arbre_egaux(arbre1->g, arbre2->g);
}


#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a > b ? a : b

int arbre_min(Arbre *arbre)
{
  assert(arbre != NULL);

  if(!arbre->g && !arbre->d) // sans fils
    {
      return arbre->val;
    }
  else if(!arbre->d || !arbre->g) // 1 seul fils
    {
      int min = arbre->d ?
            arbre_min(arbre->d) : arbre_min(arbre->g);
      return MIN(arbre->val, min);
    }
  else // 2 fils
    {
      int minG = arbre_min(arbre->g);
      int minD = arbre_min(arbre->d);
      return MIN(MIN(minD, minG), arbre->val);
    }
}

int arbre_max(Arbre *arbre)
{
  assert(arbre != NULL);

  if(!arbre->g && !arbre->d) // sans fils
    {
      return arbre->val;
    }
  else if(!arbre->d || !arbre->g) // 1 seul fils
    {
      int max = arbre->d ?
            arbre_max(arbre->d) : arbre_max(arbre->g);
      return MAX(arbre->val, max);
    }
  else // 2 fils
    {
      int maxG = arbre_max(arbre->g);
      int maxD = arbre_max(arbre->d);
      return MAX(MAX(maxD, maxG), arbre->val);
    }
}

int arbre_contient(Arbre *arb, int val)
{
  if(!arb) return 0;

  if(arb->val == val) return 1;

  if(arb->g && arbre_contient(arb->g, val)) return 1;
  if(arb->d && arbre_contient(arb->d, val)) return 1;

  return 0;
}
