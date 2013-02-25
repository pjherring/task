#include "main.h"

static const char* kWelcomeMessage = 
    "\n\n\nWelcome to task!\n"
    "Here are your commands:\n"
    "n(ew) - Begin a new task\n"
    "f(inish) - finish the current task\n"
    "s(how) - show current task\n"
    "a(dd) - add a note to the current task\n"
    "l(oad) - load a task file\n"
    "w(rite) - save a task file\n"
    "p(rint) - print tasks\n"
    "q(uit) - quit\n";
    
    
void get_user_input(char** command);
void execute_command(char*, ListT*, TaskT**);
int do_quit(char * command);
void init_command_dict();

DictionaryT* kCommandStrDict = NULL;

int main() {
    printf("%s\n\n", kWelcomeMessage);

    //bootstrap
    char * command;
    ListT* tasks;
    TaskT* current;

    tasks = List(10, NULL);
    command = NULL;
    current = NULL;

    init_command_dict();



    while (command == NULL || strlen(command) == 0 || !do_quit(command)) {
        get_user_input_msg(&command, "\nWhat would you like to do? ");

        if (command != NULL && strlen(command) > 0) {
            execute_command(command, tasks, &current);
        }
    }

    free(command);
}


void init_command_dict() {
    kCommandStrDict = Dict();
    dict_add(kCommandStrDict, "n", &execute_new);
    dict_add(kCommandStrDict, "new", &execute_new);
    dict_add(kCommandStrDict, "f", &execute_finish);
    dict_add(kCommandStrDict, "finish", &execute_finish);
    dict_add(kCommandStrDict, "s", &execute_show);
    dict_add(kCommandStrDict, "show", &execute_show);
    dict_add(kCommandStrDict, "a", &execute_add_note);
    dict_add(kCommandStrDict, "add", &execute_add_note);
    dict_add(kCommandStrDict, "l", &execute_load);
    dict_add(kCommandStrDict, "load", &execute_load);
    dict_add(kCommandStrDict, "w", &execute_save);
    dict_add(kCommandStrDict, "write", &execute_save);
    dict_add(kCommandStrDict, "print", &execute_print);
    dict_add(kCommandStrDict, "p", &execute_print);
}


void execute_command(char* command, ListT* tasks, TaskT** current) {
    assert(command != NULL && strlen(command) != 0);

    char* command_token = command;
    void (*command_executor)(char*, ListT*, TaskT**) = NULL;
    int space_idx = -1;

    space_idx = strstr(command, " ") - command;

    if (space_idx > 0) {
        //get the first word
        command_token = malloc(sizeof(char) * (space_idx + 1));
        strncpy(command_token, command, space_idx);

    } 

    command_executor = dict_obj_at(kCommandStrDict, command_token);

    if (command_executor == NULL) {
        puts("Invalid command");
        return;
    }

    if (space_idx > 0) {
        free(command_token);
    }

    command_executor(command, tasks, current);
}

static const char* kQuitString = "quit";
static const char* kQuitStringAbbr = "q";

int do_quit(char* command) {
    char* substr = strstr(command, kQuitString);

    //if the substr is NULL this sequence doesn't appear
    //in order to quit we need to make sure the string is the first in the 
    //command
    /*
     * If the substr is NULL an occurance was not found
     * The difference in pointers tells us the location of the
     * sequence in the command variable. It needs to be the first thing
     * in order to quit
     */
    return strcmp(command, kQuitStringAbbr) == 0 
        || (substr != NULL && ((substr - command) == 0));
}
