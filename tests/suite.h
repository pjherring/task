#ifndef TK_SUITE
#define TK_SUITE 

//inclue
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <Block.h>

typedef void(*test_case_fp)(void);

typedef struct SuiteT {
    int test_count;
    int (^run)();
    void (^destroy)();
    test_case_fp *tests;
} SuiteT;

static size_t suite_size = sizeof(SuiteT);

SuiteT * Suite(int test_count, ...);

#endif
