/*!
 \file dawg.h
 \brief Header contenant les fonctions relatives au DAWG.
 \author JOCHYMSKI Hugo
 \date Octobre/2020
*/
#ifndef __DAWG_H
#define __DAWG_H


#include "hashmap.h"
#include <stdbool.h>
#include <time.h>


#define N 26 // Taille + 1
#define MAX_TAILLE 26 // Taille + 1
#define MAX_SIZE 2047

/******************************************************************************/
/************************************STRUCT************************************/
/******************************************************************************/

/*!
 \struct Sommet
 \brief Structure représentatant un sommet du DAWG.
*/
typedef struct Sommet {
	int label; /*!< Label unique du sommet courant*/
	struct Sommet *tab[N]; /*!< Arêtes sortantes du sommet. */
	bool mot_valide; /*!< Mot présent dans le dictionnaire ? */
   	size_t id;
   	bool fin;
} Sommet;

/*!
 \struct Arete
 \brief Arete reliant deux sommets du DAWG
*/
typedef struct Arete {
	char label; /*!< Label de l'arete */
	struct Sommet* sommet_gauche; /*!< Pointeur vers le sommet gauche. */ // SRC
	struct Sommet* sommet_droit; /*!< Pointeur vers le sommet droit. */	// DST
} Arete;

/*!
 \struct dawg
 \brief Représente le dawg
*/
typedef struct dawg {
	Sommet *racine;
	struct hashmap_s hashmap;
	struct stack *pile;
	size_t id_suivant;
	char *dernier_sommet;
} dawg;
/******************************************************************************/
/******************************************************************************/

dawg *initilisation_dawg(void);

size_t plusGrandPrefixeCommun(char* mot1, char* mot2);

char *confection_cle(Sommet *sommet);

void minimisation(dawg *dawg, size_t taille);

void sommet_insertion(dawg *dawg, char *mot);

bool recherche_mot_dawg(dawg *dawg, char *mot);

int suppression_hasmap(void *const hashmap, struct hashmap_element_s *const element);

void suppression_dawg(dawg *dawg);

dawg *construct_dawg(const char *pathname);

float dawg_test_mot_fr(dawg *racine, char *mot, int last);

float dawg_test_mot_eng(dawg *racine, char *mot, int last);

float dawg_test_mot_germ(dawg *racine, char *mot, int last);

void detec_dawg(char phrase[MAX_SIZE+1], int temps);












// /*!
//    \brief Minimise par mutation un DAWG jusqu'à la profondeur 'n'.
//    \param [in] struct dawg_sommet racine Racine du DAWG.
//    \param [in] size_t p Profondeur jusqu'à laquelle minimiser.
//    \return NONE
// */
// void dawg_minimiser(struct dawg_sommet racine, size_t p);

// /*!
//    \brief Ajoute des noeuds au DAWG en fonction du mot passé en argument.
//    \param [in] dawg_sommet* depart Point de départ de l'ajout.
//    \param [in] char* mot Mot à insérer.
//    \param [in] size_t indexDebut Index du mot à partir duquel commencer à ajouter.
//    \return NONE
// */
// void dawg_ajouter(struct dawg_sommet* depart, char* mot, size_t indexDebut);

// /*!
// \brief Insere par mutation un mot dans le DAWG.
// \param [in] struct dawg_sommet sommet racine du DAWG.
// \param [in] char* motPrecedent Mot précédant 'mot'.
// \param [in] char* mot Mot à inserer.
// \return NONE
// */
// void dawg_inserer_mot(struct dawg_sommet racine, char* motPrecedent, char* mot);

// /*!
//    \brief Genere un DAWG avec un dictionnaire
//    \param [in] char* pathToDic Chemin d'acces au dictionnaire à utiliser.
//    \return Un DAWG rempli avec le dictionnaire.
// */
// struct dawg_sommet creation(char* pathToDic);

#endif
