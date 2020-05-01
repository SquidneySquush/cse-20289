/* table.h */

#ifndef TABLE_H
#define TABLE_H

#include "pair.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Constants */

#define DEFAULT_CAPACITY    (1<<10)

/* Structures */

typedef struct {
    Pair    *buckets;
    size_t   capacity;
    size_t   size;
} Table;

/* Functions */

Table *	    table_create(size_t capacity);
Table *	    table_delete(Table *t);

void        table_insert(Table *t, const char *key, const Value value, Type type);
Value *     table_search(Table *t, const char *key);
bool        table_remove(Table *t, const char *key);

void	    table_format(Table *t, FILE *stream);

#endif

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
