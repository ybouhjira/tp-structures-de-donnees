#include <stdio.h>
#include <stdlib.h>
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
  int i;
  for(i = 0; i < indent; ++i) printf(" ");

  printf("%d\n", arbre->val);

  if(arbre->gauche) Afficher_arbre(arbre->gauche, indent + 3);
  if(arbre->droit) Afficher_arbre(arbre->droit, indent + 3);
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
