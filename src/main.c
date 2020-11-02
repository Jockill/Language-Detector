#include <stdio.h>
#include <string.h>

#include "../header/utils.h"
#include "../header/hashmap.h"
#include "../header/arbre.h"
#include "arbre.c"




/*
 * Copy this function template to construct either a DAWG or a trie 
 * based on the dictionary filename given
 * 
 * Don't forget to change the void return type of this function 
 */
Arbre construct(char *dict) {

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


/*
// Fonction de découpage d'une string qd espace
// Récu 
char decoupage_de_phrase(char *phrase) {
	size_t len = strlen(phrase); 
	char temp[] = " "; 
	char *mot = strtok(phrase, temp);  
	while(mot != NULL) {
		// Le truc à faire 
		mot = strtok(NULL, temp); 
	}

	/* Surement inutile 
	for(size_t i = 0; i < len; i++) {
	} 
	/
}
*/


// Fonction de test des mots en FR ainsi obtenus et retourne un compteur 
size_t test_mot_fr(Arbre racine, char *mot, size_t cptr) {
	if(recherche_mot_arbre(racine, mot)) {
		cptr++; 
	}
	return cptr; 
}

// Fonction de test des mots rn ENG ainsi obtenus et retourne un compteur 
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

// Focntion qui donne la langue 
void donne_langue(size_t cptr_fr, size_t cptr_eng, size_t cptr_germ) {
	if(cptr_fr > cptr_eng && cptr_fr > cptr_germ) {
		printf("La langue détectée est le français.\n"); 
	}
	else if(cptr_eng > cptr_fr && cptr_eng > cptr_germ) {
		printf("La langue détectée est l'anglais.\n"); 
	}
	else if(cptr_germ > cptr_fr && cptr_germ > cptr_eng) {
		printf("La langue détectée est l'allemand.\n"); 
	}
	// Tous le compteurs à zéro : langue inconnu
	else {
		printf("La langue détectée est INCONNU.\n");
	}
}

int main(int argc, char* argv[]) {
 
	if(argc != 2) {
		fprintf(stderr, "Usage: ./main <phrase à tester>"); 
		exit(EXIT_FAILURE); 
	}

	char *phrase; 
	phrase = argv[1]; 


	// Initilisation des compteurs pour déterminer la langue 
	size_t cptr_fr = 0; 
	size_t cptr_eng = 0; 
	size_t cptr_germ = 0; 




	// Tester si la phrase ne possède pas d'accents ou de symboles proscrits 




	// Initilisation des dicos dans le "tri"
	Arbre racine_fr = construct("../dict/french-wordlist.txt");
	Arbre racine_eng = construct("../dict/english-wordlist.txt");
	Arbre racine_germ = construct("../dict/german-wordlist.txt");	



	// Le fait en 1er juste et après double tout et affiche "null" à la fin 
	// Découpage de la phrase
	size_t len = strlen(phrase); 
	char temp[] = " "; 
	char *mot = strtok(phrase, temp);  
	while(mot != NULL) {
		// Le truc à faire 
		printf("'%s'\n", mot);
		cptr_fr = test_mot_fr(racine_fr, mot, cptr_fr); 
		cptr_eng = test_mot_eng(racine_eng, mot, cptr_eng); 
		cptr_germ = test_mot_germ(racine_germ, mot, cptr_germ); 
		mot = strtok(NULL, temp); 
	}
	printf("%d\n", cptr_fr); 
	printf("%d\n", cptr_eng); 
	printf("%d\n", cptr_germ); 


	// Affichage de la langue 
	donne_langue( cptr_fr, cptr_eng, cptr_germ); 



/*
//A METTRE DS UNE FONCTION 
	printf("%d\n", recherche_mot_arbre(racine_fr, "alors"));
	printf("%d\n", recherche_mot_arbre(racine_eng, "alors")); 
	printf("%d\n", recherche_mot_arbre(racine_germ, "ich")); 
// A ENLEVER
*/

	// Libération de l'espace mémoire alloué 
	suppression_arbre(racine_fr); // Dico fr
	suppression_arbre(racine_eng); // Dico eng
	suppression_arbre(racine_germ); // Dico germ


	return EXIT_SUCCESS;
}