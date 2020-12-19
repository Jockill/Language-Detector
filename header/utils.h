#ifndef __UTILS_H
#define __UTILS_H

#define MAX_SIZE 2047


#include <stdlib.h>

void detection(int arbre, int temps);

size_t plusGrandPrefixeCommun(char* mot1, char* mot2);

void lecture(char phrase[MAX_SIZE]);

/*!
   \brief Trouve le plus grand prefixe commun à deux mots.
   \param [in] mot* mot1 Premier mot
   \param [in] mot* mot2 Deuxième mot
   \return Plus grand préfixe commun à mot1 et mot2.
*/
size_t plusGrandPrefixeCommun(char *mot1, char *mot2);


size_t ascii_to_index(char c);

void remove_char(char *word, size_t index);
void parse_word(char *word);
char *concat(const char *s1, const char *s2);

#endif
