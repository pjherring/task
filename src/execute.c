#include "execute.h"

static int is_command_only(char* command);
static char* get_text_from_command(char* command);

void execute_new(char* command, ListT* tasks, TaskT** current_task) {
    assert(strlen(command) > 0);
    assert(tasks != NULL);

    char* task_str;
    TaskT* task;

    //did we just have the command name?
    if (is_command_only(command)) {
        printf("What do you need to get done?\n");
        get_user_input(&task_str);
    } else {
        /*
         * We are copying memory rather than just pointing to the beginning of
         * the task part of command because we will free command eventually
         */
        int first_space_idx, command_strlen;

        first_space_idx = strstr(command, " ") - command;
        command_strlen = strlen(command);
        task_str = malloc(sizeof(char) * (command_strlen - first_space_idx));
        //add 1 to the command ptr to not copy the space
        strncpy(task_str, (command + first_space_idx + 1), (command_strlen - first_space_idx));
    }

    *current_task = Task(task_str);
    list_append(tasks, task);
}


void execute_finish(char* command, ListT* tasks, TaskT** current_task) {

    if (*current_task != NULL) {
        TaskT* _current;

        _current = *current_task;
        _current->is_complete = YES;

        if (tasks->size > 1) {

            TaskT* task;
            int task_idx;

            task_idx = list_index_of(tasks, _current) - 1;
            task = tasks->values[task_idx];

            while (task->is_complete == YES && task_idx >= 0) {
                task = tasks->values[task_idx];
            }

            *current_task = task->is_complete == NO ? task : NULL;

        } else {
            *current_task = NULL;
        }

    } else {
        printf("No current task.\n");
    }
}


void execute_show(char* command, ListT* tasks, TaskT** current_task) {
    TaskT* _current;
    _current = *current_task;

    if (_current != NULL) {
        char* status;

        status = _current->is_complete ? "Finished" : "Not Finished";
        printf("\nYour current task is: '%s'. \nIts status is '%s'.\n", _current->text, status);
    } else {
        printf("No current task.\n");
    }
}


void execute_add_note(char* command, ListT* tasks, TaskT** current_task) {
    assert(command != NULL);
    assert(current_task != NULL);

    list_append((*current_task)->notes, command);
}


void execute_child(char* command, ListT* tasks, TaskT** current_task) {
    char* child_text;
    TaskT* child;

    if (is_command_only(command)) {
        printf("What do you need to get done?");
        get_user_input(&child_text);
    } else {
        child_text = get_text_from_command(command);
    }

    child = Task(child_text);
    task_add_child(*current_task, child);
    *current_task = child;
}


void execute_load(char* command, ListT* tasks, TaskT** current_task) {
    _DEBUG("execute_load");
}


void execute_save(char* command, ListT* tasks, TaskT** current_task) {
    _DEBUG("execute_save");
}

static int is_command_only(char* command) {
    return stroccur(command, " ") == 0;
}

static char* get_text_from_command(char* command) {
    int first_space_idx, command_strlen;
    char* text;;

    first_space_idx = strstr(command, " ") - command;
    command_strlen = strlen(command);
    text = malloc(sizeof(char) * (command_strlen - first_space_idx));
    //add 1 to the command ptr to not copy the space
    strncpy(text, (command + first_space_idx + 1), (command_strlen - first_space_idx));
    return text;
}
