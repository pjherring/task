#include "task.h"

static const int kNotesInitSize = 10;
static TaskT zero = {0};

/*
 * Constants
 */
const char * kTaskJsonTextKey = "text";
const char * kTaskJsonNotesKey = "notes";
const char * kTaskJsonChildrenKey = "children";
const char * kTaskJsonIsCompleteKey = "is_complete";


/*
 * Private functions
 */
static void write_task(json_t *object, TaskT* task);
static void write_children_to_task(json_t *, TaskT*);

TaskT* Task(char* const task_text) {

    TaskT* instance;

    instance = malloc(task_size);
    *instance = zero;

    instance->text = malloc(sizeof(char)* (strlen(task_text) + 1));
    strcpy(instance->text, task_text);

    instance->children = List(10, NULL);
    instance->is_complete = NO;
    instance->notes = List(kNotesInitSize, NULL);

    return instance;
}

/*
 * Frees the text and self
 */
void task_destroy(TaskT* self) {
    assert(self != NULL);
    free(self->text);
    list_destroy(self->notes);
    free(self);
}

void task_add_note(TaskT* self, char* note) {
    assert(self != NULL);
    assert(note != NULL);

    list_append(self->notes, note);
}

void task_complete(TaskT* self) {
    self->is_complete = YES;
}

void task_add_child(TaskT* self, TaskT* child) {
    list_append(self->children, child);
}

static size_t kJsonFlags = JSON_INDENT(4) | JSON_PRESERVE_ORDER;

void task_write(ListT* tasks, FILE* file) {
    assert(tasks->size > 0);

    json_t *task_json_arr;;
    int write_result;
    int task_idx;

    task_json_arr = json_array();
    DEBUG("number of tasks %d", tasks->size);

    for (task_idx = 0; task_idx < tasks->size; task_idx++) {
        json_t* task_json_obj;
        TaskT* task;

        task_json_obj = json_object();
        task = list_obj_at_idx(tasks, task_idx);

        DEBUG("task idx %d", task_idx);
        DEBUG("task text %s", task->text);

        write_task(task_json_obj, task);

        json_array_append(task_json_arr, task_json_obj);
        json_decref(task_json_obj);
    }
    write_result = json_dumpf(task_json_arr, file, kJsonFlags);
    _assert_that(write_result == 0, "failed to write json to file");

    //freeing the memory for json
    json_decref(task_json_arr);
}


ListT* task_read(FILE *file) {
    return NULL;
}

/*
 * Begin PRIVATE FUNCTIONS
 */


/*
 * Writes a task to a json file
 */
static void write_task(json_t* json_obj, TaskT* task) {

    //write text to json
    json_object_set_new(json_obj, kTaskJsonTextKey, json_string(task->text));
    //write is complete to json
    json_object_set_new(
        json_obj,
        kTaskJsonIsCompleteKey,
        (task->is_complete == YES ? json_true() : json_false())
    );


    /*
     * If we have notes, add them to the json_obj
     */
    if (task->notes != NULL && task->notes->size > 0) {
        
        json_t *notes_json_arr;
        int note_idx;

        notes_json_arr = json_array();
        for (note_idx = 0; note_idx < task->notes->size; note_idx++) {
            char *note;

            note = list_obj_at_idx(task->notes, note_idx);
            json_array_append_new(notes_json_arr, json_string(note));
        }

        json_object_set(json_obj, kTaskJsonNotesKey, notes_json_arr);
        //decref to avoid memory leaks
        json_decref(notes_json_arr);
    }

    write_children_to_task(json_obj, task);
}

/*
 * Will use recursion to write children objects to a json file
 */
static void write_children_to_task(json_t* json_obj, TaskT* task) {
    /*
     * If we have children then use recursion to write them to json
     */
    if (task->children != NULL && task->children->size > 0) {
        json_t * children_json_arr;
        int child_idx;

        children_json_arr = json_array();

        for (child_idx = 0; child_idx < task->children->size; child_idx++) {
            json_t *child_json_obj;
            TaskT* child_task;

            child_json_obj = json_object();
            child_task = list_obj_at_idx(task->children, child_idx);

            //RECURSION
            write_task(child_json_obj, child_task);

            /*
             * append it and then decrement the reference count to avoid
             * leaks
             */
            json_array_append(children_json_arr, child_json_obj);
            json_decref(child_json_obj);
        }

        /*
         * Add it to the task json and decrement to avoid leaks
         */
        json_object_set(json_obj, kTaskJsonChildrenKey, children_json_arr);
        json_decref(children_json_arr);
    }
}
