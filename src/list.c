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

int list_index_of(ListT* self, void* obj) {
    int value_idx;

    for (value_idx = 0; value_idx < self->size && self->values[value_idx] != obj; value_idx++) ;

    return value_idx;
}


void* list_pop(ListT* self) {
    void* to_return;

    if (self->size > 0) {
        to_return = *self->last_value;
        self->values[self->size - 1] = NULL;
        self->size--;
        self->last_value = self->size == 0 ? NULL : &self->values[self->size - 1];

        return to_return;
    }

    return NULL;
}


void list_empty(ListT* self, int do_free) {
    void* popped;

    while ((popped = list_pop(self)) != NULL) {
        if (do_free) {
            free(popped);
        }
    }
}


void* list_iterate(ListT* self) {
    static ListT* current = NULL;
    static int list_idx = -1;

    assert(self != NULL || current != NULL);

    if (self != NULL && self != current) {
        current = self;
        list_idx = 0;
    }

    assert(current != NULL);

    if (list_idx == current->size) {
        list_idx = -1;
        current = NULL;
        return NULL;
    } else {
        return current->values[list_idx++];
    }

}


void list_copy(ListT* dest, ListT* source) {
    assert(dest != NULL && source != NULL);

    void* item;

    while ( (item = list_iterate(source)) != NULL) {
        list_append(dest, item);
    }
}
