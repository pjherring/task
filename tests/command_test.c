#include "tester.h"
#include "../src/command.h"

static void test_init();

SuiteT* Suite_command() {
    SuiteT *suite = Suite("command tests", &test_init, NULL);
    return suite;
}

static void test_init() {
    char * text = "task Write this unit test";
    CommandT *command = Command(text);
    assert(command->type == CommandTypeTask);
    assert(command->destroy != NULL);
    assert(command->text != NULL);
    assert(strcmp(command->text, text) == 0);
    assert(command->type == CommandTypeTask);
    assert(command->is_open == YES);
    assert(command->notes != NULL);
    command->destroy(command);
}
