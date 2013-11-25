#include "liste.h"
#include <stdlib.h>

struct Liste
{
  unsigned int taille;
  ElementListe *premier;
};


Liste* Creer_liste()
{
  // Allocation de la mémoire
  Liste *liste = malloc(sizeof(Liste));

  // Initialisation
  liste->taille = 0;
  liste->premier = NULL;

  return liste;
}
