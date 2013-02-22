#include "tester.h"
#include "../src/task.h"

static void test_init();
static void test_add_note();
static void test_complete();
static void test_add_child();
static void test_read_write();

SuiteT* Suite_task() {
    SuiteT *suite = Suite("task tests", &test_init, &test_add_note, 
        &test_complete, &test_add_child, &test_read_write, NULL);
    return suite;
}

static void test_init() {
    char * text = make_str("task Write this unit test");

    TaskT *task = Task(text);

    assert(task->text != NULL);
    assert(strcmp(task->text, text) == 0);
    assert(task->children != NULL);
    assert(task->is_complete == NO);
    assert(task->notes != NULL);

    task_destroy(task);
}

static void test_add_note() {
    TaskT *task = Task(make_str("task write this unit test"));

    task_add_note(task, make_str("this is hard"));
    ListT* notes = task->notes;
    assert_that(notes->size == 1, "incorrect size of notes %d", notes->size);
    assert_strs_equal(
        "this is hard", list_obj_at_idx(notes, 0),
        "actual '%s'", (char*) list_obj_at_idx(notes, 0)
    );

    task_destroy(task);
}

static void test_complete() {
    TaskT *task = Task(make_str("write this unit test"));
    assert_that(task->is_complete == NO, "is complete is %d", task->is_complete);
    task_complete(task);
    assert_that(task->is_complete == YES, "is complete is %d", task->is_complete);
    task_destroy(task);
}

static void test_add_child() {
    TaskT* parent = Task(make_str("write this unit test"));
    TaskT* child = Task(make_str("how do I write unit tests?"));

    assert(parent->children != NULL);
    task_add_child(parent, child);
    ListT *children = parent->children;
    assert(children != NULL);
    assert(children->size == 1);
    TaskT* _child = list_obj_at_idx(children, 0);
    assert(child == _child);

    task_destroy(parent);
    task_destroy(child);
}

static void test_read_write() {
    TaskT *task, *child, *task_2;
    char * const filename = "task.js";

    ListT* tasks;
    ListT* read_tasks;

    task = Task(make_str("write this unit test"));
    task_add_note(task, make_str("a note"));

    child = Task(make_str("write a method"));
    task_add_note(child, make_str("child note"));

    task_add_child(task, child);

    task_2 = Task(make_str("write this class"));
    task_2->is_complete = YES;
    tasks = List(10, task, task_2, NULL);

    task_write(tasks, filename);
    
    read_tasks = task_read(filename);
    assert_that(read_tasks != NULL, "read_tasks is null");
    assert_that(read_tasks->size == 2, "incorrect size: %d", read_tasks->size);

    TaskT *read_task_one, *read_task_two, *read_child;
    read_task_one = list_obj_at_idx(read_tasks, 0);
    read_task_two = list_obj_at_idx(read_tasks, 1);
    
    assert_strs_equal(read_task_one->text, "write this unit test", 
        "strings not equal");
    assert_that(read_task_one->is_complete == NO, "should be NO");
    assert_strs_equal(
        "a note", (char*) list_obj_at_idx(read_task_one->notes, 0),
        "incorrect child note"
    );

    assert_strs_equal(read_task_two->text, "write this class",
        "incorrect text for read_task_two: %s", read_task_two->text);
    assert_that(read_task_two->is_complete == YES, "should be NO");
    assert_that(read_task_one->children->size == 1, 
        "incorrect size for read_task_one->children: %d", 
        read_task_one->children->size);

    read_child = list_obj_at_idx(read_task_one->children, 0);
    assert_that(read_child != NULL, "read_child is NULL");
    assert_strs_equal(read_child->text, "write a method",
        "incorrect text for read_child: %s", read_child->text);
    assert_that(read_child->notes->size == 1, 
        "incorrect size for read_child->notes: %d", read_child->notes->size);
    assert_strs_equal(
        "child note", (char*) list_obj_at_idx(read_child->notes, 0),
        "incorrect child note"
    );


    task_destroy(task);
    task_destroy(child);
    task_destroy(task_2);
}

