#include "../header/arbre.h"
#include "../header/utils.h"

// Manque data et flag 
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



/*
int main() {
	Arbre racine = noeud_initialisation(); 
	noeud_insertion(racine, "zea"); 
	printf("%d\n", recherche_mot_arbre(racine, "zea")); 
	

	noeud_insertion(racine, "zearo"); 
	printf("%d\n", recherche_mot_arbre(racine, "zearoa")); 

	noeud_insertion(racine, "albert"); 
	printf("%d\n", recherche_mot_arbre(racine, "albert")); 

	suppression_arbre(racine); 


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

	return 0; 
}
*/


