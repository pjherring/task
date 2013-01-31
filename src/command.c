#include "command.h"

command_t command_from_string(char * const command_str);
CommandDataT * data_from_string(char * const command_str);

CommandT * NewCommand(char * const command_str) {

	CommandT *command = malloc(command_size);
    assert_that(command, "command was not malloced");

    command->type = command_from_string(command_str);
    command->data = data_from_string(command_str);

    assert_that(command->type != CommandTypeNotFound, "Could not make command from \"%s\"\n", command_str);

	return command;
}

command_t command_from_string(char * const command_str) {
   char * const lowercase_command = lowercase_str(command_str);

   if (strcmp(lowercase_command, kTaskCommandStr) == 0) {
        return CommandTypeAddTask;
   } else if (strcmp(lowercase_command, kNoteCommandStr) == 0) {
       return CommandTypeTakeNote;
   } else if (strcmp(lowercase_command, kCompleteTask) == 0) {
       return CommandTypeCompleteTask;
   }

   return CommandTypeNotFound;
}

CommandDataT * data_from_string(char * const command_str) {
    return NULL;
}
