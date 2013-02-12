#include "assertions.h"

/*  */
char * create_error_string(char * fmt, ...);

void assert_not_null(void * obj, char * const fmt, ...) {
    va_list args;
    va_start(args, fmt);

    assert_that(obj != NULL, fmt, args);
}

void assert_that(int expression, char * fmt, ...) {
    if (!expression) {
        va_list args;
        va_start(args, fmt);

        char * error_str = create_error_string(fmt, args);
        printf("%s", error_str);
        abort(void);
    }
}

static char const * const kErrorFmt = "File: %s (Line %d), %s";
static size_t kErrorFmtSize = sizeof(kErrorFmt);

char * create_error_string(char * const fmt, ...) {

    va_list args;
    va_start(args, fmt);

    //construct complete fmt string, which includes file name and line number i.e. 'File: main.c (Line 5) %s'
    size_t complete_fmt_size = sizeof(fmt) + kErrorFmtSize + sizeof(__FILE__) + sizeof(int);
    char * const complete_fmt_str = malloc(complete_fmt_size);
    sprintf(complete_fmt_str, kErrorFmt, __FILE__, __LINE__, fmt);

    //now construct the string with the varargs passed in
    size_t error_str_size = complete_fmt_size + sizeof(args);
    char * error_str = malloc(error_str_size);
    sprintf(error_str, complete_fmt_str, args);

    return error_str;
}
*/

