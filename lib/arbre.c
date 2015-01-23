#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "arbre.h"

Arbre* arbre_creer(int val)
{
  // Allouer la mémoire
  Arbre *arbre = calloc(1, sizeof(Arbre));
  if(!arbre)
    {
      printf("Erreur d'allocation de mémoire\n");
      exit(1);
    }
  arbre->val = val;
  return arbre;
}

void arbre_detruire(Arbre **arbre)
{
  // Supprimer la mémoire allouer pour tout l'arbre
  if((*arbre)->g) arbre_detruire(&(*arbre)->g);
  if((*arbre)->d) arbre_detruire(&(*arbre)->d);
  free(*arbre);
  *arbre = NULL;
}

//void arbre_afficher(Arbre *arbre, int indent)
//{
//  assert(arbre);
//  int i;
//  for(i = 0; i < indent; ++i) printf(" ");

//  printf(" --> %d\n", arbre->val);

//  int ajout = 4;

//  // gauche
//  if(arbre->g)
//    {
//      arbre_afficher(arbre->g, indent + ajout);
//    }
//  else if(arbre->d)
//    {
//      for(i = 0; i < indent + ajout; ++i) printf(" ");
//      printf(" --> NULL\n");
//    }

//  // droit
//  if(arbre->d)
//    {
//      arbre_afficher(arbre->d, indent + ajout);
//    }
//  else if(arbre->g)
//    {
//      for(i = 0; i < indent + ajout; ++i) printf(" ");
//      printf(" --> NULL\n");
//    }
//}

int arbre_longueur(Arbre *arbre, int longeur)
{
  if(!arbre || (!arbre->d && !arbre->g)) //arbre vide ou pas de de fils
    {
      return longeur;
    }
  else
    {
      int lngGauche = arbre_longueur(arbre->g, longeur);
      int lngDroit = arbre_longueur(arbre->d, longeur);
      return (lngDroit > lngGauche ? lngDroit : lngGauche) + 1;
    }
}

void arbre_affichage_prefixe(Arbre *arbre)
{
  assert(arbre);
  printf("%d, ", arbre->val);
  if(arbre->g) arbre_affichage_prefixe(arbre->g);
  if(arbre->d) arbre_affichage_prefixe(arbre->d);
}

void arbre_affichage_infixe(Arbre *arbre)
{
  assert(arbre);

  if(!arbre->g && !arbre->d)
    printf("%d, ", arbre->val);
  else
    {
      if(arbre->g) arbre_affichage_infixe(arbre->g);
      printf("%d, ", arbre->val);
      if(arbre->d) arbre_affichage_infixe(arbre->d);
    }
}

void arbre_affichage_postfixe(Arbre *arbre)
{
  assert(arbre);

  if(arbre->g) arbre_affichage_postfixe(arbre->g);
  if(arbre->d) arbre_affichage_postfixe(arbre->d);
  printf("%d, ", arbre->val);
}

void arbre_insertion_ordonnee(Arbre **arbre, int val)
{
  if(!(*arbre))
    *arbre = arbre_creer(val);
  else
    {
      if(val >= (*arbre)->val)  arbre_insertion_ordonnee(&(*arbre)->d, val);
      else arbre_insertion_ordonnee(&(*arbre)->g, val);
    }
}

Arbre* arbre_fils_plus_a_droite(Arbre *arbre)
{
  if(!arbre->d) return arbre;
  else return arbre_fils_plus_a_droite(arbre->d);
}

void arbre_supprimer_arbre_ordonnee(Arbre **arb, int val)
{
  if(!(*arb)) return;

  if((*arb)->val == val) // trouvé
    {
      // Supprimer les autres occurences
      arbre_supprimer_arbre_ordonnee(&(*arb)->d, val);

      if(!(*arb)->d && !(*arb)->g) // 0 fils
        {
          free(*arb);
          *arb = NULL;
        }
      else if(((*arb)->d && !(*arb)->g) || ((*arb)->g && !(*arb)->d)) // 1 fils
        {
          Arbre *fs = (*arb)->d? (*arb)->d : (*arb)->g;
          Arbre *ancien_arb = *arb;
          *arb = fs;
          free(ancien_arb);
        }
    else
        {
          Arbre *ancien_arb = *arb;
          *arb = arbre_fils_plus_a_droite((*arb)->g);
          (*arb)->d = ancien_arb->d;
          free(ancien_arb);
        }
    }
  else
    {
      if(val >= (*arb)->val)
        arbre_supprimer_arbre_ordonnee(&(*arb)->d, val);
      if(val < (*arb)->val)
        arbre_supprimer_arbre_ordonnee(&(*arb)->g, val);
    }
}

