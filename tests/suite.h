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
#include <assert.h>
#include "../src/common.h"

typedef void(*test_case_fp)(void);

typedef struct SuiteT {
    char * name;
    test_case_fp *tests;
} SuiteT;

static size_t suite_size = sizeof(SuiteT);

SuiteT * Suite(char * const name, ...);

int suite_run(SuiteT*);
void suite_destroy(SuiteT*);

#endif
