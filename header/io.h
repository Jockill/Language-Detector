#ifndef __IO_H
#define __IO_H

#define DETEC_TRIE 0
#define DETEC_DAWG 1

#include <time.h>

/*!
  \brief clear l'écran.
*/
void clear();

/*!
  \brief Attend que l'utilisateur appuyes sur 'entrée' pour continuer le programme
*/
void pause();

/*!
  \brief Affiche avec quelle structure se fera la détection
  \param [in] int arbre Entier représentant l'abre à utiliser.
  \note DETEC_TRIE = 0, DETEC_DAWG = 1
  \seealso menu
*/
void print_detection(int arbre);

/*!
  \brief Affiche le logo du programme
*/
void print_header();

/*!
  \brief Affiche l'aide
*/
void print_help();

/*!
  \brief Affiche la langue détectée ainsi que le pourcentage de confiance.
  \param [in] float cptr_fr Compte de mots en francais
  \param [in] float cptr_eng Compte de mots en anglais
  \param [in] float cptr_germ Compte de mots en allemand
*/
void print_langue(float cptr_fr, float cptr_eng, float cptr_germ);

/*!
  \brief Affiche le prompt de sortie du programme
  \seealso menu
*/
void print_quit();

/*!
  \brief Affiche le prompt pour commencer la détection
  \seealso menu
*/
void print_start();

/*!
  \brief Affiche si le temps sera renseigné ou pas a la fin de la détection
  \param [in] int temps Booléen valant 1 pour oui, 0 pour non
  \seealso menu
*/
void print_temps(int temps);

/*!
  \brief Affiche le temps total mis par les différentes étapes de la détection.
  \param [in] clock_t init Temps en ticks d'horloge de l'initialisation de la \
  structure
  \param [in] clock_t init Temps en ticks d'horloge de la détection (=lecture)
  \param [in] clock_t init Temps en ticks d'horloge de la suppression de la \
  structure
*/
void print_listeTemps(clock_t init, clock_t detec, clock_t del);

/*!
  \function menu
  \brief Affiche le menu principal 
*/
void menu();

#endif
