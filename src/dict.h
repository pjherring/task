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
} DictionaryT;


static size_t kDictSize = sizeof(DictionaryT);
static size_t kNodeSize = sizeof(DictionaryNodeT);

/*
 * Constructor for dictionary
 */
DictionaryT* Dict();

/*
 * Destroy the dictionary
 */
void dict_destroy(DictionaryT*);
/*
 * Add a key val pair
 */
void dict_add(DictionaryT*, char*, void*);
/*
 * Fetch object at key
 */
void* dict_obj_at(DictionaryT*, char*);

#endif
