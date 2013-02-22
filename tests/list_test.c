#include "tester.h"
#include "../src/list.h"

static void test_init();
static void test_obj_at_idx();
static void test_append();
static void test_index_of();

SuiteT* Suite_list() {
    SuiteT *suite = Suite("list tests", &test_init, &test_obj_at_idx,
        &test_append, &test_index_of, NULL);
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

    list_destroy(list);
}

static void test_obj_at_idx() {
    ListT *list = List(10, "one", "two", "three", NULL);
    char * obj = list_obj_at_idx(list, 0);
    assert(strcmp(obj, "one") == 0);
    list_destroy(list);
}

static void test_append() {

    ListT *list = List(10, "bleh", NULL);
    assert_that(list->size == 1, "size is %d", list->size);
    list_append(list, "something");
    assert_that(list->size == 2, "size is %d", list->size);
    _assert_strs_equal(
        "bleh", list_obj_at_idx(list, 0), "should be bleh"
    );
    _assert_strs_equal("something", list_obj_at_idx(list, 1),
        "should be 'something'");
    assert_strs_equal(
        "something", (char* )*list->last_value,
        "incorrect last_value %s", (char*) *list->last_value
    );
    assert_that(list->capacity == 10, "incorrect capacity %d", list->capacity);

    list_destroy(list);

    list = List(2, "one", "two", NULL);
    assert_that(list->size == 2, "size is %d", list->size);
    assert_that(list->capacity == 2, "capacity is %d", list->capacity);

    list_append(list, "three");
    assert_that(list->size == 3, "size is %d", list->size);
    assert_that(list->capacity == 4, "capacity is %d", list->capacity);
    _assert_strs_equal(
        "three",
        list_obj_at_idx(list, 2),
        "should be 'three'");
    assert_strs_equal(
        "three", (char*) *list->last_value,
        "incorrect last_value %s", (char*) *list->last_value
    );
    assert_that(list->capacity == 4, "incorrect capacity %d", list->capacity);
}


static void test_index_of() {
    char* one = "one";
    char* two = "two";
    char* three= "three";
    ListT* list = List(10, NULL);
    list_append(list, one);
    list_append(list, two);
    list_append(list, three);

    assert_that(0 == list_index_of(list, one), "incorrect index %d", list_index_of(list, one));
    assert_that(1 == list_index_of(list, two), "incorrect index %d", list_index_of(list, two));
    assert_that(2 == list_index_of(list, three), "incorrect index %d", list_index_of(list, three));
}
