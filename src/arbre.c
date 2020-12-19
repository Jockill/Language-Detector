#include "../header/arbre.h"
#include "../header/utils.h"
#include "../header/io.h"

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
	// here insert the word in the trie or in the DAWG
	// To complete ...
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
size_t test_mot_fr(Arbre racine, char *mot, size_t cptr) {
	if(recherche_mot_arbre(racine, mot)) {
		cptr++;
	}
	return cptr;
}

// Fonction de test des mots en ENG ainsi obtenus et retourne un compteur
size_t test_mot_eng(Arbre racine, char *mot, size_t cptr) {
	if(recherche_mot_arbre(racine, mot)) {
		cptr++;
	}
	return cptr;
}

// Fonction de test des mots en GERM ainsi obtenus et retourne un compteur
size_t test_mot_germ(Arbre racine, char *mot, size_t cptr) {
	if(recherche_mot_arbre(racine, mot)) {
		cptr++;
	}
	return cptr;
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

void detec_trie(char phrase[MAX_SIZE])
{
	// Initilisation des compteurs pour déterminer la langue
	size_t cptr_fr = 0;
	size_t cptr_eng = 0;
	size_t cptr_germ = 0;

	// Initilisation des dicos dans le "tri"
	// #WARNING: construct_trie plutot ?
	Arbre racine_fr = construct_trie("../dict/french-wordlist.txt");
	Arbre racine_eng = construct_trie("../dict/english-wordlist.txt");
	Arbre racine_germ = construct_trie("../dict/german-wordlist.txt");

	char phrase[MAX_SIZE+1] = lecture(phrase);

	// Découpage de la phrase
	size_t len = strlen(phrase);
	char temp[] = " ";
	char *mot = strtok(phrase, temp);
	while(mot != NULL) {
		// Le truc à faire
		printf("%s\n", mot);
		cptr_fr = test_mot_fr(racine_fr, mot, cptr_fr);
		cptr_eng = test_mot_eng(racine_eng, mot, cptr_eng);
		cptr_germ = test_mot_germ(racine_germ, mot, cptr_germ);
		mot = strtok(NULL, temp);
	}
	printf("%d\n", cptr_fr);
	printf("%d\n", cptr_eng);
	printf("%d\n", cptr_germ);

	// Affichage de la langue
	print_langue(cptr_fr, cptr_eng, cptr_germ);

	// Libération de l'espace mémoire alloué
	suppression_arbre(racine_fr); // Dico fr
	suppression_arbre(racine_eng); // Dico eng
	suppression_arbre(racine_germ); // Dico germ
}
