#ifndef PILE_H
#define PILE_H

#include "liste.h"

typedef Liste Pile;

#define pile_empiler liste_ajout_debut

/** Entrées :
  *   pile : Une pile
  * Sorties :
  *   la valeur de l'élément dépilé
  * Description :
  *   supprime l'élément en tête de la pile
  */
int pile_depiler(Pile **pile);

/** Entrées :
  *   pile : Une pile
  * Description :
  *
  */
void pile_afficher(Pile **pile);

#endif // PILE_H
