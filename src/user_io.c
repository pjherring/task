#include "user_io.h"

static const size_t kUserInputInitSize = 100;

void get_user_input_msg(char** command, const char* message) {
    printf("%s", message);
    get_user_input(command);
}

void get_user_input(char** command) {
    char* _command; /* pointer to *commnad  */
    char c; /* character for getting user input  */
    int user_input_idx;
    size_t current_command_size;

    *command = calloc(kUserInputInitSize, sizeof(char));
    _command = *command;
    c = EOF;
    user_input_idx = 0;
    current_command_size = kUserInputInitSize;

    while ((c = getchar()) != EOF && c != '\n') {
        _command[user_input_idx++] = c;

        if (user_input_idx == current_command_size) {
            current_command_size += kUserInputInitSize;
            _command = realloc(_command, sizeof(char) * current_command_size);
        }

    }

    *command = trim(_command);
    free(_command);
}

int get_numeric_input(char* msg) {

    char* user_input_str = NULL;
    int numeric;

    if (msg != NULL) {
        printf("%s", msg);
    }

    while (user_input_str == NULL) {
        get_user_input(&user_input_str);
    }

    numeric = strtodigit(user_input_str);

    return numeric;
}


void get_multiline_input(char** input, const char* msg) {
    char* _input;
    char c;
    int input_idx;
    size_t current_size;

    printf(msg, NULL);
    _input = calloc(kUserInputInitSize, 1);
    c = EOF;
    input_idx = 0;
    current_size = kUserInputInitSize;

    while ((c = getchar()) != EOF && strstr(_input, "\n\n") == NULL) {
        _input[input_idx++] = c;

        if (input_idx == current_size) {
            current_size += kUserInputInitSize;
            _input = realloc(_input, current_size);
        }
    }

    *input = trim(_input);
    free(_input);
}

