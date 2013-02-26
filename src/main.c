#include "main.h"

static const char* kWelcomeMessage = 
    "\n\n\nWelcome to task!\n"
    "Here are your commands:\n"
    "n(ew) - Begin a new task\n"
    "a(dd) - add a note to the current task\n"
    "f(inish) - finish the current task\n"
    "s(how) - show current task\n"
    "p(rint) - print tasks\n"
    "c(hange) - change tasks\n"
    "l(oad) - load a task file\n"
    "w(rite) - save a task file\n"
    "q(uit) - quit\n";
    
    
DictionaryT* get_command_dict();
void get_user_input(char** command);
void execute_command(char*, ListT*, TaskT**);
int do_quit(char * command);


int main() {
    puts(kWelcomeMessage);

    //bootstrap
    char * command;
    ListT* tasks;
    TaskT* current;

    tasks = List(10, NULL);
    command = NULL;
    current = NULL;

    get_user_input_msg(&command, "\nWhat would you like to do? ");

    while (command == NULL || strlen(command) == 0 || !do_quit(command)) {

        if (command != NULL && strlen(command) > 0) {
            execute_command(command, tasks, &current);
        }

        get_user_input_msg(&command, "\nWhat would you like to do? ");
    }


    if (tasks->size > 0) {
        get_user_input_msg(&command, "\nSave your tasks? (y)/n: ");

        if (strlen(command) == 0 || 
            (strcmp(command, "n") != 0 && strcmp(command, "N") != 0)) {
            execute_save(command, tasks, &current);
        }
    }

    free(command);
}


DictionaryT* get_command_dict() {

    static DictionaryT* command_dict = NULL;
    
    if (command_dict == NULL) {
        command_dict = Dict();
        dict_add(command_dict, "n", &execute_new);
        dict_add(command_dict, "new", &execute_new);
        dict_add(command_dict, "f", &execute_finish);
        dict_add(command_dict, "finish", &execute_finish);
        dict_add(command_dict, "s", &execute_show);
        dict_add(command_dict, "show", &execute_show);
        dict_add(command_dict, "a", &execute_add_note);
        dict_add(command_dict, "add", &execute_add_note);
        dict_add(command_dict, "l", &execute_load);
        dict_add(command_dict, "load", &execute_load);
        dict_add(command_dict, "w", &execute_save);
        dict_add(command_dict, "write", &execute_save);
        dict_add(command_dict, "print", &execute_print);
        dict_add(command_dict, "p", &execute_print);
        dict_add(command_dict, "c", &execute_change);
        dict_add(command_dict, "change", &execute_change);
    }

    return command_dict;
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

    command_executor = dict_obj_at(get_command_dict(), command_token);

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
