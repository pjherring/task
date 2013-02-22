#ifndef TK_EXECUTE_H
#define TK_EXECUTE_H 

#include "list.h"
#include "task.h"
#include "tk_string.h"
#include "user_io.h"

void execute_new(char*, ListT*, TaskT**);
void execute_finish(char*, ListT*, TaskT**);
void execute_show(char*, ListT*, TaskT**);
void execute_add(char*, ListT*, TaskT**);
void execute_child(char*, ListT*, TaskT**);
void execute_load(char*, ListT*, TaskT**);
void execute_save(char*, ListT*, TaskT**);

#endif
