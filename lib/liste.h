#ifndef LISTE_H
#define LISTE_H

#include <stdlib.h>

/*
 * La liste chainéé
 */
typedef struct Liste Liste;

/*
 * Un élément de la liste
 */
typedef struct ElementListe
{
  void* val;
  struct ElementListe *suivant;
} ElementListe;

/* Sorties :
 *    Liste *liste : Une liste chainée
 * Description:
 *    Création et initialisation d'une liste chainée
 */
Liste* liste_creer();

/* Entrées :
 *    Liste *liste : Une liste chainée
 * Description:
 *    Supprime la mémoire allouée pour une liste chainée
 */
void liste_detruire(Liste **liste);

/* Entrées :
 *    Liste :Une liste chainée
 * Sorties :
 *    unsigned int taille : La taille de la liste
 * Description:
 *    Retourne la taille de la liste
 */
int liste_taille(Liste *liste);

/* Entrées :
 *    Liste *liste : Une liste chainée
 * Sorties :
 *    ElementListe *element : Le premier element de la liste
 * Description:
 *    Retourne le premier élément de la liste
 */
ElementListe* liste_premier(Liste *liste);


/* Entrées :
 *    Liste *liste : Une liste chainée
 *    int val : La valeur à inserer
 *    int pos : La position de l'insertion
 * Description:
 *    Inserer l'élément val à la position pos
 */
void liste_inserer(Liste *liste, void* val, int pos);

/* Entrées :
 *    Liste *liste : Une liste chainée
 *    unsigned int pos :
 * Description:
 *    Supprime l'élément à la position indiquée
 */
void liste_supprimer(Liste *liste, int pos);

/* Entrées :
 *    void *val : Valeur recherché
 *    Liste *liste : Une liste
 *    int cmp(void* elem1, void* elem2, size_t) : fonction de comparaison
 * doit retourner 0 si elem1 égale elem2, un nombre négatif ou négatif
 * respectivement si elem1 < elem2 ou elem1 > elem2.
 * Sorties :
 *    int pos : La premier position dans laquelle la valeur existe, ou -1
 *  si cette valeur n'a pas pu etre trouvé
 * Description:
 *    Retourne la position de la valeur val dans la liste
 */
int liste_recherche(void* val, Liste *liste,
                  int (*cmp)(const void*, const void*));

/* Entrées :
 *  Liste *liste : Une liste
 *  int pos : La position
 *  cmp : fonction de comparaison entre deux éléments de la liste
 * Sorties :
 *  ElementListe *element : L'élément à la position pos
 * Description:
 *    Retourne l'élément à la postion pos dans la liste
 */
ElementListe* liste_acceder(Liste *liste, int pos);

/* Entrées :
 *  Liste *l1 : première liste
 *  Liste *l2 : deuxième liste
 * Sorties :
 *  Liste* intersect : intersection des deux listes
 * Description:
 *    Retourne l'intersection de deux listes
 */
Liste *liste_intersection(Liste *l1, Liste *l2,
                          int cmp(const void *, const void *));

#endif // LISTE_H
