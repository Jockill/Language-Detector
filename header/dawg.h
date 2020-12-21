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
	struct Sommet *tab[N]; 	/*!< Arêtes sortantes du sommet. */
	bool mot_valide; 	/*!< Bool pur savoir si le mot actuel est dans le dictionnaire. */
   size_t id;		/*!< Représente l'id du sommet actuel. */
   bool fin;		/*!< Bool pour savoit si sommet est final. */
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
	Sommet *racine;			/*!< Pointeur vers la racine du dawg. */
	struct hashmap_s hashmap;	/*!< Hasmap associée au dawg actuel. */
	struct stack *pile;		/*!< Pile associé au dawg actuel. */
	size_t id_suivant; 		/*!< Id suivant. */
	char *dernier_sommet; 		/*!< String représentant le dernier mot ajouté. */
} dawg;
/******************************************************************************/
/******************************************************************************/

/*!
   \brief Initialisation du dawg.
   \return Un dawg
*/
dawg *initilisation_dawg(void);


/*!
   \brief Calcul le plus grand préfixe commun entre deux strings
   \param [in] pointeur.
   \param [in] char Pointeur.
   \return size_t.
*/
size_t plusGrandPrefixeCommun(char* mot1, char* mot2);

/*!
   \brief Créer une clé à partir d'un sommet.
   \param [in] Sommet Pointeur.
   \return Une string.
*/
char *confection_cle(Sommet *sommet);

/*!
   \brief Minimasation jusqu'a une profondeur taille.
   \param [in] dawg Pointeur vers un dawg.
   \param [in] size_t Taille qui représente la profondeur.
   \return None.
*/
void minimisation(dawg *dawg, size_t taille);

/*!
   \brief Insérer un mot dans le dawg.
   \param [in] dawg Pointeur vers un dawg.
   \param [in] char Pointeur.
   \return None.
*/
void sommet_insertion(dawg *dawg, char *mot);

/*!
   \brief Rechercher la présence d'un mot dans le dawg.
   \param [in] dawg Pointeur vers un dawg.
   \param [in] char Pointeur.
   \return bool.
*/
bool recherche_mot_dawg(dawg *dawg, char *mot);

/*!
   \brief Libération de la hasmap associé à un dawg.
   \param [in] void Hashmap.
   \param [in] struct hasmap_element_s element.
   \return int.
*/
int suppression_hasmap(void *const hashmap, struct hashmap_element_s *const element);

/*!
   \brief Libération de l'esapace mémoire allouer à un dawg.
   \param [in] dawg Pointeur vers un dawg.
   \return int.
*/
void suppression_dawg(dawg *dawg);

/*!
   \brief Création d'un dawg avec un dictionnaire.
   \param [in] dawg Pointeur vers un dawg.
   \return int.
*/
dawg *construct_dawg(const char *pathname);

/*!
   \brief Test si <mot> est en francais
   \param [in] dawg* racine Racine du DAWG
   \param [in] char* mot Mot à tester
   \param [in] int last Langue(s) du dernier mot testé
   \return 1 si <mot> est en <langue> et que le dernier aussi, \
   0.5 si <mot> est en <langue> mais que le dernier non, \
   0 si <mot> n'est pas en <langue>
*/
float dawg_test_mot_fr(dawg* racine, char *mot, int last);

/*!
   \brief Test si <mot> est en anglais
   \param [in] dawg* racine Racine du DAWG
   \param [in] char* mot Mot à tester
   \param [in] int last Langue(s) du dernier mot testé
   \return 1 si <mot> est en <langue> et que le dernier aussi, \
   0.5 si <mot> est en <langue> mais que le dernier non, \
   0 si <mot> n'est pas en <langue>
*/
float dawg_test_mot_eng(dawg* racine, char *mot, int last);

/*!
   \brief Test si <mot> est en allemand
   \param [in] dawg* racine Racine du DAWG
   \param [in] char* mot Mot à tester
   \param [in] int last Langue(s) du dernier mot testé
   \return 1 si <mot> est en <langue> et que le dernier aussi, \
   0.5 si <mot> est en <langue> mais que le dernier non, \
   0 si <mot> n'est pas en <langue>
*/
float dawg_test_mot_germ(dawg* racine, char *mot, int last);

/*!
   \brief Lis une phrase puis détermine sa langue
   \param [in] dawg* racine_fr Racine du trie en francais
   \param [in] dawg* racine_eng Racine du trie en anglais
   \param [in] dawg* racine_germ Racine du trie en allemand
   \param [in] char phrase[MAX_SIZE+1] Phrase à détecter
   \return NONE
*/
void dawg_lecture(dawg *racine_fr, dawg *racine_eng, dawg *racine_germ, char phrase[MAX_SIZE+1]);

/*!
   \brief Cree un DAWG, test la langue de <phrase> puis supprime le DAWG.
   \param [in] char phrase[MAX_SIZE+1] Phrase à détecter.
   \param [in] int temps Booléen déterminant l'affichage du temps (1) ou non (0)
   \return NONE
*/
void detec_dawg(char phrase[MAX_SIZE+1], int temps);


#endif
