#include "CuTest.h"
#include "../src/task_io.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void test_get_user_input(CuTest *tc) {
	printf("Type something and hit return (testing user input): ");
	char * user_input = get_user_input(-1);
	CuAssertPtrNotNullMsg(tc, "user input pointer is null", user_input);
	int equal_strings = strcmp("", user_input);
	CuAssertTrue(tc, equal_strings != 0);
}

CuSuite* task_io_suite() {
	CuSuite *suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, test_get_user_input);
	return suite;
}

