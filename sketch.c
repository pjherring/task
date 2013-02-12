#include "sketch.h"

int main() {
    PRINT_STACK(10);
}

void print_stack(void ** arr, int stack_size) {
    size_t i;
    char **strings;
    size_t size;

    size = backtrace(arr, stack_size);
    strings = backtrace_symbols(arr, size);

    printf("Obtained %zd stack frames.\n", size);

    for (i = 0; i < size; i++) {
        printf("%s\n", strings[i]);
        char syscom[256];
        sprintf(syscom, "atos %p -e sighandler", strings[i]);
        system(syscom);
    }

    free(strings);
}
