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

long string_hash32(char *key) {
    /* Calculates the hash of the `key` string. 32bit. */
    int len = strlen(key);
    int hash;
    char *p = key;
    hash = p[0] << 7;
    for (int i = 0; i < len; i++) {
        hash = (hash * 1000003) ^ *(p + i);
    }
    hash ^= len;
    return hash;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Usage: %s <string-to-hash>\n", argv[0]);
        return 1;
    }
    printf ("64bit hash: %" PRIu64 "\n", string_hash64(argv[1]));
    printf ("32bit hash: %ld\n", string_hash32(argv[1]));

    return 0;
}
