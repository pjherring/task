#include "execute.h"


void execute_new(char* command, ListT* tasks, TaskT** current_task) {
    assert(strlen(command) > 0);
    assert(tasks != NULL);

    char* task_str;
    TaskT* task;

    //did we just have the command name?
    if (stroccur(command, " ") == 0) {
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
    _DEBUG("execute_finish");
}


void execute_show(char* command, ListT* tasks, TaskT** current_task) {
    _DEBUG("execute_show");
}


void execute_add(char* command, ListT* tasks, TaskT** current_task) {
    _DEBUG("execute_add");
}


void execute_child(char* command, ListT* tasks, TaskT** current_task) {
    _DEBUG("execute_child");
}


void execute_load(char* command, ListT* tasks, TaskT** current_task) {
    _DEBUG("execute_load");
}


void execute_save(char* command, ListT* tasks, TaskT** current_task) {
    _DEBUG("execute_save");
}
