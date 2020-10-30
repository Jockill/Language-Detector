#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../header/utils.h"
#include "../header/hashmap.h"

#define N 100

typedef struct Noeud {
	char *data; 
	bool flag; // Si ds le mot est ds le dicou ou non 
	struct Noeud **tab; // Tab vers ses fils 
} Noeud; 

typedef struct Noeud *Arbre; 



// Créer t-il un arbre à chaque fois ? 
Arbre noeud_initialisation(void) {
	Arbre t = (Arbre)malloc(sizeof(Noeud));
	if(t == NULL) perror("Erreur malloc"); 
	t -> data = NULL; 
	t -> flag = false; 
	t -> tab = malloc(26 * sizeof(Arbre));
	for(int i = 0; i < 26; i++) {
		t -> tab[i] = NULL; 
	}
	return t; 
}




// Si index sup à 25 devient 0 
int index_mod(int index) {
	if(index > 25) {
		index = 0;
	} 
	return index; 
}




// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 2 fonctions init (arbre puis noeud ????)
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// Faire appel à noeud_init et celle de test de mot 
void noeud_insertion_lettre(Arbre arbre, char lettre, int index) {
	//Arbre nul
	if(arbre == NULL) perror("Prbm arbre nul"); 
	//Boucle/récu qui parcours le tab pour ajouter 
	Noeud *nouv_noeud; 
	nouv_noeud = noeud_initialisation(); 
	nouv_noeud -> data = lettre; // Manque les lettres précédentes 



	// Pointe  vers le prochain fils à remplir ???? Non nécessaire si j'avais 2 fonctions d'init 
	nouv_noeud -> tab[index_mod(index + 1)] = ;  


}

void noeud_insertion_mot(Arbre arbre, char *mot) {
	// Nb de caract du mot 
	char buf_ascii[N]; // Nous plaçons les ascii ici 
	int buf_index[N]; // Nous plaçons les index ici 
	sprintf(buf_ascii, "%s", mot); 
	for(int i = 0; i < N; i++) {
		buf_index[i] = ascii_to_index(buf_ascii[i]); // Transvase les ascii tab ds index tab 
		// Nécessaire pour savoir écire ds quel tab (rappel 26 tabs)
		noeud_insertion_lettre(arbre, buf_ascii[i], buf_index[i]); 
	}
}


void recherche_mot_arbre(char *mot) {
}



void print_arbre(Noeud *arbre) {

}

int main() {
	return 0; 
}


