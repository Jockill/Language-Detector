#include "../header/arbre.h"
#include <string.h>

#define LASTFR 100
#define LASTEN 10
#define LASTDE 1

Arbre construct_trie(char *dict) {

	Arbre racine = noeud_initialisation();


	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	FILE *fp;


	// open file
	fp = fopen(dict, "r"); // read mode
	if (fp == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	// read file
	while ((read = getline(&line, &len, fp)) != -1) {

	// remove newline
	size_t length = strlen(line);
		if((length > 0) && (line[length-1] == '\n')) {
			line[length-1] ='\0';
		}
		noeud_insertion(racine, line);
	}

	fclose(fp);
	free(line);

	return racine;
}

Arbre noeud_initialisation(void) {
	Arbre nouveau_noeud = (Arbre)malloc(sizeof(Noeud));
	nouveau_noeud -> feuille = false;
	for(size_t i = 0; i < N; i++) {
		nouveau_noeud -> tab[i] = NULL;
	}
	return nouveau_noeud;
}

// Ajoute un noeud à l'arbre
// Ajoute le flag feuille(mot dico) à la fin
void noeud_insertion(Noeud *racine, char *message) {
	Arbre chemin = racine;

	size_t index;

	while(*message) {
		index = ascii_to_index(*message);
		// Création d'un nv noeud si le chemin n'existe pas
		if(chemin -> tab[index] == NULL) {
			chemin -> tab[index] = noeud_initialisation();
		}
		chemin = chemin -> tab[index];
		message++;
	}
	chemin -> feuille = true;
}

// Pr savoir si est mot du dico
// Retourne bool pour savoir si mot est ds arbre
bool recherche_mot_arbre(Arbre racine, char *message) {
	bool result = false;
	if(racine == NULL) {
		return result;
	}
	size_t index;
	Arbre chemin = racine;
	// Tant que nous sommes pas à la fin de la string
	while(*message) {

		// Pr aller au noeud suivant
		index = ascii_to_index(*message);
		chemin = chemin -> tab[index];

		// Test si le noeud suivant est existant
		if(chemin == NULL) {
			return result;
		}

		message++; // Enlève la premiere lettre à chauqe itération mais garde la fin
	}
	// Si le chemin noeud est une feuille et nous avons atteint
	// la fin du message nous retournons vrai
	result = chemin -> feuille;
	return result;
}

// Fonction de test des mots en FR ainsi obtenus et retourne un compteur
float trie_test_mot_fr(Arbre racine, char *mot, int last)
{
	if (recherche_mot_arbre(racine, mot) && last%1000 >= LASTFR)
		return 1;
	else if (recherche_mot_arbre(racine, mot))
		return 0.5;
	else
		return 0;
}

// Fonction de test des mots en ENG ainsi obtenus et retourne un compteur
float trie_test_mot_eng(Arbre racine, char *mot, int last)
{
	if (recherche_mot_arbre(racine, mot) && last%100 >= LASTEN)
		return 1;
	else if (recherche_mot_arbre(racine, mot))
		return 0.5;
	else
		return 0;
}

// Fonction de test des mots en GERM ainsi obtenus et retourne un compteur
float trie_test_mot_germ(Arbre racine, char *mot, int last)
{
	if (recherche_mot_arbre(racine, mot) && last%10 >= LASTDE)
		return 1;
	else if (recherche_mot_arbre(racine, mot))
		return 0.5;
	else
		return 0;
}

void suppression_arbre(Arbre racine) {
	for(size_t i = 0; i < N; i++) {
		if(racine -> tab[i] != NULL) {
			suppression_arbre(racine -> tab[i]);
		}
		else {
			continue;
		}
	}
	free(racine);
}

void detec_trie(char phrase[MAX_SIZE+1])
{
	// Initilisation des compteurs pour déterminer la langue
	float cptr_fr = 0;
	float cptr_eng = 0;
	float cptr_germ = 0;
	float tmp = 0;
	int last = 0;


	// Initilisation des dicos dans les "trie"
	Arbre racine_fr = construct_trie("./dict/french-wordlist.txt");
	Arbre racine_eng = construct_trie("./dict/english-wordlist.txt");
	Arbre racine_germ = construct_trie("./dict/german-wordlist.txt");


	// Découpage de la phrase
	char temp[] = " ";
	char *mot = strtok(phrase, temp);
	while(mot != NULL) {
		last = 0;
		tmp = 0;
		tmp = trie_test_mot_fr(racine_fr, mot, last);
		if (tmp > 0)
		{
			cptr_fr += tmp;
			last += LASTFR;
		}
		tmp = trie_test_mot_eng(racine_eng, mot, last);
		if (tmp > 0)
		{
			cptr_eng += tmp;
			last += LASTEN;
		}
		tmp = trie_test_mot_germ(racine_germ, mot, last);
		if (tmp > 0)
		{
			cptr_germ += tmp;
			last += LASTDE;
		}
		mot = strtok(NULL, temp);
	}
	// Affichage de la langue
	print_langue(cptr_fr, cptr_eng, cptr_germ);

	// Libération de l'espace mémoire alloué
	suppression_arbre(racine_fr); // Dico fr
	suppression_arbre(racine_eng); // Dico eng
	suppression_arbre(racine_germ); // Dico germ
}
