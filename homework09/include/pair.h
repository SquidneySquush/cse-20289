/* pair.h */

#ifndef PAIR_H
#define PAIR_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* Type Definitions */

typedef union {
    int64_t number;
    char   *string;
} Value;

typedef enum {
    NUMBER,
    STRING,
} Type;

/* Structures */

typedef struct Pair Pair;
struct Pair {
    char   *key;
    Value   value;
    Type    type;
    Pair   *next;
};

/* Functions */

Pair *      pair_create(const char *key, const Value value, Pair *next, Type type);
Pair *      pair_delete(Pair *e, bool recursive);
void        pair_update(Pair *e, const Value value, Type type);
void        pair_format(Pair *e, FILE *stream);

#endif

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
