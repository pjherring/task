#include "dict.h"

static uint32_t hash(char * key, int capacity);

static const int initCapacity = 100;

DictionaryT* Dict() {

    DictionaryT *self = malloc(kDictSize);
    self->list = calloc(initCapacity, kNodeSize);
    self->capacity = initCapacity;
    self->size = 0;

    return self;
}


void dict_add(DictionaryT* self, char * key, void * value) {
    uint32_t hash_value = hash(key, self->capacity);

    if (self->list[hash_value]) {
        free(self->list[hash_value]);
    }

    DictionaryNodeT *node = malloc(kNodeSize);
    node->key = key;
    node->value = value;
    node->hash = hash_value;

    self->list[hash_value] = node;
    self->size++;
}


void dict_destroy(DictionaryT* self) {
    DictionaryNodeT *node;
    int i;

    for (i = 0; i < self->size; i++) {
        free(self->list[i]);
    }

    free(self);
}


void* dict_obj_at(DictionaryT* self, char * key) {

    uint32_t hash_value = hash(key, self->capacity);

    if (!self->list[hash_value]) {
        return NULL;
    }

    DictionaryNodeT *node = self->list[hash_value];
    return node->value;
}

static uint32_t hash(char * key, int capacity) {

    uint32_t hash_value;

    for (hash_value = 0; *key != '\0'; key++) {
        hash_value = *key + 31 * hash_value;
    }

    return hash_value % capacity;
}
