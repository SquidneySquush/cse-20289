/* str_title: convert strings to title-case */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *str_title(const char *s) {
    char *t = strdup(s);
    //strncpy(t, s, strlen(t));

    char *c = t;
    while (*c) {
      *c = toupper(*c);
      while (*c && !isspace(*c)){
				c++;
			}
      while (*c &&  isspace(*c)){
				c++;
			}
    }
		*c= '\0';
		puts(t);
		free(t);
		return t;
}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
      str_title(argv[i]);
    }

    return 0;
}
