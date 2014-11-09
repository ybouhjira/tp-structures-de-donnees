#ifndef FILE_H
#define FILE_H

#include "liste.h"

typedef Liste FileElem;

typedef struct File
{
  FileElem *tete, *queue;
}File;

/*
 * Entrées:
 *  file : Une file
 *  val : La valeur à enfiler
 * Description :
 *  Ajoute un element en tete de la file.
 */
void file_enfiler(File *file, int val);

/*
 * Entrées:
 *  f : Une file
 * Sortie :
 *  Le nombre d'élements contenu dans la file
 */
int file_taille(File *f);

/* Entrées :
 *    file : Une file
 * Sorties :
 *   La valeur de l'élément supprimé
 * Description :
 *   Supprimer un élément de la file
 */
int file_defiler(File *file);


/* Entrées :
 *   file : Une file
 * Description :
 *   Affiche le contenu de la file
 */
void file_afficher(File *file);

/*
 * Entrées :
 *  file : Une file
 * Sortie:
 *  Une copie de la file
 */
File file_copier(File *file);

#endif // FILE_H
