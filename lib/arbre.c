#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "arbre.h"

Arbre* Creer_Arbre(int val)
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

void Detruire_arbre(Arbre *arbre)
{
  if(arbre->gauche) Detruire_arbre(arbre->gauche);
  if(arbre->droit) Detruire_arbre(arbre->droit);
  free(arbre);
}

void Afficher_arbre(Arbre *arbre, int indent)
{
  assert(arbre);
  int i;
  for(i = 0; i < indent; ++i) printf(" ");

  printf(" --> %d\n", arbre->val);

  int ajout = 4;
  if(arbre->gauche) Afficher_arbre(arbre->gauche, indent + ajout);
  else if(arbre->droit)
    {
      for(i = 0; i < indent + ajout; ++i) printf(" ");
      printf(" --> NULL\n");
    }
  if(arbre->droit) Afficher_arbre(arbre->droit, indent + ajout);
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
    *arbre = Creer_Arbre(val);
  else
    {
      if(val > (*arbre)->val)  Inserer_arbre_ordnnee(&(*arbre)->droit, val);
      else Inserer_arbre_ordnnee(&(*arbre)->gauche, val);
    }
}
