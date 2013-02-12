
#ifndef TK_SKECTH
#define TK_SKETCH

#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

#define PRINT_STACK(size) do { \
    void *arr[size]; \
    print_stack(arr, size); \
} while(0);

void print_stack(void ** arr, int stack_size);

#endif
