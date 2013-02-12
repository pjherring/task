#include "suite.h"

static int run_local(SuiteT *suite);
static void destroy(SuiteT *suite);

static const int kTestsDefaultSize = 10;

SuiteT* Suite(char * const name, ...) {
    SuiteT *instance = malloc(suite_size);

    instance->run = &run_local;
    instance->destroy = &destroy;
    instance->name = name;

    va_list ap;
    va_start(ap, name);

    int current_size = kTestsDefaultSize;
    instance->tests = malloc(sizeof(test_case_fp) * current_size);
    test_case_fp test_case;
    int test_case_idx = 0;

    do {
        test_case = va_arg(ap, test_case_fp);
        instance->tests[test_case_idx++] = test_case;

        if (test_case_idx == current_size) {
            current_size += kTestsDefaultSize;
            instance->tests = realloc(
                instance->tests,
                sizeof(test_case_fp) * current_size
            );
        }

    } while (test_case != NULL);

    return instance;
}

static int run_local(SuiteT *suite) {

    pid_t pid;
    int test_idx = 0;
    int failure_count = 0;
    test_case_fp test_case;

    while ( (test_case = suite->tests[test_idx++]) != NULL) {

        pid = fork();

        if (pid == 0) {
            //child
            test_case();
            printf(".");
            exit(0);
        } else {
            int status;
            waitpid(pid, &status, 0);

            if (!WIFEXITED(status)) {
                printf("Error code %d\n", status);
                printf("F");
                failure_count++;
            } 
        }
    }

    printf("\n");

    return failure_count;
}

static void destroy(SuiteT *suite) {
    free(suite->tests);
    free(suite);
}
