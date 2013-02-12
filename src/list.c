#include "list.h"

static void* list_object_at_index(ListT* self, int idx);;
static void destroy(ListT* self);
static void append(ListT*, void*);

ListT* List(int initial_capacity, ...) {
    ListT* self;
    int capacity;

    va_list args;
    void * arg;

    int values_idx;

    self = malloc(kListSize);
    capacity = initial_capacity;
    self->values = malloc(kVoidPointerSize * capacity);
    
    va_start(args, initial_capacity);

    for (values_idx = 0; (arg = va_arg(args, void*)) != NULL; values_idx++) {

        self->values[values_idx] = arg;

        if (values_idx == capacity) {
            capacity += initial_capacity;
            self->values = realloc(
                self->values, kVoidPointerSize * capacity
            );
        }

    }

    //we need to NULL terminate this list, but we need to make sure we have
    //enough memory to do so
    if (values_idx == capacity) {
        self->values = 
            realloc(self->values, kVoidPointerSize * (capacity + 1));
    }
    
    self->values[values_idx] = NULL;
    self->capacity = capacity;
    self->size = values_idx;

    if (self->size > 0) {
        self->last_value = self->values + (self->size - 1);
    }
    self->destroy = &destroy;
    self->object_at_index = &list_object_at_index;
    self->append = &append;

    return self;
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

    //do we need more capacity
    if (self->capacity == self->size) {
        self->capacity *= 1.5;
        self->values = realloc(self->values, kVoidPointerSize * self->capacity);
    }

    self->values[self->size] = obj;
    self->size++;
    self->last_value++;
}
