#include "tester.h"
#include "../src/execute.h"

static void test_new();
static void test_show();
static void test_finish();
static void test_add_note();
static void test_execute_child();

SuiteT* Suite_execute() {
    return Suite("Execute Tests", &test_new, &test_show, &test_finish, &test_add_note, &test_execute_child, NULL);
}

static void test_new() {
    ListT* tasks;
    char* command;
    TaskT* current;

    tasks = List(10, NULL);
    command = "n some";

    execute_new(command, tasks, &current);
    assert_that(current != NULL, "current is null", NULL);
    assert_strs_equal(current->text, "some", "incorrect text '%s'", current->text);
    assert_that(tasks->size == 1, "incorrect size %d", tasks->size);
    _assert_that(list_obj_at_idx(tasks, 0) == current, "current is incorrect.");

    list_destroy(tasks);
    task_destroy(current);
}

static void test_show() {
    ListT* tasks;
    TaskT* current;

    current = Task("some task");
    tasks = List(10, current, NULL);

    execute_show(NULL, tasks, &current);
    list_destroy(tasks);
    task_destroy(current);
}

static void test_finish() {
    ListT* tasks;
    TaskT *three, *one, *two, *current;

    one = Task("some task");
    current = one;
    tasks = List(10, one, NULL);

    execute_finish(NULL, tasks, &current);
    assert_that(current == NULL, "one should be null", NULL);
    assert_that(tasks->size == 1, "incorrect tasks size %d", tasks->size);
    assert_that(((TaskT*) list_obj_at_idx(tasks, 0))->is_complete == YES, "Should be complete", NULL);

    two = Task("two");
    three = Task("three");

    list_append(tasks, two);
    list_append(tasks, three);

    current = three;
    execute_finish(NULL, tasks, &current);
    _assert_that(current != NULL, "current should not be NULL");
    assert_that(current == two, "current should be two but is %p", current);
    _assert_that(three->is_complete == YES, "should be YES");

    task_destroy(one);
    task_destroy(two);
    task_destroy(three);
    list_destroy(tasks);
}

static void test_add_note() {
    TaskT* task;
    ListT* tasks;
    
    task = Task("this is a task");
    tasks = List(10, task, NULL);

    execute_add_note(make_str("a this is a note"), tasks, &task);
    _assert_that(task->notes != NULL, "notes should not be NULL");
    assert_that(task->notes->size == 1, "incorrect notes size: %d", task->notes->size);
    assert_strs_equal((char*) list_obj_at_idx(task->notes, 0), "this is a note", "incorrect str: '%s'", (char*) list_obj_at_idx(task->notes, 0));
    task_destroy(task);
}

static void test_execute_child() {
    TaskT *task, *current;
    ListT* tasks;

    task = Task("parent");
    tasks = List(10, task, NULL);
    current = task;

    execute_child("a child task", tasks, &current);
    _assert_that(current != task, "current should no longer be task");
    assert_strs_equal(current->text, "child task", "incorrect text %s", current->text);
    _assert_that(task->children->size > 0, "no children");
    _assert_that(list_obj_at_idx(task->children, 0) == current, "current is not the child of task");

    task_destroy(task);
    task_destroy(current);
    list_destroy(tasks);
}
