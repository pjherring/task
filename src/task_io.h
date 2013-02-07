#ifndef TASK_IO
#define TASK_IO

/*
 * Will get a user input string from STDIN.
 *
 * @param max_len The maximum length of the user input. If max_len = -1, get_user_input
 * will attempt to realloc to get the longest user_input it can.
 *
 * Note the char * must be freed at some point
 */
char *get_user_input(int max_len);

#endif
