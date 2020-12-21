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

/*!
   \brief Initialise un trie en le remplissant par tous les mots de <dict>
   \param [in] char* dict Dictionnaire à utiliser.
   \return Un trie rempli.
*/
Arbre construct_trie(char* dict);

/*!
   \brief Permet l'initialisation d'un noeud pour un trie.
   \return Arbre racine
*/
Arbre noeud_initialisation(void);


/*!
   \brief Permet l'insertion d'un noeud supplémentaire dans un arbre.
   \param [in] racine Racine de l'arbre.
   \param [in] message Mot à insérer dans l'arbre.
   \return NONE
*/
void noeud_insertion(Noeud *racine, char *message);

/*!
   \brief Test si <mot> est en francais
   \param [in] dawg* racine Racine du trie
   \param [in] char* mot Mot à tester
   \param [in] int last Langue(s) du dernier mot testé
   \return 1 si <mot> est en <langue> et que le dernier aussi, \
   0.5 si <mot> est en <langue> mais que le dernier non, \
   0 si <mot> n'est pas en <langue>
*/
float trie_test_mot_fr(Arbre racine, char *mot, int last);

/*!
   \brief Test si <mot> est en anglais
   \param [in] Arbre racine Racine du trie
   \param [in] char* mot Mot à tester
   \param [in] int last Langue(s) du dernier mot testé
   \return 1 si <mot> est en <langue> et que le dernier aussi, \
   0.5 si <mot> est en <langue> mais que le dernier non, \
   0 si <mot> n'est pas en <langue>
*/
float trie_test_mot_eng(Arbre racine, char *mot, int last);

/*!
   \brief Test si <mot> est en allemand
   \param [in] Arbre racine Racine du trie
   \param [in] char* mot Mot à tester
   \param [in] int last Langue(s) du dernier mot testé
   \return 1 si <mot> est en <langue> et que le dernier aussi, \
   0.5 si <mot> est en <langue> mais que le dernier non, \
   0 si <mot> n'est pas en <langue>
*/
float trie_test_mot_germ(Arbre racine, char *mot, int last);


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

/*!
   \brief Lis une phrase puis détermine sa langue
   \param [in] Arbre racine_fr Racine du trie en francais
   \param [in] Arbre racine_eng Racine du trie en anglais
   \param [in] Arbre racine_germ Racine du trie en allemand
   \param [in] char phrase[MAX_SIZE+1] Phrase à détecter
   \return NONE
*/
void trie_lecture(Arbre racine_fr, Arbre racine_eng, Arbre racine_germ, char phrase[MAX_SIZE+1]);

/*!
   \brief Cree un trie, test la langue de <phrase> puis supprime le trie.
   \param [in] char phrase[MAX_SIZE+1] Phrase à détecter.
   \param [in] int temps Booléen déterminant l'affichage du temps (1) ou non (0)
   \return NONE
*/
void detec_trie(char phrase[MAX_SIZE+1], int temps);

#endif
