#include <stdio.h>
#include <string.h>

#include "../header/utils.h"
#include "../header/arbre.h"


int main()
{
	int tmp = 0;
	clock_t temps[100][3] = {0};
	clock_t tdebut, tfinit, tftest, tfsup;
	for (int i=0; i<100; i++)
	{
		//Trie
		tdebut = clock();
		Arbre racine_fr = construct_trie("dict/french-wordlist.txt");
		tfinit = clock()-tdebut;
		tmp = trie_test_mot_fr(racine_fr, "gratuit", 0);
		tftest = clock()-tfinit;
		suppression_arbre(racine_fr);
		tfsup = clock()-tftest;

		temps[i][1] = tfinit;
		temps[i][2] = tftest;
		temps[i][3] = tfsup;
	}

	clock_t moyInit, moyTest, moySup;
	for (int i=0; i<100; i++)
	{
		moyInit += temps[i][0];
		moyTest += temps[i][1];
		moySup += temps[i][2];
	}
	moyInit /= 100;
	moyTest /= 100;
	moySup /= 100;
	printf("Init : %ld\nTest : %ld\nSupression : %ld\n", moyInit, moyTest, moySup);
	return EXIT_SUCCESS;
}
