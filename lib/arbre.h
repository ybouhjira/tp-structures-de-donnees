#ifndef ARBRE_H
#define ARBRE_H

typedef struct Arbre
{
  int val;
  struct Arbre *gauche, *droit;
} Arbre;


/*
 * Entrées:
 *   int val : La valeur du noeud
 * Sortie :
 *   Un noeud d'un arbre
 * Description :
 *   Alloue de la mémoire pour un noeud et lui affecte la valeur val.
 */
Arbre* arbre_creer(int val);

/*
 * Entrées :
 *  Arbre **arbre : Un arbre
 * Description :
 *  Supprime l'arbre de la mémoire.
 */
void arbre_detruire(Arbre **arbre);

/*
 * Entées :
 *  Arbre *arbre : Un arbre
 *  int indent : espace avant chaque ligne (appelez la fonction en
 *    donnant 0 pour ce paramètre)
 * Description :
 *    Affiche l'arbre
 */
void arbre_afficher(Arbre *arbre, int indent);

/*
 * Entées :
 *  Arbre *arbre : Un arbre
 *  int longueur : longueur (donnez toujours 0 comme paramètre)
 * Description :
 *    Calcule La longueur maximale des branche de l'arbre
 */
int arbre_longueur(Arbre *arbre, int longeur);

/*
 * Entées :
 *  Arbre *arbre : Un arbre
 * Description :
 *    Affichage prefixé de l'arbre
 */
void arbre_affichage_prefixe(Arbre *arbre);

/*
 * Entées :
 *  Arbre *arbre : Un arbre
 * Description :
 *    Affichage infixé
 */
void arbre_affichage_infixe(Arbre *arbre);

/*
 * Entées :
 *  Arbre *arbre : Un arbre
 * Description :
 *    Affichage postfixés
 */
void arbre_affichage_postfixe(Arbre *arbre);

/*
 * Entées :
 *  Arbre *arbre : Un arbre ordonné horizontalement
 *  int val : La valeur à insérer
 * Description :
 *    Insére la valeur dans l'arbre
 */
void arbre_insertion_ordonnee(Arbre **arbre, int val);

/*
 * Entées :
 *  Arbre *arbre : Un arbre ordonné horizontalement
 *  int val : La valeur à insérer
 * Description :
 *    Supprime la valeur de l'arbre
 */
void arbre_supprimer_arbre_ordonnee(Arbre **arbre, int val);

/*
 * Entées :
 *  Arbre *arbre1 : Un arbre
 *  Arbre *arbre1 : Un arbre
 * Sortie :
 *  retourne 1 si arbre1 == arbre2, sinon retourne 0
 * Description :
 *    Comapre les 2 arbres récursivement
 */
int arbre_egaux(Arbre *arbre1, Arbre *arbre2);

/*
 * Entées :
 *  Arbre *arbre1 : Un arbre non vide
 * Sortie :
 *  La valeur minimale de l'arbre
 */
int arbre_min(Arbre *arb);

/*
 * Entées :
 *  Arbre *arbre1 : Un arbre non vide
 * Sortie :
 *  La valeur maxiamale de l'arbre
 */
int arbre_max(Arbre *arb);

#endif // ARBRE_H
