/* main.c: string library utility */

#include "str.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char *PROGRAM_NAME = NULL;

/* Flags */

enum {
    /* TODO*: Enumerate Flags */
    STRIP   = 1<<1,
    REVERSE = 1<<2,
    LOWER   = 1<<3,
    UPPER   = 1<<4,
    TITLE   = 1<<5
};

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s SOURCE TARGET\n\n", PROGRAM_NAME);
    fprintf(stderr, "Post Translation filters:\n\n");
    fprintf(stderr, "   -s      Strip whitespace\n");
    fprintf(stderr, "   -r      Reverse line\n");
    fprintf(stderr, "   -l      Convert to lowercase\n");
    fprintf(stderr, "   -u      Convert to uppercase\n");
    fprintf(stderr, "   -t      Convert to titlecase\n");
    exit(status);
}

void translate_stream(FILE *stream, char *source, char *target, int flag) {
    /* TODO: Process each line in stream by performing transformations */
  char buffer[BUFSIZ];

  while(fgets(buffer, BUFSIZ, stream)!=NULL){

    str_chomp(buffer);
  if( source != NULL && target != NULL){

    str_translate(buffer,source,target);

  }

  if (flag & STRIP){

    str_strip(buffer);
  }
  if (flag & REVERSE){
    str_reverse(buffer);
  }
  if (flag & LOWER){
    str_lower(buffer);
  }
  if (flag & UPPER){
    str_upper(buffer);
  }
  if (flag & TITLE){
    str_title(buffer);
  }

  puts(buffer);
}

}

/* Main Execution */

int main(int argc, char *argv[]) {
  int argind = 1;
  int32_t flag = 0;
  PROGRAM_NAME = argv[0];

    /* TODO: Parse command line arguments */
  while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-'){
    char *arg = argv[argind++];
    switch (arg[1]) {
      case 'h':
        usage(0);
        break;
      case 's':
        flag ^= 1<<1;
        break;
      case 'r':
        flag ^= 1<<2;
        break;
      case 'l':
        flag ^= 1<<3;
        break;
      case 'u':
        flag ^= 1<<4;
        break;
      case 't':
        flag ^= 1<<5;
        break;
   
      }
    }
  char *source = argv[argind++];
  char *target = argv[argind++];

  /* TODO: Translate Stream */
  translate_stream(stdin, source, target, flag );

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
