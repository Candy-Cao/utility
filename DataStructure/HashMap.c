#include  <stdlib.h>
#include <stdbool.h>
#include "uthash.h"

typedef struct HashNode {
    int key;
    UT_hash_handle hh;
} HashNode;

HashNode *user = NULL;
void add_user(int ikey) {
    HashNode *s = (HashNode*)malloc(sizeof(HashNode));
    s->key = ikey;
    HASH_ADD_INT(user, key, s);
}
bool find_user(int ikey) {
    HashNode *s;
    HASH_FIND_INT(user, &ikey, s);
    return s != NULL;
}

void del_all_user() {
    HashNode *p, *tmp;
    HASH_ITER(hh, user, p, tmp) {
        HASH_DEL(user, p);
        free(p);
    }
}