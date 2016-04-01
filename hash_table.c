/* Hash table implementation, should reproduce Python's dict. */

#import <stdlib.h>
#import <stdio.h>
#import <string.h>
#import <math.h>
#import "prlib.h"

typedef struct DictNode {
    unsigned long hash; // precomputed hash key
    char *key; // string key
    int value; // int value
} DictNode;

int PERTURB_SHIFT = 5;
float OCCUPANCY_RATIO = 0.66f;
typedef enum {LINEAR_PROBING, OPEN_ADDRESSING, SEPARATE_CHAINING} Strategy;

typedef struct Dict {
    DictNode *table;
    int size;
    Strategy strategy;
} Dict;

Dict *dict(int size) {
    Dict *new = (Dict *) malloc(sizeof(Dict));
    new->table = (DictNode *) malloc(sizeof(DictNode) * size);
    new->size = size;
    for (int i = 0; i < size; i++) {
        new->table[i].key = NULL;
    }
    new->strategy = OPEN_ADDRESSING;
    return new;
}

int dict_resize(Dict *);

DictNode *dict_get(Dict *_dict, char *key) {
    unsigned long hash = string_hash32(key, _dict->size);
    if (_dict->table[hash].key == NULL) {
        return NULL; // the key is not here and it is not because of collisions
    }

    if (!strcmp(_dict->table[hash].key, key)) { // key hit!
        return &_dict->table[hash];
    }

    /* The following cases are meant for when then key is not where we expect,
     this is, a collision occurred when inserting it. */
    switch(_dict->strategy) {
    case LINEAR_PROBING:
        for (int i = hash; i < _dict->size && _dict->table[i].key != NULL; i++) {
            if (!strcmp(_dict->table[i].key, key)) {
                return &_dict->table[i];
            }
        }
        break;
    case OPEN_ADDRESSING: {
        int i = hash, perturb = hash;
        while (_dict->table[i].key != NULL) {
            if (!strcmp(_dict->table[i].key, key)) {
                return &_dict->table[i];
            }
            // TODO: this should be moved to its own function.
            i = (5 * i) + 1 + perturb;
            perturb >>= PERTURB_SHIFT;
            i = i % _dict->size;
        }
        break;
    }

    case SEPARATE_CHAINING:
        return NULL;
        break;
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
    } else if (_dict->strategy == OPEN_ADDRESSING) {
        // open addressing implementation
        long i = hash, perturb = hash;
        while (_dict->table[i].key != NULL) {
            i = (5 * i) + 1 + perturb;
            perturb >>= PERTURB_SHIFT;
            i = i % _dict->size;
        }
        dict_put_absolute(_dict, key, value, hash, i);
        return 1;

    }
    dict_resize(_dict); // resize if needed
    return 0;
}

int dict_count_keys(Dict *_dict) {
    /* Counts amount of used keys from Dict. */
    int count = 0;
    for (int i = 0; i < _dict->size; i++) {
        if (_dict->table[i].key != NULL) {
            count++;
        }
    }
    return count;
}

char **dict_keys(Dict *_dict) {
    int count = dict_count_keys(_dict);
    char **keys = (char **) malloc(sizeof(char *) * count);
    for (int i = 0, j = 0 ; i < _dict->size; i++) {
        if (_dict->table[i].key != NULL) {
            asprintf((keys + j++), "%s", _dict->table[i].key);
        }
    }

    return keys;
}

int dict_resize(Dict *_dict) {
    // needs some improvement, as the dictionary is not being resized
    // or something. the algorithms work until an unescapable loop
    // triggers, as the dict is still the same size, the dict_put
    // method is not able to find a new place where to put the new
    // value... and it keeps looping thru a endless cycle.
    int keys_count = dict_count_keys(_dict);
    if ((float)keys_count / (float)_dict->size > 2.0/3.0) {
        printf("resizing is happening\n");
        Dict *new_dict = dict(_dict->size * 2);
        char **keys = dict_keys(_dict);
        for (int i = 0; i < keys_count; i++) {
            int value = dict_get(_dict, keys[i])->value;
            dict_put(new_dict, keys[i], value);
        }
        free(_dict->table);
        _dict->table = new_dict->table;
        free(keys);
    }
    return _dict->size;
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
    Dict *hash = dict(8);
    char *keys[] = {"one", "two", "three", "four", "five", "six" , "seven",
                    "eight", "nine"};/*, "ten", "eleven", "twelve", "thirteen",
                    "fourteen", "fiveteen", "sixteen"}; //*/

    for (size_t i = 0; i < sizeof(keys)/sizeof(keys[0]); i++) {
        dict_put(hash, keys[i], i+1);
    }

    int count = dict_count_keys(hash);
    printf("dict size: %d\n", count);

    char **_keys = dict_keys(hash);
    for (int i = 0; i < count; i++) {
        printf("key: %s\n", _keys[i]);
    }

    free(_keys);

//    print_dict(hash);
}
