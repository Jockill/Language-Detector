/*!
 \file dawg.h
 \brief Header contenant les fonctions relatives au DAWG.
 \author JOCHYMSKI Hugo
 \date Octobre/2020
*/
#ifndef __DAWG_H
#define __DAWG_H

#include <stdbool.h>

/******************************************************************************/
/************************************STRUCT************************************/
/******************************************************************************/

/*!
\struct dawg_arete
\brief Arete reliant deux sommets du DAWG
*/
struct dawg_arete
{
        int label; /*!< Label de l'arete */
        struct dawg_sommet* sommetGauche; /*!< Pointeur vers le sommet gauche. */
        struct dawg_sommet* sommetDroit; /*!< Pointeur vers le sommet droit. */
};

/*!
 \struct dawg_sommet
 \brief Structure représentatant un sommet du DAWG.
*/
struct dawg_sommet
{
        int label; /*!< Label unique du sommet */
        dawg_arete aretesSortantes[26]; /*!< Arêtes sortantes du sommet. */
        bool motValide; /*!< Mot présent dans le dictionnaire ? */
};

struct dawg_root
{
        Stack pile; //Attention Stack == struct stack*
        struct hashmap_s map;
        dawg_arete aretesSortantes[26];
};

/******************************************************************************/
/******************************************************************************/

/*!
   \brief Minimise par mutation un DAWG jusqu'à la profondeur 'n'.
   \param [in] struct dawg_sommet racine Racine du DAWG.
   \param [in] size_t p Profondeur jusqu'à laquelle minimiser.
   \return NONE
*/
void dawg_minimiser(struct dawg_sommet racine, size_t p)

/*!
   \brief Ajoute des noeuds au DAWG en fonction du mot passé en argument.
   \param [in] dawg_sommet* depart Point de départ de l'ajout.
   \param [in] char* mot Mot à insérer.
   \param [in] size_t indexDebut Index du mot à partir duquel commencer à ajouter.
   \return NONE
*/
void dawg_ajouter(dawg_sommet* depart, char* mot, size_t indexDebut)

/*!
\brief Insere par mutation un mot dans le DAWG.
\param [in] struct dawg_sommet sommet racine du DAWG.
\param [in] char* motPrecedent Mot précédant 'mot'.
\param [in] char* mot Mot à inserer.
\return NONE
*/
void dawg_inserer_mot(struct dawg_sommet racine, char* motPrecedent, char* mot);

/*!
   \brief Genere un DAWG avec un dictionnaire
   \param [in] char* pathToDic Chemin d'acces au dictionnaire à utiliser.
   \return Un DAWG rempli avec le dictionnaire.
*/
struct dawg_sommet creation(char* pathToDic);

#endif
