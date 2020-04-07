/* library.c: string utilities library */

#include "str.h"

#include <ctype.h>
#include <string.h>
#include <math.h>

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
		char *start = s;
		char *end = s + strlen(s) -1;;

		while(isspace(*start)){
			start++;
		}
		while(isspace(*end)){
			end--;
		}

		while( start <= end){
			*s = *start;
			s++;
			start++;
		}
		*s = 0;
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
		to++;
	}

	for (char *str = s; *str; str++){
			if(letter[(int)*str] != 0){
				*str = letter[(int)*str];
			}
	}
}

/**
 * Converts given string into an integer.
 * @param   s       String to convert
 * @param   base    Integer base
 * @return          Converted integer value
 **/
int	str_to_int(const char *s, int base) {
	int num = 0;
	int j = 1 ;

	switch(base){
		case 2:
			for (const char *c = s + strlen(s) - 1; c >= s; c--){
				if (isdigit(*c)){
					num += (((int)*c - 48) * j);
				}
				j *= base;
			}
			break;
		case 8:
			for (const char *c = s + strlen(s) - 1; c >= s; c--){
				if (isdigit(*c)){
					num += (((int)*c - 48) * j);
				}
				j *= base;
			}
			break;
		case 10:
			for (const char *c = s + strlen(s) - 1; c >= s; c--){
				if (isdigit(*c)){
					num += (((int)*c - 48) * j);
				}
				j *= base;
			}
			break;
		case 16:
			for (const char *c = s + strlen(s) - 1; c >= s; c--){
				if (isdigit(*c)){
					num += (((int)*c - 48) * j);
				}
				if (isalpha(*c)){
					num += (((int)toupper(*c)) - 55) * j;
				}
				j *= base;
			}
			break;
	}
    return num;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
