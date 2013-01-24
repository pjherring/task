#include "CuTest.h"
#include "../src/command.h"

void test_new_command(CuTest *tc) {
}

CuSuite* Command_GetSuite() {
	CuSuite *suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, test_new_command);
	return suite;
}

