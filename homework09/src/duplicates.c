/* duplicates.c */

#include "hash.h"
#include "macros.h"
#include "table.h"

#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Structures */

typedef struct {
    bool count;
    bool quiet;
} Options;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s paths...\n", PROGRAM_NAME);
    fprintf(stderr, "    -c     Only display total number of duplicates\n");
    fprintf(stderr, "    -q     Do not write anything (exit with 0 if duplicate found)\n");
    exit(status);
}

/**
 * Check if path is a directory.
 * @param       path        Path to check.
 * @return      true if Path is a directory, otherwise false.
 */
bool is_directory(const char *path) {
  struct stat s;
  if( stat(path, &s) || !S_ISDIR(s.st_mode)){
    return false;
  }
    return S_ISDIR(s.st_mode);
}

/**
 * Check if file is in table of checksums.
 *
 *  If quiet is true, then exit if file is in checksums table.
 *
 *  If count is false, then print duplicate association if file is in
 *  checksums table.
 *
 * @param       path        Path to file to check.
 * @param       checksums   Table of checksums.
 * @param       options     Options.
 * @return      0 if Path is not in checksums, otherwise 1.
 */
size_t check_file(const char *path, Table *checksums, Options *options) {
  //int count = 0;
  Value* cs = table_search( checksums, path);
//  if(options->quiet && cs != NULL){
  //  return 1;
//  }

  if(!(options->count) && cs != NULL ){
    fprintf(stdout, "%s is duplicate of %s\n", cs->string, path);
    return 1;
  }
    if(options->quiet && cs != NULL){
      return 1;
    }
  if(cs == NULL ){
    table_insert( checksums, path, (Value)(char *)path, STRING);
    return 0;
  }
  if(options->count && cs != NULL ){
    return 1;
  }

  return 1;
}

/**
 * Check all entries in directory (recursively).
 * @param       root        Path to directory to check.
 * @param       checksums   Table of checksums.
 * @param       options     Options.
 * @return      Number of duplicate entries in directory.
 */
size_t check_directory(const char *root, Table *checksums, Options *options) {
    DIR *d = opendir(root);
    if (!d){
      fprintf(stderr, "Unable to opendir on %s: %s\n", root, strerror(errno));
      return 0;
    }

  for (struct dirent *p = readdir(d); p; p = readdir(d)) {
    if ((streq(p->d_name, ".")) || (streq(p->d_name, ".."))) {
        continue;
        }
    check_file(p->d_name, checksums, options);
    }

    closedir(d);
    return 0;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* Parse command line arguments */
  int argind = 1;
  Options* options = (Options* )malloc(sizeof(Options));
  options->count = false;
  options->quiet = false;
  int count = 0;
  PROGRAM_NAME = argv[0];

  Table* checksums = table_create(0);
    /* TODO: Parse command line arguments */
  while (argind < argc && strlen(argv[argind]) > 1 ){
    char *argument = argv[argind++];
    switch(argument[0]){
      case '-':
        switch (argument[1]) {
          case 'h':
            usage(0);
            break;
          case 'c':
            options->count = true;
            break;
          case 'q':
            options->quiet = true;
            break;
          }
          break;
      default:
    /* Check each argument */
        if( is_directory( argument ) == true){
          count += check_directory(argument, checksums, options);
          //debug("Went through directory    = %s, %i", argument, count);
        }
        else{
          count += check_file(argument, checksums, options);
          //debug("Went through file    = %s", argument);
        }
        continue;
    }
  }
//  debug("%i", count);

      if((options->quiet == true) && count == 0){
        table_delete(checksums);
        free(options);
        return 1;
      }

    if( options->count && count > 0){
      printf("%i", count);
    }
    table_delete(checksums);
    free(options);
    /* Display count if necessary */
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
