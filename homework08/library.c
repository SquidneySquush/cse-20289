/* library.c: string utilities library */

#include "str.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/**
 * Convert all characters in string to lowercase.
 * @param   s       String to convert
 **/
void	str_lower(char *s) {
	for(char *c = s; *c ; c++){
		*c = tolower(*c);
	}
}

/**
 * Convert all characters in string to uppercase.
 * @param   s       String to convert
 **/
void	str_upper(char *s) {
	for(char *c = s; *c ; c++){
		*c = toupper(*c);
	}
}

/**
 * Convert all characters in string to titlecase.
 * @param   s       String to convert
 **/
void	str_title(char *s) {
	for(char *c = s; *c ; c++){
		char *prev = c;
		prev --;
		if( isalpha (*c) && !(isalpha(*prev))){
			*c = toupper(*c);
		}
		else if( isalpha (*c) && (isalpha(*prev))){
			*c = tolower(*c);
		}
	}
}

/**
 * Removes trailing newline (if present).
 * @param   s       String to modify
 **/
void    str_chomp(char *s) {
	char *c = s + strlen(s)-1;
	if (*c == '\n'){
			*c = '\0';
	}
}

/**
 * Removes whitespace from front and back of string (if present).
 * @param   s       String to modify
 **/
void    str_strip(char *s) {
	if (strlen(s)!=0){
		 char *headread = s;
		char *headwrite = headread;

		while(isspace(*headread)){
				++headread;
		}
		while(*headread){
			*headwrite = *headread;
			*headread = ' ';
			headwrite++;
			headread++;
		}

		char *tailread = headwrite;
		char *tailwrite = headwrite;
		while(isspace(*tailwrite)){
			tailread--;
			tailwrite--;
			if (isspace(*tailwrite)){
				*tailwrite = '\0';
			}
		}
	}

}

/*
 * Reverses a string.
 * @param   s       String to reverse
 **/
void    str_reverse(char *s) {
	char *tail = s + strlen(s) - 1;
	char *c = s;
	char *d;
	while(c < tail){
		d = *tail;   // passing pointers to temp char so i can switch them
		*tail-- = *c;
		*c++ = d;
	}
}

/**
 * Replaces all instances of 'from' in 's' with corresponding values in 'to'.
 * @param   s       String to translate
 * @param   from    String with letter to replace
 * @param   to      String with corresponding replacment values
 **/
void    str_translate(char *s, char *from, char *to) {
	int letter[1<<8] = {0}; // 256 bits

	for (char *c = from; *c; c++){
		letter[(int)*c] += *to;
		to ++;
	}

	for (char *str = s; *str ; str++){
		if(letter[(int)*str] != 0){
			*str = letter[(int)*str];
		}
		return;
	}
}

/**
 * Converts given string into an integer.
 * @param   s       String to convert
 * @param   base    Integer base
 * @return          Converted integer value
 **/
int	str_to_int(const char *s, int base) {
    return 0;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
