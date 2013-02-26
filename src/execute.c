#include "execute.h"

static int is_command_only(char* command);
static char* get_text_from_command(char* command);
static char* make_file_name();
static int is_loadable(char* filename);
static ListT* get_loadables(int do_print);

void execute_new(char* command, ListT* tasks, TaskT** current_task) {
    assert(strlen(command) > 0);
    assert(tasks != NULL);

    char* task_str;
    TaskT* task;

    //did we just have the command name?
    if (is_command_only(command)) {
        get_user_input_msg(&task_str, "What do you need to get done? ");
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

    task = Task(task_str);
    *current_task = task;
    list_append(tasks, task);
}


void execute_finish(char* command, ListT* tasks, TaskT** current_task) {

    if (*current_task != NULL) {
        TaskT* _current;
        int task_idx;

        _current = *current_task;
        printf("Finsihing '%s'", _current->text);
        _current->is_complete = YES;

        task_idx = tasks->size - 1;

        for (task_idx = tasks->size - 1; 
            task_idx >= 0 && _current->is_complete == YES;
            task_idx--) {
            _current = list_obj_at_idx(tasks, task_idx);
        }

        //-1 because if our loop goes all the way through it will go past the
        //first one
        if (task_idx < -1 || _current->is_complete == YES) {
            puts("\nAll tasks completed!");
            *current_task = NULL;
        } else {
            *current_task = _current;
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

    if (*current_task != NULL) {

        if (tasks->size == 0) {
            puts("No tasks");
            return;
        }

        char* note;

        if (is_command_only(command)) {
            get_multiline_input(&note, "What is your note? (hit return twice to end)\n");
        } else {
            char *after_space, *first_space;
            int space_idx;

            first_space = strchr(command, ' ');
            note = malloc(sizeof(char) * (strlen(command) - (command - first_space)));
            strcpy(note, first_space + 1);
        }

        task_add_note(*current_task, note);
    } else {
        puts("No current task");
    }
}

void execute_print(char* command, ListT* tasks, TaskT** current_task) {
    assert(tasks != NULL);

    if (tasks->size == 0) {
        puts("No tasks.");
    } else {
        puts("");
        int task_idx;
        for (task_idx = 0; task_idx < tasks->size; task_idx++) {
            printf("Task #%d: ", task_idx + 1);
            TaskT* task;
            task = list_obj_at_idx(tasks, task_idx);
            task_print(task);
            printf("\n", NULL);
        }
    }
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

    ListT* files;

    //check if we should save
    if (tasks != NULL && tasks->size > 0) {

        char* save_before_load;
        printf("Save before load? (y)/n? ");
        get_user_input(&save_before_load);

        if (save_before_load != NULL && strlen(save_before_load) > 0
            && save_before_load[0] == 'y' || save_before_load[0] == 'Y') {
            printf("saving\n");
            execute_save(command, tasks, current_task);
        }
    }

    files = get_loadables(YES);

    if (files->size > 0) {
        ListT* _tasks;
        TaskT* loaded_task;
        int user_selection;
        char *filename, *abs_file;;


        while ((user_selection = get_numeric_input("Choose which file to load? ")) < 0 || user_selection >= files->size) ;
        DEBUG("user_selection %d", user_selection);
        printf("\n\n");

        filename = list_obj_at_idx(files, user_selection);
        abs_file = malloc(strlen(filename) + 20);
        sprintf(abs_file, "tasks/%s", filename);

        //destroy all tasks in memory
        list_empty(tasks, YES);
        _tasks = task_read(abs_file);
        list_copy(tasks, _tasks);
        *current_task = tasks != NULL && tasks->size > 0 ? list_obj_at_idx(tasks, 0) : NULL;

        list_destroy(_tasks);
        free(abs_file);
    } else {
        puts("No files to load.");
    }

    list_destroy(files);
}


static const char* kTaskDir = "tasks";

ListT* get_loadables(int do_print) {
    DIR* task_dir;
    struct dirent *task_dirent;
    ListT* files;
    int file_idx;

    task_dir = opendir(kTaskDir);
    assert(task_dir != NULL);

    files = List(10, NULL);
    file_idx = 0;

    while ((task_dirent = readdir(task_dir)) != NULL) {
        //
        //make sure we are not looking at . and .. files
        if (is_loadable(task_dirent->d_name)) {

            list_append(files, task_dirent->d_name);

            if (do_print) {
                printf("%d) %s\n", file_idx++, task_dirent->d_name);
            }
        }
    }

    return files;
}


int is_loadable(char* filename) {
    //is this a dot file
    return strcmp(".", filename) != 0 && strcmp("..", filename) != 0;
}

static const char* kFilenamePromptFormat = "Enter a filename or hit return to save as '%s'.\n";

void execute_save(char* command, ListT* tasks, TaskT** current_task) {
    char* filename;
    int write_result;

    if (tasks != NULL && tasks->size > 0) {

        char* user_filename = NULL;
        char* input_msg = NULL;

        filename = make_file_name();
        input_msg = malloc(strlen(filename) + strlen(kFilenamePromptFormat) + 1);
        sprintf(input_msg, kFilenamePromptFormat, filename);

        get_user_input_msg(&user_filename, input_msg);

        if (user_filename != NULL && strlen(user_filename) > 0) {
            char* user_filename_with_dir;

            user_filename_with_dir = malloc(6 + 1 + strlen(user_filename));
            sprintf(user_filename_with_dir, "tasks/%s", user_filename);

            free(filename);
            free(user_filename);

            filename = user_filename_with_dir;
        }
        
        write_result = task_write(tasks, filename);

        if (task_write < 0) {
            printf("Failed to write tasks to %s\n", filename);
        }

        free(filename);
    }
}

void execute_change(char* command, ListT* tasks, TaskT** current_task) {
    int choice = -1, task_idx, one_displayed = NO;
    int* choices;

    choices = calloc(tasks->size, sizeof(int));

    for (task_idx = 0; task_idx < tasks->size; task_idx++) {
        TaskT* task;

        task = list_obj_at_idx(tasks, task_idx);

        if (task->is_complete == NO) {
            choices[task_idx] = 1;
            one_displayed = YES;
            printf("%d) %s\n", task_idx + 1, task->text);
        }
    }

    if (one_displayed == YES) {
        char* msg;

        msg = "Which task do you want to switch to? ";
        while (choices[(choice = get_numeric_input(msg)) - 1] == 0) {
            printf("Invalid choice! ", NULL);
        }

        *current_task = list_obj_at_idx(tasks, choice - 1);
    } else {
        puts("No incomplete tasks to switch to.");
    }
}


static const char* kFileTimeFormat = "%Y_%m_%d";
static size_t kFileTimeFormatSize = 20; //4 for year, 2 for month and day, 2 for _ and 1 for \0
static const char* kFileNameFormat = "tasks/task-%s.js";

static char* make_file_name() {
    time_t current_time;
    struct tm* local_time;
    char* time_str;
    char* filename;

    //get the current date into a string
    current_time = time(NULL);
    local_time = localtime(&current_time);
    time_str = malloc(kFileTimeFormatSize);
    strftime(time_str, kFileTimeFormatSize, kFileTimeFormat, local_time);

    //insert the date into the filename format
    filename = malloc(kFileTimeFormatSize + strlen(time_str) + 1);
    sprintf(filename, kFileNameFormat, time_str);

    //make sure we free our memory that held time_str
    free(time_str);

    return filename;
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
