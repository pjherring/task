#ifndef TK_COMMON
#define TK_COMMON 

#include <stdlib.h>
#include <stdio.h>
#include <execinfo.h>
#include <stdarg.h>
#include <assert.h>
#include <signal.h>

#include "assertions.h"
#include "logger.h"

#define PRINT_STACK(size) do { \
    void *arr[size]; \
    print_stack(arr, size); \
} while(0);

#define YES 1
#define NO 0

void print_stack(void ** arr, int stack_size);

extern size_t kVoidPointerSize;

#endif
