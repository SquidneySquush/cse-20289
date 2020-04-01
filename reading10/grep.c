
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

/* Main Execution */

int main(int argc, char *argv[]) {
    int argind = 1;
    char buffer[BUFSIZ];

    /* Parse command line arguments */
    PROGRAM_NAME = argv[0];
    if (argv[1] == NULL){
      usage(1);
    }                                                  /* 5 */
    while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-') {   /* 6 */
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

    while (fgets(buffer, BUFSIZ, stdin)){
      if (strstr(buffer, argv[1])){
         fputs(buffer, stdout);
      }
      else{
         return 1;
      }
    }

}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
