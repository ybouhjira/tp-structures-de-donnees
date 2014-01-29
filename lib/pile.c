#include "pile.h"

int pile_depiler(Pile **pile)
{
  int valeur = (*pile)->val;
  liste_supprimer(pile, 0);
  return valeur;
}
