#include "CuTest.h"
#include "../src/command.h"

void test_new_command(CuTest *tc) {
	CommandT *command = NewCommand("task to do something");
	CuAssertPtrNotNullMsg(tc, "the command pointer is null", command);
    CuAssertIntEquals_Msg(tc, "the command type should be task", CommandTypeAddTask, command->type);
}

CuSuite* command_suite() {
	CuSuite *suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, test_new_command);
	return suite;
}

