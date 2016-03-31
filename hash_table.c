/* Hash table implementation, should reproduce Python's dict. */

#import <stdlib.h>
#import <stdio.h>
#import <string.h>
#import "prlib.h"

typedef struct DictNode {
    unsigned long hash; // precomputed hash key
    char *key; // string key
    int value; // int value
} DictNode;

int DICT_SIZE = 31;
typedef enum {LINEAR_PROBING, HASH_PROBING, SEPARATE_CHAINING} Strategy;
// Hash probing: probing done by Python dict (not linear)

typedef struct Dict {
    DictNode *table;
    int size;
    Strategy strategy;
} Dict;

Dict *dict() {
    Dict *new = (Dict *) malloc(sizeof(Dict));
    new->table = (DictNode *) malloc(sizeof(DictNode) * DICT_SIZE);
    new->size = DICT_SIZE;
    for (int i = 0; i < DICT_SIZE; i++) {
        new->table[i].key = NULL;
    }
    new->strategy = LINEAR_PROBING;
    return new;
}

DictNode *dict_get(Dict *_dict, char *key) {
    unsigned long hash = string_hash32(key, _dict->size);
    for (int i = hash; i < _dict->size && _dict->table[i].key != NULL; i++) {
        if (!strcmp(_dict->table[i].key, key)) {
            return &_dict->table[i];
        }
    }
    return NULL;
}

int dict_put_absolute(Dict *_dict, char *key, int value, long hash, long at) {
    _dict->table[at].hash = hash;
    _dict->table[at].value = value;
    _dict->table[at].key = key;
    return 1;
}

int dict_put(Dict *_dict, char *key, int value) {
    DictNode *coll;
    if ((coll = dict_get(_dict, key)) != NULL) {
        // key exists, just update value
        coll->value = value;
        return 1;
    }
    unsigned long hash = string_hash32(key, _dict->size);
    // key does not exist, find a place
    if (_dict->strategy == LINEAR_PROBING) {
        for (long i = hash; i < _dict->size; i++) {
            if (_dict->table[i].key == NULL) { // found a place, insert here
                dict_put_absolute(_dict, key, value, hash, i);
                return 1;
            }
        }
    }
    return 0;
}

void print_dict(Dict *dict) {
    if (!dict) { printf("Dict is empty\n"); }
    for (int i = 0; i < dict->size; i++) {
        if (dict->table[i].key) {
            printf("-- %s(%lu):%d\n", dict->table[i].key,
                   dict->table[i].hash,
                   dict->table[i].value);
        }
    }
}

char *node_str(DictNode *node) {
    char *str = NULL;
    if (node) {
        asprintf(&str, "DictNode <key=%s, value=%d, hash=%lu>", node->key,
                node->value, node->hash);
        return str;
    }
    return NULL;
}


int main() {
    Dict *hash = dict();
    char *keys[] = {"one", "two", "three", "four", "five", "six", "seven",
                    "eight", "nine", "ten", "eleven", "twelve", "thirteen",
                    "fourteen", "fiveteen", "sixteen"};

    for (size_t i = 0; i < sizeof(keys)/sizeof(keys[0]); i++) {
        dict_put(hash, keys[i], i+1);
    }

    for (size_t i = 0; i < sizeof(keys)/sizeof(keys[0]); i++) {
        DictNode *tmp = dict_get(hash, keys[i]);
        if (tmp) {
            printf("%s\n", node_str(tmp));
        } else {
            printf("Key not found\n");
        }
    }

//    print_dict(hash);
}
