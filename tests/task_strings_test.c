#include "task_strings_test.h"

void test_substr() {
    char * str = "my super string";
    int len = 5;
    char * dest = malloc(sizeof(char) * len);
    substr(dest, str, 3, len);
    assert(strcmp("super", dest) == 0);
}

SuiteT* mk_task_strings_suite() {
    SuiteT *suite = newSuite(1, test_substr);
    return suite;
}

