#ifndef ARBRE_H
#define ARBRE_H

typedef struct Arbre
{
  int val;
  struct Arbre *gauche, *droit;
} Arbre;


Arbre* arbre_creer(int val);

void arbre_detruire(Arbre **arbre);

void arbre_afficher(Arbre *arbre, int indent);

int Longueur_arbre(Arbre *arbre, int longeur);

void Prefixe_arbre(Arbre *arbre);

void Infixe_arbre(Arbre *arbre);

void Postfixe_arbre(Arbre *arbre);

void Inserer_arbre_ordnnee(Arbre **arbre, int val);

void Supprimer_arbre_ordonnee(Arbre **arbre, int val);

int arbre_egaux(Arbre *arbre1, Arbre *arbre2);

#endif // ARBRE_H
