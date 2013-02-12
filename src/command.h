#ifndef TK_COMMAND_H
#define TK_COMMAND_H

#include "common.h"
#include "list.h"
#include "dict.h"
#include "tk_string.h"

typedef enum {
    CommandTypeTask, CommandTypeNote, CommandTypeComplete
} CommandType;

typedef struct CommandT {
    CommandType type;
    char * text;
    ListT *notes;
    /*
     * The deconstructor
     */
    void (*destroy)(struct CommandT* self);
    /*
     * Add a note to this command
     */
    void (*add_note)(struct CommandT* self, char * note);
    /*
     * The status of the command
     */
    int is_open;
} CommandT;

CommandT* Command(char * const command_text);

static size_t command_size = sizeof(CommandT);

#endif
