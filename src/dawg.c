#include <string.h>

#include "../header/dawg.h"
#include "../header/utils.h"
#include "../header/stack.h"


void dawg_minimiser(struct dawg_sommet racine, size_t p)
{
        dawg_arete* a;
        while (stack_size(pile) > p)
        {
                a = stack_pop(pile);
                //Si a se trouve dans la hashmap
                
                if (hashmap_get(hashmap, a->sommetDroit, len) != NULL)
                {
                        dawg_relier(a->sommetGauche, a->sommetDroit);
                }
                else
                {
                        int res = hashmap_put(hashmap, key, len, a->sommetDroit);
                        if (res != 0)
                        {
                                fprintf(stderr, "dawg_minimiser : Impossible \
                                d'ajouter la valeur dans la hashmap\n");
                                exit(EXIT_FAILURE);
                        }
                }
        }
}

void dawg_ajouter(dawg_sommet depart, char* mot, size_t indexDebut)
{

        //Pour chaque lettre du suffixe ajoutée au graphe, empiler l'arrete correspondante.

        dawg_sommet* dernier = stack_pop(pile);
        dernier->motValide = true;
}

void dawg_inserer_mot(struct dawg_sommet racine, char* motPrecedent, char* mot)
{
        size_t n; //Taille du plus grand préfixe commun.
        if (motPrecedent == NULL) n = 0;
        else n = plusGrandPrefixeCommun(motPrecedent, mot);

        dawg_minimiser(racine, n);

        if (pile == NULL) dawg_ajouter(racine, mot, n);
        else
        {
                dawg_sommet* depart = stack_pop(pile);
                dawg_ajouter(depart, mot, n);
        }
}

struct dawg_sommet creation(char* pathToDic)
{
        //Instancier le DAWG
        struct dawg_sommet dawg;
        dawg.label = 0;
        dawg.arretesSortantes = NULL;
        dawg.motValide = false;

        char* lastLine = NULL;
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        FILE *fp;

        fp = fopen(dict, "r");
        if (fp == NULL)
        {
                perror("Error while opening the file.\n");
                exit(EXIT_FAILURE);
        }

        // read file
        while ((read = getline(&line, &len, fp)) != -1)
        {
                // remove newline
                size_t length = strlen(line);
                if((length > 0) && (line[length-1] == '\n'))
                {
                        line[length-1] ='\0';
                }

                dawg_inserer_mot(dawg, lastLine, line);
                lastLine = line;
        }

        fclose(fp);
        free(line);

    return dawg;
}
