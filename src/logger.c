#include "logger.h"
/*
 * =====================================================================================
 *
 *       Filename:  log.c
 *
 *    Description:  A basic logger
 *
 *        Version:  1.0
 *        Created:  01/31/2013 14:48:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

static const char kLogPrepend[] = "[%s: %s, %s (Line %d)] ";

void tk_log(char level[], char file[], const char function_name[], int line_num, char * const fmt, ...) {
    va_list args;
    va_start(args, fmt);

    printf(kLogPrepend, level, file, function_name, line_num);
    vprintf(fmt, args);
    printf("\n");

    va_end(args);
}
