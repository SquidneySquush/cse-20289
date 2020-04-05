
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s\n", PROGRAM_NAME);
    exit(status);
}

bool cat_stream(FILE *stream, char *pattern) {
    char buffer[BUFSIZ];
    bool grep = false;

    while (fgets(buffer, BUFSIZ, stream)) {
      if (strstr(buffer, pattern) != NULL){
         fputs(buffer, stdout);
         grep = true;
      }
    }
    return grep;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    int argind = 1;

    /* Parse command line arguments */
    PROGRAM_NAME = argv[0];
    if (argv[1] == NULL){
      usage(1);
    }

   while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-'){
       char *arg = argv[argind++];
       switch (arg[1]) {
            case 'h':
               usage(0);
               break;
            default:
               usage(1);
               break;
        }
    }

    if( argc > 1 ){
      return !cat_stream(stdin, argv[1]);
   }
   else{
      usage(1);
   }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
