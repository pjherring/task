#include "../src/dict.h"
#include "suite.h"
#include "tester.h"
#include "../src/logger.h"

static void test_init();
static void test_object_at_key();

SuiteT* Suite_dict() {
    SuiteT* suite = Suite("dict tests", &test_init, &test_object_at_key, NULL);
    return suite;
}

static void test_object_at_key() {
    DictionaryT *dict = Dictionary(List(1, "key", NULL), List(1, "val", NULL));
    dict->destroy(dict);
}

static void test_init() {
    DictionaryT *instance = Dictionary(List(2, "key", "key2", NULL), List(2, "val", "val2", NULL));
    assert(instance != NULL);
    assert(instance->keys != NULL);
    assert(instance->values != NULL);
    instance->destroy(instance);
}
