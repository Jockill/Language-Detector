/*!
 \file arbre.h
 \brief Header possèdant les fonctions nécessaire pour le "trie".
 \author WERNERT Thomas
 \date Novembre/2020
*/

#ifndef __ARBRE_H
#define __ARBRE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "utils.h"
#include "../src/utils.c" // Bizarre de devoir ajouter ceci ...
//#include "hashmap.h"


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
	bool feuille; // Mot dico 
} Noeud; 

/*!
 \struct Noeud *arbre
 \brief Représente racine de l'arbre
*/
typedef struct Noeud *Tas; 
//typedef struct Noeud *Arbre; 


/******************************************************************************/
/******************************************************************************/


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



#endif