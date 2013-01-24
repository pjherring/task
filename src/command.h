#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Command {
	char * name;
	char **data;
} Command;

static size_t command_size_t = sizeof(Command);

Command * NewCommand();

#endif
