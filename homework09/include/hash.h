/* hash.h */

#ifndef HASH_H
#define HASH_H

#include <stdbool.h>
#include <stdint.h>

#include <openssl/md5.h>

/* Constants */

#define HEX_DIGEST_LENGTH   ((MD5_DIGEST_LENGTH<<1) + 1)

/* Functions */

uint64_t    hash_from_data(const void *data, size_t n);
bool        hash_from_file(const char *path, char hexdigest[HEX_DIGEST_LENGTH]);

#endif

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
