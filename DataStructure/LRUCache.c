#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10001
typedef struct _CacheNode {
    int key;
    int value;
    struct _CacheNode *next;
    struct _CacheNode *prev;
} CacheNode;

typedef struct _LRUCache {
    CacheNode head;
    CacheNode *tail;
    CacheNode *hashMap[MAX_SIZE];
    int size;
    int capacity;
} LRUCache;
void ListDeleteInner(CacheNode *p) {
    p->prev->next = p->next;
    p->next->prev = p->prev;
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache *obj = (LRUCache*)malloc(sizeof(LRUCache));
    memset(obj, 0, sizeof(LRUCache));
    obj->capacity = capacity;
    return obj;
}

int lRUCacheGet(LRUCache* obj, int key) {
    if (!obj->hashMap[key]) {
        return -1;
    }
    if (obj->hashMap[key] == obj->tail) {
        return obj->hashMap[key]->value;
    }
    CacheNode *p = obj->hashMap[key];
    ListDeleteInner(p);
    obj->tail->next = p;
    p->prev = obj->tail;
    obj->tail = p;
    return p->value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    CacheNode *pNode;
    int ret = lRUCacheGet(obj, key);
    if (ret == -1) {
        pNode = (CacheNode*)malloc(sizeof(CacheNode));
        pNode->key = key;
        pNode->value = value;
        pNode->next = NULL;
        obj->hashMap[key] = pNode;
        if (obj->tail == NULL) {
            obj->head.next = pNode;
            pNode->prev = &obj->head;
        }
        else {
            obj->tail->next = pNode;
            pNode->prev = obj->tail;
        }
        obj->tail = pNode;
        obj->size++;
    }
    if (obj->size > obj->capacity) {
        pNode = obj->head.next;
        obj->hashMap[pNode->key] = NULL;
        ListDeleteInner(pNode);
        free(pNode);
        obj->size--;
    }
    if (ret != -1) {
        obj->tail->value = value;
    }
    return ;
}

void lRUCacheFree(LRUCache* obj) {
    CacheNode *pNode = obj->tail;
    while (obj->size) {
        obj->tail = obj->tail->prev;
        free(pNode);
        pNode = obj->tail;
        obj->size--;
    }
    free(obj);
}