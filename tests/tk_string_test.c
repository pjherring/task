#include "../src/tk_string.h"
#include "suite.h"
#include "tester.h"
#include "../src/logger.h"

static void test_substr() {
    char * str = "my super string";
    char* dest = substr(str, 3, 5);
    assert_strs_equal("super", dest, "'%s' does not equal 'super'", dest);
    free(dest);
}

void test_strsplit() {

    char * str = "this is str";
    char * const delim = " ";
    char** parts;

    parts = strsplit(str, delim);

    assertStrEqual("this", parts[0]);
    assertStrEqual("is", parts[1]);
    assertStrEqual("str", parts[2]);
    free(parts);
}

void test_stroccur() {
    char * const str = "this is my big long string";
    char * const delim = "s";
    int occurance = stroccur(str, delim);
    assert(occurance == 3);
}

void test_split_arr_size() {
    char * const str = "this is a string";
    char * const delim = " ";
    size_t arr_size = split_arr_size(str, delim);
    assert(arr_size == (sizeof(char *) * 5));
}

void test_strlower() {
    char * const str = "ThIs 2 is My STRing!";
    char * const to_test = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(to_test, str);
    strlower(to_test);
    assertStrEqual("this 2 is my string!", to_test);
    free(to_test);
}

SuiteT* Suite_tk_string() {
    SuiteT* suite = 
        Suite(
            "tk_string", &test_substr, &test_strsplit, &test_stroccur,
            &test_split_arr_size, &test_strlower, NULL
        );
    return suite;
}

