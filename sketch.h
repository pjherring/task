#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <Block.h>

#ifndef TK_SUITE
#define TK_SUITE

typedef void(*test_case_fp)(void);

typedef struct SuiteT {
    int count;
    int (^run)(void);
    void (^destroy)(void);
    test_case_fp *tests;
} SuiteT;

#endif
