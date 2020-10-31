#include <stdio.h>
#include <string.h>
#include "../header/hashmap.h"

int main ()
{
        struct hashmap_s map;

        //Création
        if (hashmap_create(2, &map) != 0)
                printf("Erreur\n");
        else
                printf("Map créée\n");

        //Ajout
        int a = 666;
        if (hashmap_get(&map, "a", strlen("a")) == NULL)
        {
                if (hashmap_put(&map, "a", strlen("a"), &a))
                        printf("Erreur\n");
                else
                        printf("Élément créé\n");
        }


        int b = 420;
        if (hashmap_get(&map, "b", strlen("b")) == NULL)
        {
                if (hashmap_put(&map, "b", strlen("b"), &b))
                        printf("Erreur\n");
                else
                        printf("Élément créé\n");
        }

        printf("Nombre d'éléments : %u\n", hashmap_num_entries(&map));

        //Récupération
        int* val = (int*)hashmap_get(&map, "b", strlen("b"));
        if (val == NULL)
        {
                printf("Erreur\n");
        }
        else printf("valeur = %d\n", *val);

        return 0;
}
