#include "execute.h"

static int is_command_only(char* command);
static char* get_text_from_command(char* command);
static char* make_file_name();
static int is_loadable(char* filename);

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

        task_idx = list_index_of(tasks, _current);

        while (task_idx > 0 && _current->is_complete == YES) {
            task_idx--;
            _current = list_obj_at_idx(tasks, task_idx);
        }

        if (task_idx < 0) {
            puts("All tasks completed!");
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
    assert(current_task != NULL);

    if (tasks->size == 0) {
        puts("No tasks");
        return;
    }

    char* note;

    if (is_command_only(command)) {
        get_user_input_msg(&note, "What is your note?");
    } else {
        char *after_space, *first_space;
        int space_idx;

        first_space = strchr(command, ' ');
        note = malloc(sizeof(char) * (strlen(command) - (command - first_space)));
        strcpy(note, first_space + 1);
    }

    task_add_note(*current_task, note);
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

static const char* kTaskDir = "tasks";

void execute_load(char* command, ListT* tasks, TaskT** current_task) {
    DIR* task_dir;
    struct dirent *task_dirent;
    ListT* files;
    int file_idx, user_selection;
    char *user_selection_str = NULL, *filename = NULL, *abs_file = NULL;

    task_dir = opendir(kTaskDir);
    assert(task_dir != NULL);

    files = List(10, NULL);
    file_idx = 0;

    //check if we should save
    if (tasks != NULL && tasks->size > 0) {
        char* save_before_load;
        printf("Save before load? (y)/n?\n");
        get_user_input(&save_before_load);

        if (save_before_load != NULL && strlen(save_before_load) > 0
            && save_before_load[0] == 'y' || save_before_load[0] == 'Y') {
            printf("saving\n");
            execute_save(command, tasks, current_task);
        }
    }

    while ((task_dirent = readdir(task_dir)) != NULL) {
        //
        //make sure we are not looking at . and .. files
        if (is_loadable(task_dirent->d_name)) {
            list_append(files, task_dirent->d_name);
            printf("%d) %s\n", file_idx++, task_dirent->d_name);
        }
    }

    do {

        if (user_selection_str != NULL) {
            free(user_selection_str);
        }

        printf("Choose which file to load? ");
        get_user_input(&user_selection_str);
        user_selection = strtodigit(user_selection_str);
    }  while (user_selection < 0 && user_selection >= files->size);

    printf("\n\n");

    filename = list_obj_at_idx(files, user_selection);
    abs_file = malloc(sizeof(char) * (strlen(filename) + 6));
    sprintf(abs_file, "tasks/%s", filename);

    //destroy all tasks in memory
    if (tasks != NULL) {
        int task_idx;
        TaskT* item;

        for (task_idx = 0; task_idx < tasks->size; task_idx++) {
            item = list_obj_at_idx(tasks, task_idx);
            task_destroy(item);
        }

        list_destroy(tasks);
        tasks = NULL;
    }

    tasks = task_read(abs_file);
    *current_task = tasks != NULL && tasks->size > 0 ? list_obj_at_idx(tasks, 0) : NULL;
}


int is_loadable(char* filename) {
    const char* dot_chr;
    int dot_idx;
    
    //is this a dot file
    if (strcmp(".", filename) == 0 
        && strcmp("..", filename) == 0) {
        return NO;
    }

    dot_chr = strrchr(filename,  '.');
    
    //if no . exists, its not loadable
    if (dot_chr == NULL) {
        return NO;
    }

    dot_idx = dot_chr - filename;

    //if this dot is not the 2nd to last char
    if ((dot_idx + 3) != strlen(filename)) {
        return NO;
    }

    if (filename[dot_idx + 1] != 'j' && filename[dot_idx + 2] != 's') {
        return NO;
    }

    return YES;
}


void execute_save(char* command, ListT* tasks, TaskT** current_task) {
    char* filename;
    int write_result;

    if (tasks != NULL && tasks->size > 0) {
        filename = make_file_name();
        write_result = task_write(tasks, filename);

        if (task_write < 0) {
            printf("Failed to write tasks to %s\n", filename);
        }

        free(filename);
    }
}


static const char* kFileTimeFormat = "%Y_%m_%d";
static size_t kFileTimeFormatSize = sizeof(char) * 10; //4 for year, 2 for month and day, 2 for _ and 1 for \0
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
    filename = malloc(sizeof(char) * (strlen(kFileTimeFormat) + strlen(time_str) + 1));
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
