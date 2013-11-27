#ifndef ARBRE_H
#define ARBRE_H

typedef struct Arbre
{
  int val;
  struct Arbre *gauche, *droit;
} Arbre;


Arbre* Creer_Arbre(int val);

void Detruire_arbre(Arbre *arbre);

void Afficher_arbre(Arbre *arbre, int indent);

int Longueur_arbre(Arbre *arbre, int longeur);

void Prefixe_arbre(Arbre *arbre);

void Infixe_arbre(Arbre *arbre);

void Postfixe_arbre(Arbre *arbre);

void Inserer_arbre_ordnnee(Arbre **arbre, int val);

#endif // ARBRE_H
