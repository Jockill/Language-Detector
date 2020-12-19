#ifndef __IO_H
#define __IO_H

#define DETEC_TRIE 0
#define DETEC_DAWG 1

//Pour la doc faudra attendre juste un poil hein.

void clear();

void pause();

void print_detection(int arbre);

void print_header();

void print_help();

void print_langue(size_t cptr_fr, size_t cptr_eng, size_t cptr_germ);

void print_quit();

void print_start();

void print_temps(int temps);

void menu();

#endif
