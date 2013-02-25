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
static TaskT* read_from_json(json_t*);

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

    int note_idx;
    int child_idx;

    for (note_idx = 0; note_idx < self->notes->size; note_idx++) {
        free(list_obj_at_idx(self->notes, note_idx));
    }

    list_destroy(self->notes);
    list_destroy(self->children);

    free(self->text);
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
    assert(self != NULL && child != NULL);
    list_append(self->children, child);
    child->parent = self;
}

static size_t kJsonFlags = JSON_INDENT(4) | JSON_PRESERVE_ORDER;

int task_write(ListT* tasks, char* const filename) {
    assert(tasks->size > 0);
    assert(filename != NULL);


    json_t *task_json_arr;;
    int write_result;
    int task_idx;
    FILE *to_write;

    task_json_arr = json_array();
    for (task_idx = 0; task_idx < tasks->size; task_idx++) {
        json_t* task_json_obj;
        TaskT* task;

        task_json_obj = json_object();
        task = list_obj_at_idx(tasks, task_idx);

        write_task(task_json_obj, task);

        json_array_append(task_json_arr, task_json_obj);
        json_decref(task_json_obj);
    }

    write_result = json_dump_file(task_json_arr, filename, kJsonFlags);

    //freeing the memory for json
    json_decref(task_json_arr);

    return write_result;

}


void task_print(TaskT* task) {
    printf("\n%s\n", task->text);

    if (task->notes != NULL && task->notes->size > 0) {
        int note_idx;
        for (note_idx = 0; note_idx < task->notes->size; note_idx++) {
            char* note_str;
            note_str = list_obj_at_idx(task->notes, note_idx);
            puts(note_str);
        }
    }
    puts("");
}


ListT* task_read(char * const filename) {
    assert(filename != NULL);
    ListT* tasks;
    json_t* task_json_arr;
    json_error_t json_error;
    size_t task_size;
    int task_idx;

    task_json_arr = json_load_file(filename, 0, &json_error);

    if (!task_json_arr) {
        printf("Error loading json: \"%s\"\n", json_error.text);
        return NULL;
    }

    if (!json_is_array(task_json_arr)) {
        printf("Error loading json: should be an array!\n");
        return NULL;
    }

    task_size = json_array_size(task_json_arr);
    tasks = List(task_size, NULL);

    for (task_idx = 0; task_idx < task_size; task_idx++) {
        json_t* task_json;
        TaskT* task;

        task_json = json_array_get(task_json_arr, task_idx);

        if (!json_is_object(task_json)) {
            printf("Error! one of the tasks is not an object!\n");
        }

        task = read_from_json(task_json);

        if (task == NULL) {
            printf("Error converting task.\n");
        }

        list_append(tasks, task);
    }

    json_decref(task_json_arr);

    return tasks;
}

/*
 * Begin PRIVATE FUNCTIONS
 */

static TaskT* read_from_json(json_t* json_obj) {
    TaskT* task;
    json_t* text;
    char* text_str;
    json_t* is_complete;
    json_t* note_arr;
    json_t* child_arr;

    text = json_object_get(json_obj, kTaskJsonTextKey);
    is_complete = json_object_get(json_obj, kTaskJsonIsCompleteKey);
    note_arr = json_object_get(json_obj, kTaskJsonNotesKey);
    child_arr = json_object_get(json_obj, kTaskJsonChildrenKey);
    
    if (text == NULL || is_complete == NULL || !json_is_string(text)) {
        _DEBUG("Invalid task object.\n");
        return NULL;
    }

    text_str = (char*) json_string_value(text);
    task = Task(text_str);
    task->is_complete = json_is_true(is_complete) ? YES : NO;

    if (note_arr != NULL && json_is_array(note_arr)) {
        size_t notes_size;
        int note_idx;

        notes_size = json_array_size(note_arr);

        for (note_idx = 0; note_idx < notes_size; note_idx++) {
            json_t* note_json;

            note_json = json_array_get(note_arr, note_idx);

            if (json_is_string(note_json)) {
                const char * json_str_value;
                char * note_str;

                json_str_value = json_string_value(note_json);

                //we have to copy because 'json_str_value' will be dereferenced
                note_str = malloc(sizeof(char) * (strlen(json_str_value) + 1));
                strcpy(note_str, json_str_value);
                task_add_note(task, note_str);
            }

        }

    }

    if (child_arr != NULL && json_is_array(child_arr)) {
        size_t child_arr_size;
        int child_idx;

        child_arr_size = json_array_size(child_arr);

        for (child_idx = 0; child_idx < child_arr_size; child_idx++) {
            json_t* child_json;
            TaskT* child_task;

            child_json = json_array_get(child_arr, child_idx);
            
            if (child_json != NULL) {
                child_task = read_from_json(child_json);
                task_add_child(task, child_task);
            }

        }

    }

    return task;
}


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
/*
 * End private functions
 */