int arbre_egaux(Arbre *arbre1, Arbre *arbre2)
{
  if(!arbre1 || !arbre2) return arbre1 == NULL && arbre2 == NULL;
  return arbre1->val == arbre2->val
      && arbre_egaux(arbre1->d, arbre2->d)
      && arbre_egaux(arbre1->g, arbre2->g);
}


#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a > b ? a : b

int arbre_min(Arbre *arbre)
{
  assert(arbre != NULL);

  if(!arbre->g && !arbre->d) // sans fils
    {
      return arbre->val;
    }
  else if(!arbre->d || !arbre->g) // 1 seul fils
    {
      int min = arbre->d ?
            arbre_min(arbre->d) : arbre_min(arbre->g);
      return MIN(arbre->val, min);
    }
  else // 2 fils
    {
      int minG = arbre_min(arbre->g);
      int minD = arbre_min(arbre->d);
      return MIN(MIN(minD, minG), arbre->val);
    }
}

int arbre_max(Arbre *arbre)
{
  assert(arbre != NULL);

  if(!arbre->g && !arbre->d) // sans fils
    {
      return arbre->val;
    }
  else if(!arbre->d || !arbre->g) // 1 seul fils
    {
      int max = arbre->d ?
            arbre_max(arbre->d) : arbre_max(arbre->g);
      return MAX(arbre->val, max);
    }
  else // 2 fils
    {
      int maxG = arbre_max(arbre->g);
      int maxD = arbre_max(arbre->d);
      return MAX(MAX(maxD, maxG), arbre->val);
    }
}

int arbre_contient(Arbre *arb, int val)
{
  if(!arb) return 0;

  if(arb->val == val) return 1;

  if(arb->g && arbre_contient(arb->g, val)) return 1;
  if(arb->d && arbre_contient(arb->d, val)) return 1;

  return 0;
}

void arbre_afficher_recursive(Arbre *arb, char *prefix, int isTail) {
  printf("%s%s %d\n", prefix, isTail ? "└──" : "├──", arb->val);

  if(arb->g)
    {
      char gPrefix[100] = {0};
      strcat(gPrefix, prefix);
      strcat(gPrefix, isTail ? "    " : "│  ");
      arbre_afficher_recursive(arb->g, gPrefix, 0);
    }

  if(arb->d)
    {
      char dPrefix[100] = {0};
      strcat(dPrefix, prefix);
      strcat(dPrefix, isTail ? "    " : "└──");
      arbre_afficher_recursive(arb->d, dPrefix, 1);
    }
}

void arbre_afficher(Arbre *arb) {
  arbre_afficher_recursive(arb, "", 1);
}

/**
    Fonction : est_feuille
    Entrées : arbre
    Sortie : 0 ou 1
    description : si c'est une feuille retourn 1 sinon 0
*/
int arbre_est_feuille(Arbre* arbre)
{
    return !arbre->d && !arbre->g;
}

int arbre_hauteur(Arbre* arbre)
{
    int hg,hd;
    if(!arbre) return 0; // retourne 0 si c'est arbre vide
    hg = arbre_hauteur(arbre->g); // calcul hauteur du sous arbre gauche
    hd = arbre_hauteur(arbre->d); // calcul hauteur de sous arbre droit
    return 1+(hg > hd? hg : hd); // retourne 1 + max des deux hauteurs
}

int arbre_supprime_fils_plus_droit(Arbre* racine)
{
    int elt;
    Arbre* curseur1=NULL,*curseur2=NULL; // déclaration des pointeurs de manipulations
    curseur1=racine->g; /* initialisation de pointeur sur le sous arbre gauche*/
    curseur2=curseur1->d; /* initialiation de pointeur sur le sous arbre droit
    direct du sous arbre gauche*/
    while(curseur2->d) // tant qu'on est pas arrivé au fils plus droit
    {
        curseur1=curseur2; // on avance vers l fils droit direct du fils droit courant
        curseur2=curseur2->d; //
    }
    elt=curseur2->val; // on sauvgarde la valeur pour la retourner plutard
    free(curseur2); // libérer l'espace mémoire
    curseur1->d=curseur2->g; /* faire pointer le fils droit du parent du fils vers
    le fils gauche du noeud supprimer*/
    return elt; // retourner l'element
}


