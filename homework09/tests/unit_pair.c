/* unit_pair.c */

#include "pair.h"
#include "macros.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Constants */

static char *KEY0 = "123";
static char *KEY1 = "wake me up inside";

/* Tests */

int test_00_pair_create() {
    /* Create one entry */
    Pair *p0 = pair_create(KEY0, (Value)strtol(KEY0, NULL, 10), NULL, NUMBER);

    assert(p0);
    assert(streq(p0->key, KEY0));
    assert(p0->value.number == strtol(KEY0, NULL, 10));
    assert(p0->next == NULL);
    assert(p0->type == NUMBER);

    /* Create one entry linked to previous entry */
    Pair *p1 = pair_create(KEY1, (Value)KEY1, p0, STRING);
    assert(p1);
    assert(streq(p1->key, KEY1));
    assert(streq(p1->value.string, KEY1));
    assert(p1->next == p0);
    assert(p1->type == STRING);

    free(p0->key);
    free(p0);
    free(p1->key);
    free(p1->value.string);
    free(p1);

    return EXIT_SUCCESS;
}

int test_01_pair_delete() {
    /* Create and delete one entry */
    Pair *p0 = pair_create(KEY0, (Value)strtol(KEY0, NULL, 10), NULL, NUMBER);
    assert(p0);

    p0 = pair_delete(p0, false);
    assert(p0 == NULL);
    
    /* Create and delete two linked entries */
    p0 = pair_create(KEY0, (Value)strtol(KEY0, NULL, 10), NULL, NUMBER);
    assert(p0);
    
    Pair *p1 = pair_create(KEY1, (Value)KEY1, p0, STRING);
    assert(p1);
    
    p1 = pair_delete(p1, true);
    assert(p1 == NULL);

    /* Create and delete ten linked entries */
    Pair *head = NULL;
    for (int i = 0; i < 10; i++) {
        head = pair_create(KEY0, (Value)KEY0, head, STRING);
        assert(head);
    }
    head = pair_delete(head, true);
    assert(head == NULL);

    /* NULL check */
    pair_delete(NULL, false);
    return EXIT_SUCCESS;
}

int test_02_pair_update() {
    /* Create and update entry */
    Pair *p0 = pair_create(KEY0, (Value)strtol(KEY0, NULL, 10), NULL, NUMBER);
    assert(p0);
    assert(streq(p0->key, KEY0));
    assert(p0->value.number == strtol(KEY0, NULL, 10));
    assert(p0->next == NULL);
    assert(p0->type == NUMBER);

    pair_update(p0, (Value)KEY1, STRING);
    assert(streq(p0->value.string, KEY1));

    /* Create and update entry */
    Pair *p1 = pair_create(KEY1, (Value)KEY1, p0, STRING);
    assert(p1);
    assert(streq(p1->key, KEY1));
    assert(streq(p1->value.string, KEY1));
    assert(p1->next == p0);
    assert(p1->type == STRING);
    pair_update(p1, (Value)strtol(KEY0, NULL, 10), NUMBER);
    assert(p1->value.number == strtol(KEY0, NULL, 10));

    p0 = pair_delete(p0, false);
    assert(p0 == NULL);

    p1 = pair_delete(p1, false);
    assert(p1 == NULL);
    return EXIT_SUCCESS;
}

int test_03_pair_format() {
    /* Create temporary file */
    char path[BUFSIZ] = "/tmp/test_pair_XXXXXXX";
    int   fd = mkstemp(path);
    assert(fd > 0);
    unlink(path);

    FILE *fs = fdopen(fd, "w+");
    assert(fs);

    /* Dump entry to file */
    Pair *p0 = pair_create(KEY0, (Value)KEY1, NULL, STRING);
    pair_format(p0, fs);

    /* Rewind file */
    assert(fseek(fs, 0, SEEK_SET) == 0);

    /* Read entry output */
    char buffer[BUFSIZ];
    assert(fgets(buffer, BUFSIZ, fs));
    assert(streq(buffer, "123\twake me up inside\n"));

    pair_delete(p0, true);
    fclose(fs);
    return EXIT_SUCCESS;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s NUMBER\n\n", argv[0]);
        fprintf(stderr, "Where NUMBER is right of the following:\n");
        fprintf(stderr, "    0  Test pair_create\n");
        fprintf(stderr, "    1  Test pair_delete\n");
        fprintf(stderr, "    2  Test pair_update\n");
        fprintf(stderr, "    3  Test pair_format\n");
        return EXIT_FAILURE;
    }   

    int number = atoi(argv[1]);
    int status = EXIT_FAILURE;

    switch (number) {
        case 0:  status = test_00_pair_create(); break;
        case 1:  status = test_01_pair_delete(); break;
        case 2:  status = test_02_pair_update(); break;
        case 3:  status = test_03_pair_format(); break;
        default: fprintf(stderr, "Unknown NUMBER: %d\n", number); break;
    }
    
    return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
