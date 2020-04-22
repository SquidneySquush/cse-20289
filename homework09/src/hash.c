/* hash.c: hash functions */

#include "hash.h"

#include <stdlib.h>
#include <openssl/md5.h>
#include <unistd.h>
#include <stdio.h>

/**
 * Constants
 * http://isthe.com/chongo/tech/comp/fnv/
 */

#define FNV_OFFSET_BASIS    (0xcbf29ce484222325ULL)
#define FNV_PRIME           (0x100000001b3ULL)

/**
 * Compute FNV-1 hash.
 * @param   data            Data to hash.
 * @param   n               Number of bytes in data.
 * @return  Computed hash as 64-bit unsigned integer.
 */
uint64_t    hash_from_data(const void *data, size_t n) {
    uint64_t  hash = FNV_OFFSET_BASIS;
    uint8_t *byte = (uint8_t *)data;
    for(size_t i = 0; i < n; i++){
        hash = hash ^ byte[i];
        hash = hash * FNV_PRIME;
    }
    return hash;
}

/**
 * Compute MD5 digest.
 * @param   path            Path to file to checksum.
 * @param   hexdigest       Where to store the computed checksum in hexadecimal.
 * @return  Whether or not the computation was successful.
 */
bool        hash_from_file(const char *path, char hexdigest[HEX_DIGEST_LENGTH]) {
    MD5_CTX c;
    uint8_t buffer[BUFSIZ];
    uint8_t rawdig[MD5_DIGEST_LENGTH];
    ssize_t bytes;

    MD5_Init(&c);
    FILE* src_file = fopen(path , "r");
    if (!src_file) {
    	return EXIT_FAILURE;
    }

    bytes = fread(buffer, 1, BUFSIZ, src_file);
    while(bytes > 0){
        MD5_Update(&c, buffer, bytes);
        bytes = fread(buffer, 1, BUFSIZ, src_file);
    }

    fclose(src_file);
    MD5_Final(rawdig, &c);

    for (int i = 0; i < MD5_DIGEST_LENGTH; i++){
      sprintf(hexdigest + 2*i, "%02x", rawdig[i]);
    }

    return 1;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
