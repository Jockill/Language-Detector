#include "../header/dawg.h"
#include "../header/utils.h"
#include "../header/stack.h"
#include "../header/hashmap.h"

#include <stdbool.h>
#include <time.h>

#define LASTFR 100
#define LASTEN 10
#define LASTDE 1
#define LANG_FR 1
#define LANG_EN 2
#define LANG_DE 3
#define N 26
#define TAILLE 256

dawg *initilisation_dawg(void) {
	// Init nouveau dawg
	dawg *nouveau = (dawg*)malloc(sizeof(dawg));
	if (nouveau == NULL) {
		perror("Malloc Dawg");
		exit(EXIT_FAILURE);
	}
	nouveau -> id_suivant = 0;
	nouveau -> dernier_sommet = NULL;

	// Init racine
	nouveau -> racine = (Sommet*)malloc(sizeof(Sommet));
	if(nouveau -> racine == NULL) {
		perror("Malloc racine");
		exit(EXIT_FAILURE);
	}
	nouveau -> racine -> id = nouveau -> id_suivant++;
	nouveau -> racine -> mot_valide = false;
	memset(nouveau -> racine -> tab, 0, sizeof nouveau -> racine -> tab);

	// Init hashmap
	if(hashmap_create(1024, &(nouveau -> hashmap)) != 0) {
		fprintf(stderr, "Hashmap problème\n");
		exit(EXIT_FAILURE);
	}

	// Init stack
	nouveau -> pile = new_stack(TAILLE);

	return nouveau;
}

char *confection_cle(Sommet *sommet) {
	char buf[TAILLE];
	char *cle = NULL;

	// Si sommet est une arêtes sortantes
	if(sommet -> fin == false) {
		size_t cptr = 0;
		while(cptr < N) {
			if(sommet -> tab[cptr] != NULL) {
				char label = cptr;

				Sommet *sommet_droit = sommet -> tab[cptr];

				int test_retour = snprintf(buf, sizeof buf, "%c-%ld  ", label, sommet_droit -> id);
				if(test_retour < 0 || test_retour >= N) {
					perror("snprintf");
					exit(EXIT_FAILURE);
				}

				if(cle != NULL) {
					char *temp = cle;
					cle = concat(temp, buf);
					free(temp);
				}

				else {
					cle = concat("", buf);
				}
			}
			cptr++;
		}
	}
	// Sinon
	else {
		cle = concat("", ".");
	}

	return cle;
}

void minimisation(dawg *dawg, size_t taille) {
	size_t index;

	while((size_t)stack_size(dawg -> pile) > taille) {
		// Dépilée la pile, nommé a la nouvelle arête
		Arete *a = stack_pop(dawg -> pile);

		// Vérifier si sommets sont équivalents
		char *cle1 = confection_cle(a -> sommet_droit);
		Sommet *sommet_trouve = hashmap_get(&dawg -> hashmap, cle1, strlen(cle1));
		free(cle1);

		// Si le cas
		if(sommet_trouve != NULL) {
			index = ascii_to_index(a -> label);
			a -> sommet_gauche -> tab[index] = sommet_trouve;
			free(a -> sommet_droit);
		}

		// Sinon mettre nouveau sommet dans la hashmap
		else {
			char *cle2 = confection_cle(a -> sommet_droit);
			hashmap_put(&dawg -> hashmap, cle2, strlen(cle2), a -> sommet_droit);
		}

		free(a);
	}
}

void sommet_insertion(dawg *dawg, char *mot) {

	// Etape 1 : Préfixe commun
	size_t taille_prefixe;
	if(dawg -> dernier_sommet == NULL) {
		taille_prefixe = 0;
	}
	else {
		taille_prefixe = plusGrandPrefixeCommun(dawg -> dernier_sommet, mot);
	}

	// Etape 2 : Minimisation
	minimisation(dawg, taille_prefixe);

	// Etape 3 : Ajout du suffixe non commun
	char *suffixe_non_commun = &mot[taille_prefixe];
	Sommet *sommet_gauche;

	// Ajout du mot à la pile
	if(is_stack_empty(dawg -> pile) == true) {
		sommet_gauche = dawg -> racine;
	}
	else {
		Arete *temp = ((Arete*)(stack_peek(dawg -> pile)));
		sommet_gauche = temp -> sommet_droit;
	}

	for(char *lettre = suffixe_non_commun; *lettre != '\0'; lettre++) {
		sommet_gauche -> fin = false;

		Sommet *sommet_droit = (Sommet*)malloc(sizeof(Sommet));
		if(sommet_droit == NULL) {
			perror("Sommet droit malloc");
			exit(EXIT_FAILURE);
		}

		memset(sommet_droit -> tab, 0, sizeof sommet_droit -> tab);
		sommet_droit -> mot_valide = false;
		sommet_droit -> id = dawg -> id_suivant++;
		sommet_droit -> fin = false;

		size_t index;
		Arete *nouvelle_arete = (Arete*)malloc(sizeof(Arete));
		if(nouvelle_arete == NULL) {
			perror("Nouvelle arête Malloc ");
			exit(EXIT_FAILURE);
		}

		nouvelle_arete -> label = *lettre;
		nouvelle_arete -> sommet_gauche = sommet_gauche;
		nouvelle_arete -> sommet_droit = sommet_droit;
		index = ascii_to_index(*lettre);
		sommet_gauche -> tab[index] = sommet_droit;
		stack_push(dawg -> pile, nouvelle_arete);

		sommet_gauche = sommet_droit;
	}

	// Etape 4 : Marquer le dernier sommet ajouté
	sommet_gauche -> fin = true;
	sommet_gauche -> mot_valide = true;
	if(dawg -> dernier_sommet != NULL) {
		free(dawg -> dernier_sommet);
	}
	// Puis nous l'ajoutons à la struct
	dawg -> dernier_sommet = concat(mot, "");
}

