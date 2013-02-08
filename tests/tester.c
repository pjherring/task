#include "tester.h"

SuiteT** get_suites();

int main() {

    SuiteT** suites = get_suites();
    int suite_idx = 0;
    int suite_result = 0;
    SuiteT* current_suite;

    while ( (current_suite = suites[suite_idx++]) != NULL) {
        printf("Testing %s\n", current_suite->name);
        int failure_count = current_suite->run(current_suite);

        if (failure_count > 0) {
            printf("Failures!\n");
        }

        suite_result += failure_count;
        current_suite->destroy(current_suite);
    }

    free(suites);
    if (suite_result == 0) {
        printf("Success!\n");
        return 0;
    }

    return 1;
}

SuiteT** get_suites() {
    SuiteT** suites = malloc(sizeof(SuiteT *) * 2);
    suites[0] = Suite_tk_string();
    suites[1] = NULL;

    return suites;
}