int arbre_supprime_fils_plus_gauche(Arbre*racine)
{
    int elt; // valeur du fils plus gauche du fils droit
    Arbre* curseur1=NULL,*curseur2=NULL; // curseur pour positionnement
    curseur1=racine->d; // initialise par le sous arbre droit
    curseur2=curseur1->g;// initalisi par le sous arbre gauche
    while(curseur2->g) // tant que le sous arbre gauche n'es pas le plus gauche
    {
        curseur1=curseur2; // on descend vers le gauche en bas
        curseur2=curseur2->g;
    }
    elt=curseur2->val; // on garde la valeur
    free(curseur2); // libérer l'espace mémoire
    curseur1->g=curseur2->d; /*faire pointer le précédant du sous arbre gauche supprim
    vers le fils droit de celui ci*/
    return elt; // retourne a valeur
}


Arbre* arbre_rotate_l(Arbre* arbre)
{
    // si l'arbre est vide on retourne NULL
    if(!arbre) return (Arbre*)NULL;
    // si le sous arbre gauche est vide on sort
    if(!arbre->g) return arbre;
    // marque le sous arbre gauche
    Arbre* pencheGauche = arbre->g;
    // mettre le sous arbre droit de sous arbre gauche d'arbre comme sous arbre gauche
    arbre->g = arbre->g->d;
    // mettre le sous arbre droit de la penche gauche l'arbre a rotationéé
    pencheGauche->d=arbre;
    // l'arbre devient la racine de la penche gauche
    return pencheGauche;
}


Arbre* arbre_rotate_r(Arbre* arbre)
{
    // si l'arbre est vide on retourne NULL
    if(!arbre) return (Arbre*)NULL;
    // si l'arbre droit est vide on retourne NULL
    if(!arbre->d) return arbre;
    // marque le sous arbre droit
    Arbre* pencheDroite = arbre->d;
    // mettre le sous arbre gauche de sous arbre droit comme sous arbre droit
    arbre->d = arbre->d->g;
    // mettre le sous arbre arbre gauche de la penche droite l'arbre a rotationée
    pencheDroite->g = arbre;
    // l'arbre devient la racine de la penche droite
    return pencheDroite;
}


Arbre* arbre_equilibre(Arbre* arbre,int equ)
{
    // si l'arbre est vide on sort
    if(!arbre) return arbre;
    if(equ>1) // deséquilibre droit
    {
        // déséquilibre droit gauche
        if(arbre_hauteur(arbre->d->d) < arbre_hauteur(arbre->d->g))
            // rotation gauche de sous arbre droit
            arbre->d = arbre_rotate_l(arbre->d);
        // rotation droite
        arbre=arbre_rotate_r(arbre);
    }
    if(equ<-1) // deséquilibre gauche
    {
        //déséquilibre gauche droit
        if(arbre_hauteur(arbre->g->g) < arbre_hauteur(arbre->g->d))
            // rotation droite de sous arbre gauche
            arbre->g = arbre_rotate_r(arbre->g);
        // rotation gauche
        arbre=arbre_rotate_l(arbre);
    }
    // retour de l'arbre équilibré
    return arbre;
}



/**
    Fonction : insertion equilibre
    Entrées : arbre, elt a inserer
    Sortie : arbre equilibré
*/

Arbre* arbre_insert_equilibre(Arbre* arbre,int elt)
{
    int hd,hg,equ; // variable pour hauteur gauche et droite
    // si l'arbre est vide retourn une nouvelle arbre
    if(!arbre) return arbre_creer(elt);
    // si l element est plus petit que val
    if(elt<arbre->val)
    {
        // insertion dans le sous arbre gauche
        arbre->g=arbre_insert_equilibre(arbre->g,elt);
    }else // sinon l element est plus grand ou egale
    {
        // insertion dans element le sous arbre droit
        arbre->d=arbre_insert_equilibre(arbre->d,elt);
    }
    // calcul de la hauteur de sous arbre droit
    hd=arbre_hauteur(arbre->d);
    // calcul de la haute de sous arbre gauche
    hg=arbre_hauteur(arbre->g);
    // calcul de l'equilibre de l'arbre
    equ = hd - hg;
    // equilibrage
    return arbre_equilibre(arbre,equ);
}


