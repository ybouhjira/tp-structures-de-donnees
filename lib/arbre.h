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

#endif // ARBRE_H
