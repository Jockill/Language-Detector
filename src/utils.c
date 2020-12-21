#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../header/utils.h"


void lecture(char phrase[MAX_SIZE+1])
{
	printf("\nVeuillez entrer la phrase à détecter : ");
	int cmpt = 0;
	getchar();
	char c = 1;
	while(cmpt < MAX_SIZE+1 && c != EOF && c != 10)
	{
		c = getchar();
		if (c!=10)
			phrase[cmpt++] = c;
	}

	char copy[MAX_SIZE+1] = {0};
	for (int i=0; i<cmpt-2; i++)
		copy[i] = phrase[i];

	phrase = copy;
}

void detection(int arbre, int temps)
{
	clear();
	clock_t tDebut, tTotal;
	char phrase[MAX_SIZE+1] = {0};

	lecture(phrase);

	if (temps == 1)
	 	tDebut = clock();


	if (arbre == DETEC_TRIE)
		detec_trie(phrase, temps);
	else if (arbre == DETEC_DAWG)
		detec_dawg(phrase, temps);


	if (temps == 1)
	{
		tTotal = clock()-tDebut;
		printf("\nLa détection a duré %ld s.\n", tTotal/CLOCKS_PER_SEC);
	}

	pause();
	clear();
}

size_t plusGrandPrefixeCommun(char* mot1, char* mot2) {
	size_t i = 0;
	while (mot1[i] == mot2[i] && (mot1[i] != '\0') && (mot2[i] != '\0'))
		i++;
	return i;
}

/**
 * Change ASCII char (a-z) to array index
 * a -> 0, b -> 1, c -> 2, ..., z -> 25
 */
size_t ascii_to_index(char c) {
	size_t index = (size_t) c;

	if(index < 97 || index > 122) {
		perror("ascii_to_index function can only read lowercase letter a-z.\n");
		exit(EXIT_FAILURE);
	}

	return index - 97;
}

/**
 * Remove char from string at the given index
 */
void remove_char(char *word, size_t index) {
	memmove(&word[index],&word[index+1],strlen(word)-index);
}

/**
 * Remove all char from given string that aren't a-z
 */
void parse_word(char *word) {
	for(size_t i = 0; i < strlen(word); i++) {
		size_t index = (size_t) word[i];
		if(index < 97 || index > 122) {
		remove_char(word, i);
		}
	}
}

/**
 * Concat two strings together
 */
char* concat(const char *s1, const char *s2) {
	char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
	// in real code you would check for errors in malloc here
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}
