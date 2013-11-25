#ifndef LISTE_H
#define LISTE_H

/*
 * La liste chainéé
 */
typedef struct Liste Liste;

/*
 * Un élément de la liste
 */
typedef struct ElementListe
{
  int valeur;
  struct ElementListe *suivant;
} ElementListe;

/*
 * Nom de la fonction: Creer_liste
 * Sorties :
 *    Liste *liste : Une liste chainée
 * Description:
 *    Création et initialisation d'une liste chainée
 */
Liste* Creer_liste();

#endif // LISTE_H