bool recherche_mot_dawg(dawg *dawg, char *mot) {
	Sommet *sommet;
	size_t index;
	bool result = false;
	sommet = dawg -> racine;

	while(*mot) {
		index = ascii_to_index(*mot);
		Sommet *prochain_sommet = sommet -> tab[index];
		if (prochain_sommet == NULL) {
			return result;
		}
		sommet = prochain_sommet;
		mot++;
	}

	if(sommet -> mot_valide) {
		result = true;
		return result;
	}

	result = sommet -> mot_valide;
	return result;
}

int suppression_hasmap(void *const hashmap, struct hashmap_element_s *const element) {
	(void)hashmap;
	free((char*)element -> key);
	free((Sommet*)element -> data);
	return EXIT_SUCCESS;
}

void suppression_dawg(dawg *dawg) {
	hashmap_iterate_pairs(&(dawg -> hashmap), suppression_hasmap, NULL);
	hashmap_destroy(&(dawg -> hashmap));
	suppression_pile(dawg -> pile);
	free(dawg -> racine);
	free(dawg -> dernier_sommet);
	free(dawg);
}

dawg *construct_dawg(const char *pathname) {
	char buf[TAILLE];
	dawg *nouveau_dawg = initilisation_dawg();
	FILE *fd = fopen(pathname, "r");

	while(fgets(buf, sizeof buf, fd) != NULL) {
		parse_word(buf);
		sommet_insertion(nouveau_dawg, buf);
	}

	minimisation(nouveau_dawg, 0);
	fclose(fd);

	return nouveau_dawg;
}


float dawg_test_mot_fr(dawg* racine, char *mot, int last)
{
	if (recherche_mot_dawg(racine, mot) && last%1000 >= LASTFR)
		return 1;
	else if (recherche_mot_dawg(racine, mot))
		return 0.5;
	else
		return 0;
}

float dawg_test_mot_eng(dawg* racine, char *mot, int last)
{
	if (recherche_mot_dawg(racine, mot) && last%100 >= LASTEN)
		return 1;
	else if (recherche_mot_dawg(racine, mot))
		return 0.5;
	else
		return 0;
}

float dawg_test_mot_germ(dawg* racine, char *mot, int last)
{
	if (recherche_mot_dawg(racine, mot) && last%10 >= LASTDE)
		return 1;
	else if (recherche_mot_dawg(racine, mot))
		return 0.5;
	else
		return 0;
}

void dawg_lecture(dawg *racine_fr, dawg *racine_eng, dawg *racine_germ, char phrase[MAX_SIZE+1])
{
	// Initilisation des compteurs pour déterminer la langue
	float cptr_fr = 0;
	float cptr_eng = 0;
	float cptr_germ = 0;
	float tmp = 0;
	int last = 0;
	int current = 0;

	// Découpage de la phrase
	char temp[] = " ";
	char *mot = strtok(phrase, temp);
	while(mot != NULL) {
		tmp = 0;
		current = 0;
		tmp = dawg_test_mot_fr(racine_fr, mot, last);
		if (tmp > 0)
		{
			cptr_fr += tmp;
			last += LASTFR;
		}
		tmp = dawg_test_mot_eng(racine_eng, mot, last);
		if (tmp > 0)
		{
			cptr_eng += tmp;
			last += LASTEN;
		}
		tmp = dawg_test_mot_germ(racine_germ, mot, last);
		if (tmp > 0)
		{
			cptr_germ += tmp;
			last += LASTDE;
		}
		mot = strtok(NULL, temp);
		last = current;
	}

	// Affichage de la langue
	print_langue(cptr_fr, cptr_eng, cptr_germ);
}

void detec_dawg(char phrase[MAX_SIZE+1], int temps)
{

	clock_t tdInit, ttInit;
	clock_t tdLecture, ttLecture;
	clock_t tdDel, ttDel;

	if (temps == 1) tdInit = clock();
	// Initilisation des dicos dans les dawg
	dawg *racine_fr = construct_dawg("dict/french-wordlist.txt");
	dawg *racine_eng = construct_dawg("dict/english-wordlist.txt");
	dawg *racine_germ = construct_dawg("dict/german-wordlist.txt");
	if (temps == 1) ttInit = clock()-tdInit;


	if (temps == 1)	tdLecture = clock();
	dawg_lecture(racine_fr, racine_eng, racine_germ, phrase);
	if (temps == 1) ttLecture = clock()-tdLecture;


	if (temps == 1) tdDel = clock();
	// Libération de l'espace mémoire alloué
	suppression_dawg(racine_fr);
	suppression_dawg(racine_eng);
	suppression_dawg(racine_germ);
	if (temps == 1)
	{
		ttDel = clock() - tdDel;
		print_listeTemps(ttInit, ttLecture, ttDel);
	}
}
