#ifndef ARBRE_H
#define ARBRE_H

typedef struct Arbre
{
  int val;
  struct Arbre *g, *d;
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
void arbre_afficher(Arbre *arbre);

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


int arbre_contient(Arbre *arb, int val);

/**
    Fonction : est_feuille
    Entrées : arbre
    Sortie : 0 ou 1
    description : si c'est une feuille retourn 1 sinon 0
*/
int arbre_est_feuille(Arbre* arbre);

/**
    Fonction : hauteur
    Entrées : arbre
    Sortie : entier
    Description : calcul la hauteur
*/
int arbre_hauteur(Arbre* arbre);


/**
    Fonction : supprime_fils_plus_droit
    Entrée : racine
    Sortie : valeur du noeud de fils le plus droit du fils gauche
*/
int arbre_supprime_fils_plus_droit(Arbre* racine);


/**
    Fonction : supprime le fils plus gauche du fils droit
    Entrées: racine
    Sortie : valeur de fils plus gauche du fils droit
*/

int arbre_supprime_fils_plus_gauche(Arbre*racine);



/**
    Fonction : rotation gauche
    Entrées : arbre
    Sortie : arbre rotationée
*/
Arbre* arbre_rotate_l(Arbre* arbre);

/**
    Fonction : rotation droite
    Entrées : arbre
    Sortie : arbre rotationée
    Description : effectue une rotation droite
*/

Arbre* arbre_rotate_r(Arbre* arbre);


/**
    Fonction : equilibre
    Entrées : arbre, valuer d'equilibre
    Sortie : arbre rotationée
    Description : equilibre l'arbre selon equ qui est soit -1 0 ou 1
*/

Arbre* arbre_equilibre(Arbre* arbre,int equ);


/**
    Fonction : insertion equilibre
    Entrées : arbre, elt a inserer
    Sortie : arbre equilibré
*/

Arbre* arbre_insert_equilibre(Arbre* arbre,int elt);



/**
    Fonction : supprime_equilibre
    Entrées : racine et element a supprime
    Sortie : arbre equilibre
*/
Arbre* arbre_supprime_equilibre(Arbre* racine,int elt);


void arbre_afficher_recusrsive_equilibre(Arbre *arb, char *prefix, int isTail);

void arbre_afficher_equilibre(Arbre *arb);

#endif // ARBRE_H
