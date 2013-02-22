#ifndef TK_COMMAND_H
#define TK_COMMAND_H

#include <jansson.h>

/*
 * Begin includes
 */
#include "common.h"
#include "list.h"
#include "dict.h"
#include "tk_string.h"
/*
 * End includes
 */

/*
 * Begin Constants
 */
extern const char * kTaskJsonTextKey;
extern const char * kTaskJsonNotesKey;
extern const char * kTaskJsonChildrenKey;
extern const char * kTaskJsonIsCompleteKey;

typedef struct TaskT {
    /*
     * The text describing this task
     */
    char * text;
    /*
     * Any notes associated with this task
     */
    ListT *notes;
    /*
     * Sub tasks, or tasks that come up while performing this one
     */
    ListT *children;
    /*
     * The status of the task
     */
    int is_complete;
} TaskT;


static size_t task_size = sizeof(TaskT);

TaskT* Task(char * const task_text);
void task_destroy(TaskT* task);
void task_add_note(TaskT* task, char* note);
void task_complete(TaskT* task);
void task_add_child(TaskT* parent, TaskT* child);
/*
 * write json data to a file 
 */
int task_write(ListT* tasks, char* const filename);
/*
 * Read json data from a file to create tasks
 */
ListT* task_read(char * const filename);


#endif
