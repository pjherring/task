#ifndef TK_USER_IO
#define TK_USER_IO 

#include "common.h"
#include "tk_string.h"

void get_user_input(char** user_input_str);
void get_user_input_msg(char**, const char*);
void get_multiline_input(char** input, const char* msg);
int get_numeric_input(char*);

#endif
