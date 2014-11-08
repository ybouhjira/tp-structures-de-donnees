#ifndef LISTE_H
#define LISTE_H

#include <stdlib.h>
#include "arbre.h"

/*
 * Un élément de la liste
 */
typedef struct Liste
{
  int val;
  struct Liste *suiv;
} Liste;


/*
 * Entrées:
 *  liste : La liste d'origine
 *  pos : La position
 * Coupe la liste liste à la position pos
 */
Liste* liste_couper(Liste **liste, int pos);

void liste_ajouter_suite(Liste **liste, char *suite);

/*
 * Entrées:
 *  liste : Une liste
 * Sortie :
 *  Copie de la liste
 */
Liste* liste_copier(Liste *liste);

/* Sorties :
 *    Liste *liste : Une liste chainée
 * Description:
 *    Création et initialisation d'une liste chainée
 */
Liste* liste_creer(int val);

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
 *    int val : La valeur à inserer
 *    int pos : La position de l'insertion
 * Description:
 *    Inserer l'élément val à la position pos
 */
void liste_inserer(Liste **liste, int val, int pos);

/* Entrées :
 *    Liste *liste : Une liste chainée
 *    int val : La valeur à inserer
 * Description:
 *    Inserer l'élément val au début de la liste
 */
void liste_inserer_debut(Liste **liste, int val);

/* Entrées :
 *    Liste *liste : Une liste chainée
 *    unsigned int pos :
 * Description:
 *    Supprime l'élément à la position indiquée
 */
void liste_supprimer(Liste **liste, int pos);

/* Entrées :
 *    void *val : Valeur recherché
 *    Liste *liste : Une liste
 * Sortie :
 *     La premier position dans laquelle la valeur existe, ou -1
 *  si cette valeur n'a pas pu etre trouvé
 * Description:
 *    Retourne la position de la valeur val dans la liste
 */
int liste_recherche(int val, Liste *liste, Liste **elem);

/* Entrées :
 *  Liste *liste : Une liste
 *  int pos : La position
 *  cmp : fonction de comparaison entre deux éléments de la liste
 * Sorties :
 *  ElementListe *element : L'élément à la position pos
 * Description:
 *    Retourne l'élément à la postion pos dans la liste
 */
Liste *liste_acceder(Liste *liste, int pos);

/* Entrées :
 *  Liste *l1 : première liste
 *  Liste *l2 : deuxième liste
 * Sortie :
 *  Liste* intersect : intersection des deux listes
 */
Liste *liste_intersection(Liste *l1, Liste *l2);

/* Entrées :
 *    liste : Une liste chainée
 *    trace : indiquez avec cette variable si vous voulez afficher la trace
 * de l'algorithme
 * Description:
 *    Fait le tri à bulle de la liste
 */
void liste_tri_bulles(Liste *liste, int trace);

/* Entrées :
 *    Liste *liste : Une liste chainée
 *    int pos1 : première position
 *    int pos2 : deuxième position
 * Description:
 *    Echange les éléments aux positions pos1 et pos2
 */
void liste_echange(Liste *liste, int pos1, int pos2);

/* Nom de la fonction: liste_ajout_fin
 * Entrees:
 *   Liste **liste : Liste d'entiers
 *   int val : Valeur à insérer
 * Description:
 *    Ajout la valeur à la fin de la liste
 */
void liste_ajout_fin(Liste **liste, int val);

/* Nom de la fonction: liste_ajout_fin
 * Entrees:
 *   Liste **liste : Liste d'entiers
 *   int val : La valeur à ajouter
 * Description:
 *    ajoute un élément au début de la liste
 */
void liste_ajout_debut(Liste **liste, int val);

/* Nom de la fonction: liste_insertion_ordonnee
 * Entrees:
 *   Liste **liste : Liste d'entiers
 *   int val : Valeur à insérer
 * Description:
 *    Insérer un élément à la bonne position dans une liste ordonné
 * (avant le premier nombre supérieur)
 */
void liste_insertion_ordonnee(Liste **liste, int val);

/* Nom de la fonction: liste_afficher
 * Entrees:
 *   Liste *liste : Liste d'entiers
 *   Liste *fin : Fin de la liste
 * Description:
 *    Afficher la liste sous le formate suivant :
 * [1, 2, 3, 4]
 */
void liste_afficher(Liste *liste, Liste *fin);

/* Nom de la fonction: liste_tri_insertion
 * Entrees:
 *   Liste *liste : Liste d'entiers
 * Description:
 *    Tri par insertion
 */
void liste_tri_insertion(Liste **liste, int trace);

/* Nom de la fonction: liste_min
 * Entrees:
 *    liste : Liste d'entiers
 *    trace : indiquez avec cette variable si vous voulez afficher la trace
 * de l'algorithme
 * Description:
 *    Retourne le minimum d'une liste
 */
Liste* liste_min(Liste* liste);

/* Nom de la fonction: liste_tri_selection
 * Entrees:
 *   liste : Liste d'entiers
 * Description:
 *    Tri par selection
 */
void liste_tri_selection(Liste **liste, int trace);

/* Nom de la fonction: liste_tri_rapide
 * Entrees:
 *   Liste *liste : Liste d'entiers
 *   Liste *fin : dernier élément de la liste
 *   trace : indiquez avec cette variable si vous voulez afficher la trace
 * de l'algorithme
 * Description:
 *    Tri rapide
 */
void liste_tri_rapide(Liste **liste, Liste *fin, int trace);

//Arbre *liste_arbre_tournoi(Liste *liste);

/* Nom de la fonction: Liste_acceder
 * Entrees:
 *   Liste *liste : Une liste d'entiers
 *   int pos : position de l'élément cible
 * Description:
 *    Retourne l'élément à la position pos
 */
Liste* liste_acceder(Liste *liste, int pos);

/* Nom de la fonction: tri_tas
 * Entrees:
 *   Liste *liste : Liste d'entiers
 *   trace : indiquez avec cette variable si vous voulez afficher la trace
 * de l'algorithme
 * Description:
 *    Tri par tas
 */
void liste_tri_tas(Liste *liste, int trace);

#endif // LISTE_H
