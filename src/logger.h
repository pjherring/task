#ifndef TK_LOG
#define TK_LOG 

#define _DEBUG(fmt) DEBUG(fmt, NULL)
#define DEBUG(fmt, ...) do { \
    tk_log("Debug", __FILE__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__); \
} while(0);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void tk_log(char level[], char file[], const char function_name[], int line_num, char * fmt, ...);

#endif
