#include "tester.h"

int main() {
    SuiteT * task_string_suite = mk_task_strings_suite();
    int status = task_string_suite->run_suite(task_string_suite);

    if (status > 0) {
        printf("Failures");
    }

    return status;
}
