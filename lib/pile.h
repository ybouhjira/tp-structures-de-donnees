#ifndef PILE_H
#define PILE_H

#include "liste.h"

typedef Liste Pile;

// Empiler dans une pile
#define pile_empiler liste_ajout_debut

/* Entrées :
 *   pile : Une pile
 * Sortie :
 *   la valeur de l'élément dépilé
 * Description :
 *   supprime l'élément en tête de la pile et retourne ça valeur.
 */
int pile_depiler(Pile **pile);

/* Entrées :
 *   pile : Une pile
 * Description :
 *   Afficher le contenu de la pile
 */
void pile_afficher(Pile **pile);

/*
 * Entrees:
 *  pile : Une pile
 * Sortie:
 *  Copie de la pile
 */
Pile *pile_copier(Pile **pile);

#endif // PILE_H
