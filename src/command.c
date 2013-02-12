#include "command.h"

static const char kCommandTypeTaskStr = 't';
static const char kCommandTypeNoteStr = 'n';
static const char kCommandTypeCompleteStr = 'c';

static char * kCommandDelim = " ";
static const int kNotesInitSize = 10;


//methods
static CommandType commandtype_from_str(char * str);
static void destroy(CommandT* destroy);
static void add_note(CommandT* self, char * note);

CommandT * Command(char * const command_text) {

    size_t parts_size;
    char **parts;
    CommandType type;
    CommandT *instance;
    
    parts_size = split_arr_size(command_text, kCommandDelim);
    parts = malloc(parts_size);
    strsplit(parts, command_text, kCommandDelim);

    assert((sizeof(parts) / sizeof(char *)) > 0);

    type = commandtype_from_str(parts[0]);
    assert(type != -1);

    instance = malloc(command_size);

    instance->text = malloc(sizeof(char) * (strlen(command_text) + 1));
    strcpy(instance->text, command_text);

    instance->type = type;
    instance->is_open = YES;
    instance->destroy = &destroy;
    instance->notes = List(kNotesInitSize, NULL);

    return instance;
}

/*
 * Frees the text and self
 */
static void destroy(CommandT* self) {
    assert(self != NULL);
    free(self->text);
    self->notes->destroy(self->notes);
    free(self);
}

/*
 * Will look at first character of str and produce a command from it.
 *
 * @param str The string to get the command from
 *
 * @return CommandType enum. -1 if string does not match.
 */
static CommandType commandtype_from_str(char * str) {
    char first;
    assert(sizeof(str) / sizeof(char) > 0);
    first = str[0];

    if (first >= 'A' && first <= 'Z') {
        first += ('a' - 'A');
    }

    assert(first >= 'a' && first <= 'z');
    
    if (first == kCommandTypeTaskStr) {
        return CommandTypeTask;
    } else if (first == kCommandTypeCompleteStr) {
        return CommandTypeComplete;
    } else if (first == kCommandTypeNoteStr) {
        return CommandTypeNote;
    }

    return -1;
}

static void add_note(CommandT *self, char * note) {
    _assert_that(self != NULL, "self can not be NULL");
    _assert_that(note != NULL, "note can not be NULL");
}

