
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s\n", PROGRAM_NAME);                                    /* 1 */
    exit(status);                                                                 /* 2 */
}

bool cat_stream(FILE *stream, char *pattern) {
    char buffer[BUFSIZ];

    while (fgets(buffer, BUFSIZ, stream)) {
      if (strstr(buffer, pattern)){
         fputs(buffer, stdout);
         buffer[0] = 0;
      }
      else{
         return 1;
      }
    }
    return true;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    int argind = 1;

    /* Parse command line arguments */
    PROGRAM_NAME = argv[0];
    if (argv[1] == NULL){
      usage(1);
    }
    char* pattern = argv[1];
                                          /* 5 */
   while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-'){   /* 6 */
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

    return !cat_stream(stdin, pattern);

}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
