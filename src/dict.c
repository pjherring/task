#include "dict.h"

static void destroy(DictionaryT* self);

DictionaryT* Dictionary(ListT* keys, ListT* values) {
    _assert_that(keys != NULL && values != NULL, "keys and values are required");
    _assert_that(keys->size == values->size, "keys and values must have same size");
    assert(keys->size == values->size);

    DictionaryT *instance = malloc(kDictSize);
    instance->keys = keys;
    instance->values = values;
    instance->size = keys->size;
    instance->destroy = &destroy;

    return instance;
}

static void destroy(DictionaryT* self) {
    assert(self && self->keys && self->values);
    free(self->keys);
    free(self->values);
    free(self);
}
