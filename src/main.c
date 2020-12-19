#include <stdio.h>
#include <string.h>

#include "../header/utils.h"
#include "../header/hashmap.h"
#include "../header/arbre.h"
#include "../header/io.h"
// #include "arbre.c"

#define MAX_SIZE 2047
#define DETEC_TRIE 0
#define DETEC_DAWG 1

void checkargs(int argc, char** argv)
{
	if (argc > 4)
	{
		fprintf(stderr, "Mauvais arguments.\n");
		print_help();
		exit(1);
	}
	else if (argc > 1)
	{
		int arbre = DETEC_TRIE;
		int temps = 0;
		for (int i=1; i<argc; i++)
		{
			//creer var

			if (!strcmp(argv[i], "-T") || !strcmp(argv[i], "--trie"))
			{
				arbre = DETEC_TRIE;
			}
			else if (!strcmp(argv[i], "-D") || !strcmp(argv[i], "--dawg"))
			{
				arbre = DETEC_DAWG;
			}
			else if (!strcmp(argv[i], "-t=0"))
			{
				temps = 0;
			}
			else if (!strcmp(argv[i], "-t=1"))
			{
				temps = 1;
			}

		}
		detection(arbre, temps);
		// fprintf(stderr, "temps = %d\narbre = %d\n", temps, arbre);
	}
}


int main(int argc, char** argv)
{
	if (argc != 1) checkargs(argc, argv);
	menu();
	return 0;
}
