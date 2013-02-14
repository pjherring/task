#include "../src/dict.h"
#include "suite.h"
#include "tester.h"
#include "../src/logger.h"

static void test_init();
static void test_add();
static void test_at();

SuiteT* Suite_dict() {
    SuiteT* suite = Suite("dict tests", &test_init, &test_add, &test_at, NULL);
    return suite;
}

static void test_add() {
    DictionaryT* dict = Dict();
    dict_add(dict, "key", "some value");
    assert_that(dict->size == 1, "size is %d", dict->size);
    dict_destroy(dict);
}

static void test_at() {
    DictionaryT* dict = Dict();
    dict_add(dict, "key", "value");
    assert_that(dict->size == 1, "size is %d", dict->size);
    char * value = dict_obj_at(dict, "key");
    assert_strs_equal("value", value, "incorrect, should be '%s' but is '%s'", "value", value);
    dict_destroy(dict);
}

static void test_init() {
    DictionaryT *instance = Dict();

    assert_that(instance != NULL, "instance is NULL", NULL);
    assert_that(instance->list != NULL, "instance->list is NULL", NULL);
    assert_that(instance->capacity == 100, "capacity is %d", instance->capacity);
    assert_that(instance->size == 0, "size is %d", instance->size);

    dict_destroy(instance);
}
