#include "command.h"

Command * NewCommand() {
	Command *command = malloc(command_size_t);
	return command;
}
