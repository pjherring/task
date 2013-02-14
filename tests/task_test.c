#include "tester.h"
#include "../src/task.h"

static void test_init();
static void test_add_note();
static void test_complete();
static void test_add_child();
static void test_write();

SuiteT* Suite_task() {
    SuiteT *suite = Suite("task tests", &test_init, &test_add_note, 
        &test_complete, &test_add_child, &test_write, NULL);
    return suite;
}

static void test_init() {
    char * text = "task Write this unit test";

    TaskT *task = Task(text);

    assert(task->text != NULL);
    assert(strcmp(task->text, text) == 0);
    assert(task->children != NULL);
    assert(task->is_complete == NO);
    assert(task->notes != NULL);

    task_destroy(task);
}

static void test_add_note() {
    TaskT *task = Task("task write this unit test");

    task_add_note(task, "this is hard");
    ListT* notes = task->notes;
    assert_that(notes->size == 1, "incorrect size of notes %d", notes->size);
    assert_strs_equal(
        "this is hard", list_obj_at_idx(notes, 0),
        "actual '%s'", list_obj_at_idx(notes, 0)
    );

    task_destroy(task);
}

static void test_complete() {
    TaskT *task = Task("write this unit test");
    assert_that(task->is_complete == NO, "is complete is %d", task->is_complete);
    task_complete(task);
    assert_that(task->is_complete == YES, "is complete is %d", task->is_complete);
    task_destroy(task);
}

static void test_add_child() {
    TaskT* parent = Task("write this unit test");
    TaskT* child = Task("how do I write unit tests?");

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

static void test_write() {
    FILE *write_to;
    TaskT *task, *child, *task_2;

    write_to = fopen("task.js", "w");

    task = Task("write this unit test");
    task_add_note(task, "a note");

    child = Task("write a method");
    task_add_note(child, "child note");

    task_add_child(task, child);

    task_2 = Task("write this class");
    ListT* tasks = List(10, task, task_2);

    task_write(tasks, write_to);

    fclose(write_to);
    task_destroy(task);
    task_destroy(child);
    task_destroy(task_2);

}
