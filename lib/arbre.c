#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "arbre.h"

Arbre* arbre_creer(int val)
{
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
  if((*arbre)->gauche) arbre_detruire(&(*arbre)->gauche);
  if((*arbre)->droit) arbre_detruire(&(*arbre)->droit);
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
  if(arbre->gauche) arbre_afficher(arbre->gauche, indent + ajout);
  else if(arbre->droit)
    {
      for(i = 0; i < indent + ajout; ++i) printf(" ");
      printf(" --> NULL\n");
    }
  if(arbre->droit) arbre_afficher(arbre->droit, indent + ajout);
  else if(arbre->gauche)
    {
      for(i = 0; i < indent + ajout; ++i) printf(" ");
      printf(" --> NULL\n");
    }
}

int Longueur_arbre(Arbre *arbre, int longeur)
{
  if(!arbre || (!arbre->droit && !arbre->gauche))
    return longeur;
  else
    {
      int lngGauche = Longueur_arbre(arbre->gauche, longeur);
      int lngDroit = Longueur_arbre(arbre->droit, longeur);
      return (lngDroit > lngGauche ? lngDroit : lngGauche) + 1;
    }
}

void Prefixe_arbre(Arbre *arbre)
{
  assert(arbre);
  printf("%d, ", arbre->val);
  if(arbre->gauche) Prefixe_arbre(arbre->gauche);
  if(arbre->droit) Prefixe_arbre(arbre->droit);
}

void Infixe_arbre(Arbre *arbre)
{
  assert(arbre);

  if(!arbre->gauche && !arbre->droit)
    printf("%d, ", arbre->val);
  else
    {
      if(arbre->gauche) Infixe_arbre(arbre->gauche);
      printf("%d, ", arbre->val);
      if(arbre->droit) Infixe_arbre(arbre->droit);
    }
}

void Postfixe_arbre(Arbre *arbre)
{
  assert(arbre);

  if(arbre->gauche) Postfixe_arbre(arbre->gauche);
  if(arbre->droit) Postfixe_arbre(arbre->droit);
  printf("%d, ", arbre->val);
}

void Inserer_arbre_ordnnee(Arbre **arbre, int val)
{
  if(!(*arbre))
    *arbre = arbre_creer(val);
  else
    {
      if(val >= (*arbre)->val)  Inserer_arbre_ordnnee(&(*arbre)->droit, val);
      else Inserer_arbre_ordnnee(&(*arbre)->gauche, val);
    }
}

Arbre* Fils_plus_a_droite(Arbre *arbre)
{
  if(!arbre->droit) return arbre;
  else return Fils_plus_a_droite(arbre->droit);
}

void Supprimer_arbre_ordonnee(Arbre **arbre, int val)
{
  if(!(*arbre)) return;

  if((*arbre)->val == val)
    {
      Supprimer_arbre_ordonnee(&(*arbre)->droit, val);
      if(!(*arbre)->droit && !(*arbre)->gauche)
        {
          free(*arbre);
          *arbre = NULL;
        }
      else if(((*arbre)->droit && !(*arbre)->gauche) ||
        ((*arbre)->gauche && !(*arbre)->droit))
        {
          Arbre *fs = (*arbre)->droit? (*arbre)->droit : (*arbre)->gauche;
          Arbre *ancien_arb = *arbre;
          *arbre = fs;
          free(ancien_arb);
        }
    else
        {
          Arbre *ancien_arb = *arbre;
          *arbre = Fils_plus_a_droite((*arbre)->gauche);
          (*arbre)->droit = ancien_arb->droit;
          free(ancien_arb);
        }
    }
  else
    {
      if(val >= (*arbre)->val)
        Supprimer_arbre_ordonnee(&(*arbre)->droit, val);
      if(val < (*arbre)->val)
        Supprimer_arbre_ordonnee(&(*arbre)->gauche, val);
    }
}

int arbre_egaux(Arbre *arbre1, Arbre *arbre2)
{
  if(!arbre1 || !arbre2) return arbre1 == NULL && arbre2 == NULL;
  return arbre1->val == arbre2->val
      && arbre_egaux(arbre1->droit, arbre2->droit)
      && arbre_egaux(arbre1->gauche, arbre2->gauche);
}
