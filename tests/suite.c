#include "suite.h"

int run_local(SuiteT *suite);
void destroy_local(SuiteT *suite);

SuiteT* Suite(int test_count, ...) {
    SuiteT *instance = malloc(suite_size);
    instance->test_count = test_count;

    va_list ap;
    va_start(ap, test_count);

    instance->tests = malloc(sizeof(test_case_fp) * test_count);

    int test_case_idx;
    for (test_case_idx = 0; test_case_idx < test_count; test_case_idx++) {
        test_case_fp test_case = va_arg(ap, test_case_fp);
        instance->tests[test_case_idx] = test_case;
    }

    instance->run = ^int() { run_local(instance); };
    instance->destroy = ^void() { destroy_local(instance); };

    return instance;
}

int run_local(SuiteT *suite) {

    pid_t pid;
    int test_idx;

    for (test_idx = 0; test_idx < suite->test_count; test_idx++) {

        pid = fork();
        printf("process %d\n", pid);

        if (pid == 0) {
            //child
            printf("child\n");
            sleep(1);
            test_case_fp test_case = *suite->tests[test_idx];
            test_case();
        } else {
            printf("parent\n");
            int status = 0;
            waitpid(pid, &status, 0);
            printf("status: %d\n", WEXITSTATUS(status));
        }
    }

    return 1;
}

void destroy_local(SuiteT *suite) {
    free(suite->tests);
    free(suite);
}
