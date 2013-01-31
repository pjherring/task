#include "task_strings.h"

/*
 * =====================================================================================
 *
 *       Filename:  task_strings.c
 *
 *    Description:  The implementation of task_strings.h
 *
 *        Version:  1.0
 *        Created:  01/31/2013 06:43:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  PJ Herring (), 
 *   Organization:  
 *
 * =====================================================================================
 */

void substr(char * dest, char * str, int start, int len) {
    strncpy(dest, &str[start], len);
}

void strsplit(char **parts, char * str, char * delim) {

    int parts_idx = 0;
    int str_len = strlen(str);

    char * str_copy = malloc(sizeof(str));
    strcpy(str_copy, str);

    char * token;

    //this makes the most sense as our string part can never be longer than the str
    while ( (token = strtok(str_copy, delim)) != NULL) {

        parts[parts_idx++] = token;

        if (str_copy != NULL) {
            str_copy = NULL;
        }
    }

    free(str_copy);
    parts[parts_idx] = NULL;
}

int stroccur(char * str, char * delim) {
    int count = 0;
    int offset = 0;
    char * occurance = strstr(str, delim);

    while (occurance) {
        count++;
        occurance = strstr(occurance + 1, delim);
    }

    return count;
}

size_t split_arr_size(char * str, char * delim) {
    return sizeof(char *) * (stroccur(str, delim) + 2);
}

