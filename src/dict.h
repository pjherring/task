#ifndef TK_DICT
#define TK_DICT 

#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>

#include "common.h"
#include "list.h"

typedef struct DictionaryT{
    ListT* keys;
    ListT* values;
    int size;
    //methods
    void (*destroy)(struct DictionaryT*);
    void * (*object_at_key)(struct DictionaryT*, void * key);
    int (*contains_key)(struct DictionaryT*, void*);
    int (*contains_value)(struct DictionaryT*, void*);

} DictionaryT;

DictionaryT* Dictionary(ListT* keys, ListT* values);

static size_t kDictSize = sizeof(DictionaryT);

#endif
