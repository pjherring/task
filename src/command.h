#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helper.h"
#include "assertions.h"

typedef enum {
    CommandTypeAddTask, 
    CommandTypeTakeNote, 
    CommandTypeCompleteTask,
    CommandTypeNotFound
} command_t;


typedef struct {
    char * name;
    char * info;
} CommandDataT;


typedef struct Command {
    command_t type;
	char * name;
    CommandDataT * data;
} CommandT;

static size_t command_size = sizeof(CommandT);


static char * kTaskCommandStr = "task";
static char * kNoteCommandStr = "note";
static char * kCompleteTask = "complete";

CommandT * NewCommand(char * const command_str);

#endif
