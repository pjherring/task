#include "tester.h"
#include "../src/list.h"

static void test_init();
static void test_object_at_index();
static void test_append();

SuiteT* Suite_list() {
    SuiteT *suite = Suite("list tests", &test_init, &test_object_at_index,
        &test_append, NULL);
    return suite;
}

static void test_init() {
    ListT *list = List(10, "one", "two", "three", NULL);
    assert(list != NULL);
    assert(list->values);
    assert_that(list->size == 3, "size is %d", list->size);
    _assert_strs_equal("one", list->values[0], "should be 'one'");
    _assert_strs_equal("two", list->values[1], "should be 'two'");
    _assert_strs_equal("three", list->values[2], "should be 'three'");
    assert(list->values[3] == NULL);
    assert_strs_equal(
        "three", (char * ) *list->last_value, 
        "should be 'three' but its %s", (char *) *list->last_value
    );
    _assert_that(list->capacity > 0, "allocated should be gt 0");
    _assert_that(list->capacity == 10, "capacity should be 10");

    list->destroy(list);
}

static void test_object_at_index() {
    ListT *list = List(10, "one", "two", "three", NULL);
    char * obj = list->object_at_index(list, 0);
    assert(strcmp(obj, "one") == 0);
    list->destroy(list);
}

static void test_append() {
    ListT *list = List(10, "bleh", NULL);
    assert_that(list->size == 1, "size is %d", list->size);
    list->append(list, "something");
    assert_that(list->size == 2, "size is %d", list->size);
    _assert_strs_equal(
        "bleh", list->object_at_index(list, 0), "should be bleh"
    );
    _assert_strs_equal("something", list->object_at_index(list, 1),
        "should be 'something'");
    assert_strs_equal(
        "something", *list->last_value,
        "incorrect last_value %s", *list->last_value
    );
    assert_that(list->capacity == 10, "incorrect capacity %d", list->capacity);

    list->destroy(list);

    list = List(2, "one", "two", NULL);
    assert_that(list->size == 2, "size is %d", list->size);
    list->append(list, "three");
    assert_that(list->size == 3, "size is %d", list->size);
    _assert_strs_equal(
        "three",
        list->object_at_index(list, 2),
        "should be 'three'");
    assert_strs_equal(
        "three", *list->last_value,
        "incorrect last_value %s", *list->last_value
    );
    assert_that(list->capacity == 3, "incorrect capacity %d", list->capacity);
}

