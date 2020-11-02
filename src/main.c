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

int main(int argc, char* argv[]) {

	// Récup le argv[1]


	Arbre racine_fr = construct("../dict/french-wordlist.txt");
	Arbre racine_eng = construct("../dict/english-wordlist.txt");
	Arbre racine_germ = construct("../dict/german-wordlist.txt");	



	printf("%d\n", recherche_mot_arbre(racine_fr, "alors"));
	printf("%d\n", recherche_mot_arbre(racine_eng, "alors")); 
	printf("%d\n", recherche_mot_arbre(racine_germ, "ich")); 
	// Here listen for user input, parse it and detect the language of the given text
	// To complete ...	


	suppression_arbre(racine_fr); // Dico fr
	suppression_arbre(racine_eng); // Dico eng
	suppression_arbre(racine_germ); // Dico germ


	return 0;
}