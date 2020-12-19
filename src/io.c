#include <stdio.h>
#include "../header/io.h"

void clear(){
	printf("\e[1;1H\e[2J");
}

void pause()
{
	printf("\nAppuyez sur entrée pour continuer...\n");
	char c = getchar();
	//Eviter le skip si stdin est rempli par un retour a la ligne.
	if (c == 10)
		c = getchar();
}

//0 pour trie, 1 pour DAWG
void print_detection(int arbre)
{
	printf("====================================================\n");
	printf("Détection avec un \n");
	if (arbre == DETEC_TRIE)
	printf("\033[32;1m[X] trie\033[0m   \033[31;1m[ ] DAWG\033[0m\n");
	else
	printf("\033[31;1m[ ] trie\033[0m   \033[32;1m[X] DAWG\033[0m\n");
	printf("Appuyez sur 'a' pour changer ce paramètre.\n");
	printf("====================================================\n");
}

void print_header()
{
	printf("\
	    _\n\
	   | |    __ _ _ __   __ _ _   _  __ _  __ _  ___ \n\
	   | |   / _` | '_ \\ / _` | | | |/ _` |/ _` |/ _ \\\n\
	   | |__| (_| | | | | (_| | |_| | (_| | (_| |  __/\n\
	   |_____\\__,_|_| |_|\\__, |\\__,_|\\__,_|\\__, |\\___|\n\
	                     |___/             |___/      \n\
	        ____       _            _             \n\
	       |  _ \\  ___| |_ ___  ___| |_ ___  _ __ \n\
	       | | | |/ _ \\ __/ _ \\/ __| __/ _ \\| '__|\n\
	       | |_| |  __/ ||  __/ (__| || (_) | |   \n\
	       |____/ \\___|\\__\\___|\\___|\\__\\___/|_| \n");


	/*printf("\
	             __  __ _____ _   _ _   _             \n\
	 _____ _____|  \\/  | ____| \\ | | | | |_____ _____ \n\
	|_____|_____| |\\/| |  _| |  \\| | | | |_____|_____|\n\
	|_____|_____| |  | | |___| |\\  | |_| |_____|_____|\n\
	            |_|  |_|_____|_| \\_|\\___/             \n");*/
}

void print_help()
{
	printf("Voici l'aide\n");
}

void print_langue(size_t cptr_fr, size_t cptr_eng, size_t cptr_germ)
{
	if(cptr_fr > cptr_eng && cptr_fr > cptr_germ)
	printf("La langue détectée est le français.\n");
	else if(cptr_eng > cptr_fr && cptr_eng > cptr_germ)
	printf("La langue détectée est l'anglais.\n");
	else if(cptr_germ > cptr_fr && cptr_germ > cptr_eng)
	printf("La langue détectée est l'allemand.\n");
	// Tous les compteurs à zéro : langue inconnue
	else
	printf("La langue utilisée n'est pas disponible pour le moment.\n");
}

void print_quit()
{
	printf("Appuyez sur 'q' pour quiter\n");
	printf("====================================================\n");
}

void print_start()
{
	printf("Appuyez sur 'd' pour démarer la détection\n");
	printf("====================================================\n");
}

//0 pour non, 1 pour oui
void print_temps(int temps)
{
	printf("Renseigner le temps d'éxécution ?\n");
	if (temps == 1)
		printf("\033[32;1m[X] Oui\033[0m    \033[31;1m[ ] Non\033[0m\n");
	else
		printf("\033[31;1m[ ] Oui\033[0m    \033[32;1m[X] Non\033[0m\n");
	printf("Appuyez sur 't' pour changer ce paramètre.\n");
	printf("====================================================\n");
}

void menu()
{
	int temps = 1;
	int arbre = DETEC_TRIE;
	char inp = 0;

	do
	{
		clear();
		switch (inp)
		{
			case 'a':
				arbre = !arbre;
			break;
			case 't':
				temps = !temps;
			break;
			case 'd':
				detection(arbre, temps);
			break;
		}
		print_header();
		printf("\n\n");
		print_detection(arbre);
		print_temps(temps);
		print_start();
		print_quit();
		inp = getchar();
	} while (inp != 'q');
}
