#include "sketch.h"

int run(SuiteT *suite);
void destroy(SuiteT *suite);
void test_something();
void test_something_else();

int main() {


    SuiteT *a_suite = malloc(sizeof(SuiteT));
    SuiteT *b_suite = malloc(sizeof(SuiteT));

    a_suite->run = ^int(void) { run(a_suite); };
    a_suite->destroy = ^void(void) { destroy(a_suite); };

    a_suite->tests = malloc(sizeof(test_case_fp) * 1);
    a_suite->tests[0] = &test_something;
    a_suite->count = 1;

    a_suite->run();
    a_suite->destroy();
}

int run(SuiteT *suite) {
    int test_idx = 0;

    pid_t pid;

    for (test_idx; test_idx < suite->count; test_idx++) {

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

void destroy(SuiteT *suite) {
    free(suite->tests);
    free(suite);
}

void test_something() {
    printf("Test case\n");
    assert(1 == 0);
}

void test_something_else() {
    printf("TESTING SOMETHING ELSE");
}
