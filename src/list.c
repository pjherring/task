#include "list.h"

static void* list_object_at_index(ListT* self, int idx);;
static void destroy(ListT* self);
static void append(ListT*, void*);

ListT* List(int begin_size, ...) {

    ListT* instance = malloc(kListSize);
    int max = begin_size;

    instance->values = malloc(sizeof(void*) * max);

    va_list args;
    va_start(args, begin_size);
    void * arg;
    int values_idx = 0;

    while ((arg = va_arg(args, void*)) != NULL) {
        instance->values[values_idx++] = arg;

        if (values_idx == max) {
            max += begin_size;
            instance->values = realloc(instance->values, sizeof(void*) * max);
        }

        if (values_idx + 1 == max) {
            instance->last_value = &arg;
        }

    }

    if (values_idx == max) {
        instance->values = realloc(instance->values, sizeof(void*) * (max + 1));
    }

    instance->values[values_idx] = NULL;
    instance->size = values_idx;
    instance->destroy = &destroy;
    instance->object_at_index = &list_object_at_index;
    instance->append = &append;

    return instance;
}


static void * list_object_at_index(ListT* self, int idx) {
    assert(idx < self->size);
    return self->values[idx];
}

static void destroy(ListT* list) {
    free(list->values);
    free(list);
}

static void append(ListT* self, void * obj) {
    __assert_that(self != NULL);
}
