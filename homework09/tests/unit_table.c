/* test_table.c */

#include "table.h"
#include "macros.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Tests */

int test_00_table_create() {
    /* Create Table with defaults */
    Table *t = table_create(0);
    assert(t != NULL);
    assert(t->capacity == DEFAULT_CAPACITY);
    assert(t->size     == 0);
    free(t->buckets);
    free(t);

    /* Create Table with custom arguments */
    t = table_create(2);
    assert(t != NULL);
    assert(t->capacity == 2);
    assert(t->size     == 0);
    free(t->buckets);
    free(t);

    return EXIT_SUCCESS;
}

int test_01_table_delete() {
    const size_t NBUCKETS = 4;

    /* Create Table and populate buckets */
    Table *t = table_create(NBUCKETS);

    for (size_t i = 0; i < NBUCKETS; i++) {
        char k[BUFSIZ];
        sprintf(k, "%lu", i);
        t->buckets[i].next = pair_create(k, (Value)k, NULL, STRING);
        for (size_t j = 0; j < NBUCKETS; j++) {
            sprintf(k, "%lu", j);
            t->buckets[i].next = pair_create(k, (Value)k, t->buckets[i].next, STRING);
        }
    }

    /* Delete Table */
    table_delete(t);
    return EXIT_SUCCESS;
}

int test_02_table_insert() {
    const size_t NBUCKETS = 8;

    char k[BUFSIZ];
    Table *t = table_create(NBUCKETS);
    for (size_t i = 0; i < NBUCKETS/2; i++) {
        sprintf(k, "%lx", i);
        /* Insert */
        table_insert(t, k, (Value)(int64_t)i, NUMBER);
        assert(t->size == (i + 1));

        bool inserted = false;
        for (size_t b = 0; b < NBUCKETS && !inserted; b++) {
            inserted = t->buckets[b].next && \
                       streq(t->buckets[b].next->key, k) && \
                       t->buckets[b].next->value.number == i;
        }
        assert(inserted);

        /* Update */
        table_insert(t, k, (Value)(int64_t)(i*2), NUMBER);
        assert(t->size == (i + 1));

        bool updated = false;
        for (size_t b = 0; b < NBUCKETS && !updated; b++) {
            updated = t->buckets[b].next && \
                      streq(t->buckets[b].next->key, k) && \
                      t->buckets[b].next->value.number == i*2;
        }
        assert(updated);
        assert(t->size == (i + 1));
    }
    assert(t->capacity == NBUCKETS);

    table_delete(t);
    return EXIT_SUCCESS;
}

int test_03_table_search() {
    char k[BUFSIZ];
    Table *t = table_create(0);

    for (size_t i = 0; i < DEFAULT_CAPACITY/2; i++) {
        sprintf(k, "%lx", i);
        /* Insert */
        table_insert(t, k, (Value)(int64_t)i, NUMBER);
        assert(t->size == (i + 1));
    }
    assert(t->capacity == DEFAULT_CAPACITY);

    for (size_t i = 0; i < DEFAULT_CAPACITY/2; i++) {
        /* Search Success */
        sprintf(k, "%lx", i);
        Value *v = table_search(t, k);
        assert(v         != NULL);
        assert(v->number == i);
        /* Search Failure */
        sprintf(k, "-%lx", i);
        assert(table_search(t, k) == NULL);
    }

    table_delete(t);
    return EXIT_SUCCESS;
}

int test_04_table_remove() {
    char k[BUFSIZ];
    Table *t = table_create(0);

    for (size_t i = 0; i < DEFAULT_CAPACITY*3; i++) {
        sprintf(k, "%lx", i);
        /* Insert */
        table_insert(t, k, (Value)(int64_t)i, NUMBER);
        assert(t->size == (i + 1));
        assert(table_search(t, k) != NULL);
    }
    assert(t->capacity == DEFAULT_CAPACITY);

    for (size_t i = DEFAULT_CAPACITY; i < DEFAULT_CAPACITY*3; i++) {
        sprintf(k, "%lx", i);
        assert(table_remove(t, k) == true);
        assert(table_search(t, k) == NULL);
        assert(t->size == DEFAULT_CAPACITY*3 + DEFAULT_CAPACITY - i - 1);
        assert(table_remove(t, k) == false);
    }
    assert(t->size == DEFAULT_CAPACITY);
    table_delete(t);
    return EXIT_SUCCESS;
}

int test_05_table_format() {
    const size_t NBUCKETS = 8;

    char k[BUFSIZ];
    Table *t = table_create(NBUCKETS);
    for (size_t i = 0; i < NBUCKETS/2; i++) {
        sprintf(k, "%ld", i);
        /* Insert */
        table_insert(t, k, (Value)(int64_t)(i*2), NUMBER);
    }

    char p[BUFSIZ] = "/tmp/test_table_XXXXXX";
    int  fd = mkstemp(p);
    assert(fd > 0);
    unlink(p);
    FILE *fs = fdopen(fd, "r+");
    assert(fs);

    /* Dump to temporary file */
    table_format(t, fs);
    assert(fseek(fs, 0, SEEK_SET) == 0);

    /* Read from temporary file */
    char b[BUFSIZ];
    int keys   = 0;
    int values = 0;

    while (fgets(b, BUFSIZ, fs)) {
        int key, value;
        sscanf(b, "%d\t%d", &key, &value);
        keys   += key;
        values += value;
    }
    assert(keys   == 6);
    assert(values == 12);

    fclose(fs);
    table_delete(t);
    return EXIT_SUCCESS;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s NUMBER\n\n", argv[0]);
        fprintf(stderr, "Where NUMBER is right of the following:\n");
        fprintf(stderr, "    0  Test table_create\n");
        fprintf(stderr, "    1  Test table_delete\n");
        fprintf(stderr, "    2  Test table_insert\n");
        fprintf(stderr, "    3  Test table_search\n");
        fprintf(stderr, "    4  Test table_remove\n");
        fprintf(stderr, "    5  Test table_format\n");
        return EXIT_FAILURE;
    }

    int number = atoi(argv[1]);
    int status = EXIT_FAILURE;

    switch (number) {
        case 0:  status = test_00_table_create(); break;
        case 1:  status = test_01_table_delete(); break;
        case 2:  status = test_02_table_insert(); break;
        case 3:  status = test_03_table_search(); break;
        case 4:  status = test_04_table_remove(); break;
        case 5:  status = test_05_table_format(); break;
        default: fprintf(stderr, "Unknown NUMBER: %d\n", number); break;
    }

    return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
