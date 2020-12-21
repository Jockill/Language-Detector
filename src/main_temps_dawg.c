#include <stdio.h>
#include <string.h>

#include "../header/utils.h"
#include "../header/hashmap.h"
#include "../header/dawg.h"
#include "../header/io.h"

int main()
{
	int tmp = 0;
	clock_t temps[100][3] = {0};
	clock_t tdebut, tfinit, tftest, tfsup;
	for (int i=0; i<100; i++)
	{
		//DAWG
		tdebut = clock();
		dawg *racine_fr = construct_dawg("dict/french-wordlist.txt");
		tfinit = clock()-tdebut;
		tmp = dawg_test_mot_fr(racine_fr, "gratuit", 0);
		tftest = clock()-tfinit;
		suppression_dawg(racine_fr);
		tfsup = clock()-tftest;

		temps[i][0] = tfinit;
		temps[i][1] = tftest;
		temps[i][2] = tfsup;
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
