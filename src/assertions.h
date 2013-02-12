#ifndef TASK_ASSERT
#define TASK_ASSERT

#include "common.h"
#include <stdbool.h>

void assert_not_null(void * obj, char * const fmt, ...);
void assert_that(int expression, char * const fmt, ...);

#define assert_strs_equal(a, b, fmt, ...) \
    assert_that(strcmp(a, b) == 0, fmt, ##__VA_ARGS__)
#define _assert_strs_equal(a, b, fmt) assert_that(strcmp(a, b) == 0, fmt, NULL)
#define _assert_that(expression, fmt) assert_that(expression, fmt, NULL);
#define __assert_that(expression) assert_that(expression, "Assertion failed", NULL);
#define assert_that(expression, fmt, ...) \
    if (!(expression)) { \
        printf("\n"); \
        printf(fmt, ##__VA_ARGS__); \
        printf("\n"); \
        PRINT_STACK(10); \
        assert(expression); \
    } 

#endif


