#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../header/utils.h"
#include "utils.c"
//#include "../header/hashmap.h"

#define N 25 // Taille du tab de pointeurs de l'alphabet 

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
	noeud_insertion(racine, "zea"); 
	printf("%d\n", recherche_mot_arbre(racine, "zea")); 
	




/*
	char *mot= "chasse";
	printf("entier : %d\n", mot); 
	printf("string : %s\n", mot);
	printf("char : %c\n", *mot); 
	printf("entier : %d\n", 'a'); 
	printf("char : %c\n", 'a'); 

	char *mot= "chasse";  
	printf("entier : %d\n", mot); 
	printf("string : %s\n", mot); // Ne pas mettre le & !!
	printf("char : %c\n", mot); // & pas sur que change quelque chose 
	
	mot++; 
	printf("entier : %d\n", mot); 
	printf("string : %s\n", mot); 
	printf("char : %c\n", mot); 

	
	//mot = *mot - 'a'; 
	//printf("entier : %d\n", mot); 
	//printf("string : %s\n", mot); 
	//printf("char : %c\n", mot); 
*/
	return 0; 
}



/*
POUR : *message - 'a'
*message == premier pointeur de la string 
- 'a' == 


*/







/*
bool x = true;
printf("%B\n", x);
Ne marche pas 

%d trasnforme le "bool" en 1 si vrai sinon 0 
Implémnter de base ds ce type 

*/