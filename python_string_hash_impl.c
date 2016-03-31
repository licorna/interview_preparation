#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t string_hash64(char *key) {
    /* Calculates the hash of the `key` string. 64bit. */
    int len = strlen(key);
    uint64_t hash;
    char *p = key;
    hash = p[0] << 7;
    for (int i = 0; i < len; i++) {
        hash = (hash * 1000003) ^ *(p + i);
    }
    hash ^= len;
    return hash;
}

long string_hash32(char *key, int M) {
    /* Calculates the hash of the `key` string. 32bit. */
    int len = strlen(key);
    unsigned long hash;
    char *p = key;
    hash = p[0] << 7;
    for (int i = 0; i < len; i++) {
        hash = (hash * 1000003) ^ *(p + i);
    }
    hash ^= len;
    return hash % M;
}
