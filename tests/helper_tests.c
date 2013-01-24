#include "CuTest.h"
#include "../src/helper.h"
#include <stdlib.h>

void test_lowercase_str(CuTest *tc) {
    char *my_str = "Test ThIS is my string";
    char *lowercase_my_str = lowercase_str(my_str);
    CuAssertStrEquals(tc, "test this is my string", lowercase_my_str);
}

CuSuite* helper_get_suite() {
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_lowercase_str);
    return suite;
}
