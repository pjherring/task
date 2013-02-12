#ifndef TK_STRING
#define TK_STRING 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "common.h"

/*
 * Copy the substring of str into dest starting at start with a length of len
 */
void substr(char * dest, char * str, int start, int len);

/*
 * Split the str by the delim. Store in parts.
 */
void strsplit(char **parts, char * str, char * delim);

/*
 * How many times does the delim happen in the str
 */
int stroccur(char * str, char * delim);

/*
 * This is to figure out how big a char ** you need to get all the parts of a split
 * str back. It will add an extra space for another char * that will be NULL
 */
size_t split_arr_size(char * str, char * delim);

/*
 * This will lowercase @param to_lower
 * @param to_lower the string to change all characters to lowercase
 */
void strlower(char * to_lower);

#endif
