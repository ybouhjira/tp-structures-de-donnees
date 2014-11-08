#include "pile.h"
#include <stdio.h>
#include <assert.h>

int pile_depiler(Pile **pile)
{
  assert(*pile);

  int valeur = (*pile)->val;
  liste_supprimer(pile, 0);
  return valeur;
}

void pile_afficher(Pile **pile)
{
  Pile *copie = NULL;
  while(*pile)
    pile_empiler(&copie, pile_depiler(pile));

  int i = 0;
  while(copie)
    {
      int val = pile_depiler(&copie);
      printf("%d : %d\n", i++, val);
      pile_empiler(pile, val);
    }
}


Pile* pile_copier(Pile **pile)
{
  Pile *copie = NULL, *pile2 = NULL;

  while(*pile)
    {
      int val = pile_depiler(pile);
      pile_empiler(&pile2, val);
      pile_empiler(&copie, val);
    }

  *pile = pile2;

  return copie;
}
