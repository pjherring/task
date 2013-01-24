#include "CuTest.h"
#include "../src/command.h"

void test_new_command(CuTest *tc) {
	Command *command = NewCommand();
	CuAssertPtrNotNullMsg(tc, "the command pointer is null", command);
}

CuSuite* command_suite() {
	CuSuite *suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, test_new_command);
	return suite;
}

