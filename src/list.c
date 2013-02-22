#include "list.h"

ListT* List(int initial_capacity, ...) {
    ListT* self;
    int capacity;

    va_list args;
    void * arg;

    int values_idx;

    self = malloc(kListSize);
    capacity = initial_capacity;
    self->values = calloc(capacity, kVoidPointerSize);
    
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

    return self;
}


void * list_obj_at_idx(ListT* self, int idx) {
    assert(idx < self->size);
    return self->values[idx];
}

void list_destroy(ListT* list) {
    int value_idx;

    free(list->values);
    free(list);
}

void list_append(ListT* self, void * obj) {
    __assert_that(self != NULL);

    //do we need more capacity
    if (self->capacity == self->size) {
        int new_capacity;

        new_capacity = self->capacity * 2;
        self->values = realloc(self->values, kVoidPointerSize * new_capacity);
        self->capacity = new_capacity;
    }

    self->values[self->size] = obj;
    self->last_value = &self->values[self->size];
    self->size++;
}
