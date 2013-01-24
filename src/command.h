#ifndef COMMAND_H
#define COMMAND_H

typedef struct Command {
	char * name;
	char **data;
} Command;

Command NewCommand();

#endif
