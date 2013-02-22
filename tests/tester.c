#include "tester.h"

SuiteT** get_suites();

int main() {

    SuiteT** suites = get_suites();
    int suite_idx = 0;
    int suite_result = 0;
    SuiteT* current_suite;

    while ( (current_suite = suites[suite_idx++]) != NULL) {
        printf("\nTesting %s\n", current_suite->name);
        int failure_count = suite_run(current_suite);

        if (failure_count > 0) {
            printf("Failures!\n");
        }

        suite_result += failure_count;
        suite_destroy(current_suite);
    }

    free(suites);
    if (suite_result == 0) {
        printf("Success!\n");
        return 0;
    }

    return 1;
}

SuiteT** get_suites() {
    SuiteT** suites = malloc(sizeof(SuiteT *) * 6);
    suites[0] = Suite_tk_string();
    suites[1] = Suite_list();
    suites[2] = Suite_dict();
    suites[3] = Suite_task();
    suites[4] = Suite_execute();
    suites[5] = NULL;

    return suites;
}

char* make_str(const char* str) {
    size_t size;
    char* new_str;
    new_str = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(new_str, str);
    return new_str;
}
