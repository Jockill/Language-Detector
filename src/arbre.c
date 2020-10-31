#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../header/utils.h"
#include "../header/hashmap.h"

#define N 25

typedef struct Noeud {

	//char *data; // Les mots 
	//bool flag; // Savoir si mot du dictionnaire Pr la phrase
	struct Noeud *tab[N]; // Tableau des lettres a-z 
	bool feuille; // Terminaison d'une branche et dico ? 
} Noeud; 

typedef struct Noeud *Arbre; 



// Manque data et flag 
Arbre noeud_initialisation(void) {
	Arbre nouveau_noeud = (Arbre)malloc(sizeof(Noeud)); 
	nouveau_noeud -> feuille = false; 
	for(int i = 0; i <= N; i++) {
		nouveau_noeud -> tab[i] = NULL; 
	}
	return nouveau_noeud; 
}



void noeud_insertion(Noeud *racine, char *message) {
	Arbre chemin = racine; 
	
	
	while(*message) {
		// Création d'un nv noeud si le chemin n'existe pas 
		if(chemin -> tab[*message - 'a'] == NULL) {
			chemin -> tab[*message - 'a'] = noeud_initialisation(); 
		}
		chemin = chemin -> tab[*message - 'a']; 
		message++; 
	}
	chemin -> feuille = true; 
}



// Pr savoir si est mot du dico 
bool recherche_mot_arbre(Arbre racine, char *message) {
	bool result = false; 
	if(racine == NULL) {
		return result; 
	}
	Arbre chemin = racine; 
	while(*message) {

		// Pr aller au noeud suivant 
		chemin = chemin -> tab[*message - 'a']; 
		
		// Test si le noeud suivant est existant 
		if(chemin == NULL) {
			return result; 
		}

		message++; 
	} 
	// Si le chemin noeud est une feuille et nous avons atteint 
	// la fin du message nous retournons vrai 
	result = chemin -> feuille; 
	return result; 
}



// Voir si un noeud possède un noeud fils 
bool possede_fils(Arbre chemin) {
	size_t cptr = 0;
	bool result = false; 
	while(cptr < N) {
		// Si fils 
		if(chemin -> tab[cptr]) {
			result = true; 
			return result; 
		}
	}
	return result; 
}





int main() {
	Arbre racine = noeud_initialisation(); 
	noeud_insertion(racine, "hell"); 
	printf("%d\n", recherche_mot_arbre(racine, "hello")); 
	return 0; 
}








/*
bool x = true;
printf("%B\n", x);
Ne marche pas 

%d trasnforme le "bool" en 1 si vrai sinon 0 
Implémnter de base ds ce type 

*/