#ifndef FILE_H
#define FILE_H

#include "liste.h"

typedef Liste File;

#define file_enfiler liste_ajout_fin

/** Entrées :
  *    file : Une file
  * Sorties :
  *   La valeur de l'élément supprimé
  * Description :
  *   Supprimer un élément de la file
  */
int file_defiler(File **file);


/** Entrées :
  *   file : Une file
  * Description :
  *   Affiche le contenu de la file
  */
void file_afficher(File **file);

#endif // FILE_H
