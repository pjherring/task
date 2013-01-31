#ifndef LOG
#define LOG 

#define DEBUG(fmt, ...) do { \
    task_log("Debug", __FILE__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__); \
} while(0);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void task_log(char level[], char file[], const char function_name[], int line_num, char * fmt, ...);

#endif
