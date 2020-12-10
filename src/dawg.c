//#include "../header/dawg.h"
// #include "../header/utils.h"
#include "../header/stack.h"
#include "../src/utils.c"

#include <stdbool.h>
#define N 26 
#define MOT 100


typedef struct dawg_sommet
{
	char label[MOT]; /*!< Label unique du sommet courant*/
	struct dawg_sommet *tab[N]; /*!< Arêtes sortantes du sommet. */
	bool feuille; /*!< Mot présent dans le dictionnaire ? */
} dawg_sommet;


typedef struct dawg_arete
{
	char label[MOT]; /*!< Label de l'arete */
	struct dawg_sommet *sommetGauche; /*!< Pointeur vers le sommet gauche. */ // SRC
	struct dawg_sommet *sommetDroit; /*!< Pointeur vers le sommet droit. */	// DST 
} dawg_arete;

typedef struct dawg_sommet *DAWG; 
//typedef struct dawg_arete *dawg_arete; 







DAWG noeud_initialisation() {
	dawg_sommet *nouveau_noeud = (DAWG)malloc(sizeof(dawg_sommet)); 
//	dawg_arete arete = malloc(); 
	nouveau_noeud -> feuille = false; 

//	nouveau_noeud -> label = 0; // De la racine 


	for(size_t i = 0; i < N; i++) {
		nouveau_noeud -> tab[i] = NULL; 
	}
	return nouveau_noeud; 
}






void dawg_inserer_destination(DAWG racine, char *source, char *destination) // sommet gauche et sommet droit 
{
	// Avant minimisation 
	DAWG chemin = racine; 
	
	
// MALLOC SUR ARETE 
	dawg_arete *arete;

	size_t index; 
	

	char *dest_const = destination;  
	int cptr = 2;

	dawg_sommet *sommetGauche;
	dawg_sommet *sommetDroit = chemin;

	while(*destination) {
		arete = malloc(sizeof(dawg_arete));
		arete -> sommetGauche = sommetDroit;


		char label_arete_temp[MOT];
		snprintf(label_arete_temp, cptr - 1, "%s", dest_const); // -1 au cptr, pour avoir la valeur avant 

		index = ascii_to_index(*destination); 
		// Création d'un nv noeud si le chemin n'existe pas 
		if(chemin -> tab[index] == NULL) {
			chemin -> tab[index] = noeud_initialisation(); 
		}
		chemin = chemin -> tab[index]; 

		snprintf(chemin -> label, cptr, "%s", dest_const); 
//		printf(" %s \n", chemin -> label); 
//		printf("%d\n", cptr); 
		cptr++; 

		// grace a l autre snprintf
		sprintf(arete -> label,"%s-%s", label_arete_temp, chemin -> label); 
		//printf("LABEL ARETE : %s\n", arete -> label); 


		sommetDroit = chemin; 
		arete -> sommetDroit = sommetDroit;

		// Pour voir si sommet transvase bien les sommets 
		//printf("sG : %p et sD : %p\n", arete -> sommetGauche, arete -> sommetDroit); 

		destination++; 
	}
	chemin -> feuille = true; 

	
	// MINISATION DE CES MORTS 
	// size_t n; //Taille du plus grand préfixe commun.
	// if (source == NULL) n = 0;
	// else n = plusGrandPrefixeCommun(source, destination);

	// dawg_minimiser(racine, n);

	// if (pile == NULL) dawg_ajouter(racine, destination, n);
	// else
	// {
	// 	dawg_sommet* depart = stack_pop(pile);
	// 	dawg_ajouter(depart, destination, n);
	// }
}




bool recherche_mot_arbre(DAWG racine, char *message) {
	bool result = false; 
	if(racine == NULL) {
		return result; 
	}
	size_t index; 
	DAWG chemin = racine; 
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



// Ajouter les arêtes 
void suppression_dawg(DAWG racine) {
	for(size_t i = 0; i < N; i++) {
		if(racine -> tab[i] != NULL) {
			suppression_dawg(racine -> tab[i]); 
		}
		else { 
			continue; 
		}
	}
	free(racine); 
}




// void dawg_minimiser(struct dawg_sommet racine, size_t p)
// {
// 	dawg_arete* a;
// 	while (stack_size(pile) > p)
// 	{
// 		a = stack_pop(pile);
// 		//Si a se trouve dans la hashmap
// 		if (hashmap_get(hashmap, a->sommetDroit, len) != NULL)
// 		{
// 			dawg_relier(a->sommetGauche, a->sommetDroit);
// 		}
// 		else
// 		{
// 			int res = hashmap_put(hashmap, key, len, a->sommetDroit);
// 			if (res != 0)
// 			{
// 				fprintf(stderr, "dawg_minimiser : Impossible \
// 				d'ajouter la valeur dans la hashmap\n");
// 				exit(EXIT_FAILURE);
// 			}
// 		}
// 	}
// }

// void dawg_ajouter(dawg_sommet depart, char* destination, size_t indexDebut)
// {

// 	//Pour chaque lettre du suffixe ajoutée au graphe, empiler l'arrete correspondante.

// 	dawg_sommet* dernier = stack_pop(pile);
// 	dernier->destinationValide = true;
// }


// struct dawg_sommet creation(char* pathToDic)
// {
// 	//Instancier le DAWG
// 	struct dawg_sommet dawg;
// 	dawg.label = 0;
// 	dawg.arretesSortantes = NULL;
// 	dawg.destinationValide = false;

// 	char* lastLine = NULL;
// 	char *line = NULL;
// 	size_t len = 0;
// 	ssize_t read;
// 	FILE *fp;

// 	fp = fopen(dict, "r");
// 	if (fp == NULL)
// 	{
// 		perror("Error while opening the file.\n");
// 		exit(EXIT_FAILURE);
// 	}

// 	// read file
// 	while ((read = getline(&line, &len, fp)) != -1)
// 	{
// 		// remove newline
// 		size_t length = strlen(line);
// 		if((length > 0) && (line[length-1] == '\n'))
// 		{
// 			line[length-1] ='\0';
// 		}

// 		dawg_inserer_destination(dawg, lastLine, line);
// 		lastLine = line;
// 	}

// 	fclose(fp);
// 	free(line);

//     return dawg;
// }


int main() {
	DAWG racine = noeud_initialisation(); 
	
	dawg_inserer_destination(racine, "", "zea"); 
	printf("%d\n", recherche_mot_arbre(racine, "zea"));

	dawg_inserer_destination(racine, "", "zearo"); 
	printf("%d\n", recherche_mot_arbre(racine, "zearo")); 

	dawg_inserer_destination(racine, "", "albert"); 
	printf("%d\n", recherche_mot_arbre(racine, "albert")); 

	suppression_dawg(racine); 
}