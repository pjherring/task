#include "user_io.h"

static const size_t kUserInputInitSize = 100;

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

    *command = _command;
}
