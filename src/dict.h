#ifndef TK_DICT
#define TK_DICT 

#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

#include "common.h"
#include "list.h"

typedef struct DictionaryNodeT {
    char * key;
    void * value;
    uint32_t hash;
    struct DictionaryNodeT  *next;
} DictionaryNodeT;

typedef struct DictionaryT{
    DictionaryNodeT **list;
    int capacity;
    int size;
    /*
     * Destroy this struct. Will free keys, values, and the struct
     */
    void (*destroy)(struct DictionaryT*);
    /*
     * Get the object that is matched with @param key
     */
    void (*add)(struct DictionaryT*, char * key, void * value);
    /*
     * Find object at key
     */
    void* (*at)(struct DictionaryT*, char * key);

} DictionaryT;

DictionaryT* Dictionary();

static size_t kDictSize = sizeof(DictionaryT);
static size_t kNodeSize = sizeof(DictionaryNodeT);

#endif
