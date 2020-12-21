#ifndef __IO_H
#define __IO_H

#define DETEC_TRIE 0
#define DETEC_DAWG 1

#include <time.h>

//Pour la doc faudra attendre juste un poil hein.

void clear();

void pause();

void print_detection(int arbre);

void print_header();

void print_help();

void print_langue(float cptr_fr, float cptr_eng, float cptr_germ);

void print_quit();

void print_start();

void print_temps(int temps);

void print_listeTemps(clock_t init, clock_t detec, clock_t del);

void menu();

#endif
