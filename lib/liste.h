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

/*
 * Nom de la fonction: Detruire_liste
 * Entrées :
 *    Liste *liste : Une liste chainée
 * Description:
 *    Supprime la mémoire allouée pour une liste chainée
 */
void Detruire_liste(Liste *liste);

/*
 * Nom de la fonction: Taille_liste
 * Entrées :
 *    Liste :Une liste chainée
 * Sorties :
 *    unsigned int taille : La taille de la liste
 * Description:
 *    Retourne la taille de la liste
 */
unsigned int Taille_liste(Liste *liste);

/*
 * Nom de la fonction: Premier_liste
 * Entrées :
 *    Liste *liste : Une liste chainée
 * Sorties :
 *    ElementListe *element : Le premier element de la liste
 * Description:
 *    Retourne le premier élément de la liste
 */
ElementListe *Premier_liste(Liste *liste);


/*
 * Nom de la fonction: Inserer_liste
 * Entrées :
 *    Liste *liste : Une liste chainée
 *    int val : La valeur à inserer
 *    unsigned int pos : La position de l'insertion
 * Description:
 *    Inserer l'élément val à la position pos
 */
void Inserer_liste(Liste *liste, int val, unsigned int pos);

/*
 * Nom de la fonction:
 * Entrées :
 *    Liste *liste : Une liste chainée
 *    unsigned int pos :
 * Description:
 *    Supprime l'élément à la position indiquée
 */
void Supprimer_liste(Liste *liste, unsigned int pos);

#endif // LISTE_H
