/*!
 \file arbre.h
 \brief Header possèdant les fonctions nécessaire pour le "trie".
 \author WERNERT Thomas
 \date Novembre-Decembre/2020
*/

#ifndef __ARBRE_H
#define __ARBRE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "utils.h"
// #include "../src/utils.c" // Bizarre de devoir ajouter ceci ...
// #include "hashmap.h"


#define N 26 // Taille + 1 du tab de pointeurs de l'alphabet

/******************************************************************************/
/************************************STRUCT************************************/
/******************************************************************************/

/*!
 \struct Noeud
 \brief Représente un noeud de l'arbre
*/
typedef struct Noeud {
	struct Noeud *tab[N]; // Tableau des lettres a-z
	bool feuille; // Mot valide
} Noeud;

/*!
 \struct Noeud *arbre
 \brief Représente racine de l'arbre
*/
//typedef struct Noeud *Tas;
typedef struct Noeud *Arbre;


/******************************************************************************/
/******************************************************************************/

Arbre construct_trie(char* dict);

/*!
   \brief Permet l'initialisation d'un arbre.
   \return Arbre racine
*/
Arbre noeud_initialisation(void);


/*!
   \brief Permet l'insertion d'un noeud supplémentaire dans un arbre.
   \param [in] Noeud *racine Racine de l'arbre.
   \param [in] char *message Mot à insérer dans l'arbre.
   \return NONE
*/
void noeud_insertion(Noeud *racine, char *message);

// Test si <mot> est en francais et retourne un compteur
size_t test_mot_fr(Arbre racine, char *mot, size_t cptr);

// Test si <mot> est en anglais et retourne un compteur
size_t test_mot_eng(Arbre racine, char *mot, size_t cptr);

// Test si <mot> est en allemand et retourne un compteur
size_t test_mot_germ(Arbre racine, char *mot, size_t cptr);

/*!
   \brief Permet de connaître la présence d'un mot dans l'arbre.
   \param [in] Arbre racine Racine de l'arbre.
   \param [in] char *message Mot à rechercher.
   \return true ou false
*/
bool recherche_mot_arbre(Arbre racine, char *message);

/*!
   \brief Supprime l'arbre complétement.
   \param [in] Arbre racine Racine de l'arbre.
   \return NONE
*/
void suppression_arbre(Arbre racine);

//Cree un trie, test la langue de <phrase> puis supprime le trie.
void detec_trie(char phrase[MAX_SIZE]);

#endif
