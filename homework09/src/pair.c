/* pair.c: Key/Value Pair */

#include "pair.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * Create Pair structure.
 * @param   key             Pair's key.
 * @param   value           Pair's value.
 * @param   next            Reference to next pair.
 * @param   type            Pair's value's type.
 * @return  Allocated Pair structure.
 */
Pair *	    pair_create(const char *key, const Value value, Pair *next, Type type) {
    Pair* p = (Pair*)calloc(4, sizeof(Pair));
    if (p){
    p->key = strdup(key);

    pair_update(p, value, type);

  //  if(next != NULL){
    p->next = next;

  }
    return p;
}

/**
 * Delete Pair structure.
 * @param   p               Pair structure.
 * @param   recursive       Whether or not to delete remainder of pairs.
 * return   NULL.
 */
Pair *	    pair_delete(Pair *p, bool recursive) {
    if(p){
    if (p->type == STRING){
      free(p->value.string);
    }

    if (recursive){
      pair_delete(p->next, recursive);
    }
    if(p->key){
      free(p->key);
    }
    free(p);
  }
    return NULL;
}

/**
 * Update Pair's value.
 * @param   p               Pair structure.
 * @param   value           New value for Pair.
 * @param   type            New value's type.
 */
void        pair_update(Pair *p, const Value value, Type type) {
    if (p->type == STRING){
      free(p->value.string);
    }
    switch(type){
      case STRING:
        p->value.string =  strdup(value.string);
        break;
      case NUMBER:
        p->value = value;
        break;
    }
    p->type = type;
    return;
}

/**
 * Format Pair by writing to stream.
 * @param   p               Pair structure.
 * @param   stream          File stream to write to.
 */
void        pair_format(Pair *p, FILE *stream) {
  if(p->type == STRING){
    fprintf(stream, "%s\t%s\n", p->key, p->value.string );
  }
  else{
    fprintf(stream, "%s\t%ld\n", p->key, p->value.number );
  }
  return;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