/**
    Fonction : supprime_equilibre
    Entrées : racine et element a supprime
    Sortie : arbre equilibre
*/
Arbre* arbre_supprime_arbre_equilibre(Arbre* racine,int elt)
{
    int val_rtr;
    int hd,hg,equ;
    Arbre* curseur=NULL; //
    if(!racine) return (Arbre*)NULL;
    // s'il est la racine est NULL alors on renvoi NULL
    if(racine->val==elt)
        // si la valeur de la racine est égale à la valeur a supprimer
    {
        if(racine->g && racine->g->d) /* si le sous arbre gauche exist
            et a au moins un fils droit*/
        {
            val_rtr=arbre_supprime_fils_plus_droit(racine);
    // on supprime le fils le pls droit du fils gauche en recuperant sa valeur
            racine->val=val_rtr; /* on remplace la valeur du noeud courant par
             la valeur du fils le plus droit du fils gauche supprimé*/
            return (Arbre*)racine; // on retourne la racine
        }
        if(racine->d && racine->d->g) /* si le sous arbre droit exist
            et a au moins un fils gauche*/
        {
            val_rtr=arbre_supprime_fils_plus_gauche(racine); /* on supprime le fils le pls gauche du fils
        droit en recuperant sa valeur*/
            racine->val=val_rtr; /* on remplace la valeur
             du noeud courant par la valeur du fils le plus gauche supprimé */
            return (Arbre*)racine; // on retourne la racine
        }
        if(racine->d) // s'il admet un fils droit
        {
            curseur=racine; // on sauvgarde la racine courante
            racine=racine->d; // on décale du droit vers le haut
            free(curseur); // on supprime la racine
            return (Arbre*)racine; // on retourne la racine
        }
        if(racine->g) // s'il admet un fils gauche
        {
            curseur=racine; // on sauvgarde la racine courante
            racine=racine->g; // on décale du gauche vers le haut
            free(curseur); // on supprime l'espace mémire
            return (Arbre*)racine; // on retourne la racine
        }
        free(racine); // dans ce cas c'est une feuille alors on la supprime
        return (Arbre*)NULL; // on retourne NULL
    }else // sinon c'est pas le meme element
    {
        if(arbre_est_feuille(racine)) // si la racine est une feuille
            return racine; // on s'arrete et on retourne la racin

        if(racine->val> elt)
            racine->g=arbre_supprime_arbre_equilibre(racine->g,elt); // on passe au sous arbre gauche
        else
            racine->d=arbre_supprime_arbre_equilibre(racine->d,elt); // on passe au sous arbre droit
         //calcul de la arbre_hauteur de sous arbre droit
        hd=arbre_hauteur(racine->d);
         //calcul de la haute de sous arbre gauche
        hg=arbre_hauteur(racine->g);
         //calcul de l'arbre_equilibre de l'arbre
        equ = hd - hg;
        // equilibrage du parent de la racine
        racine = arbre_equilibre(racine,equ);
        return racine; // retourne la racine
    }
}

void arbre_afficher_recusrsive_equilibre(Arbre *arb, char *prefix, int isTail)
{
    if(!arb) return;
    printf("%s%s ", prefix, isTail ? "|__" : "|--");
    printf("%d\n", arbre_hauteur(arb->d)-arbre_hauteur(arb->g));
    if(arb->g)
    {
        char gPrefix[100] = {0};
        strcat(gPrefix, prefix);
        strcat(gPrefix, isTail ? "    " : "|  ");
        arbre_afficher_recusrsive_equilibre(arb->g, gPrefix, 0);
    }
    if(arb->d)
    {
      char dPrefix[100] = {0};
      strcat(dPrefix, prefix);
      strcat(dPrefix, isTail ? "    " : "|  ");
      arbre_afficher_recusrsive_equilibre(arb->d, dPrefix, 1);
    }
}

void arbre_afficher_equilibre(Arbre *arb)
{
    arbre_afficher_recusrsive_equilibre(arb, "", 1);
}
