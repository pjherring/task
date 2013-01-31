#ifndef TASK_ASSERT
#define TASK_ASSERT

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

void assert_not_null(void * obj, char * const fmt, ...);
void assert_that(int expression, char * const fmt, ...);

#define assert_that(expression, fmt, ...) \
    if (!expression) { \
        printf(fmt, ##__VA_ARGS__); \
        assert(expression); \
    } 
        //printf("File: %s, Line: %d, %s", __FILE__, __LINE__, fmt, __VA_ARGS__); \
        //assert(false); 

#endif


