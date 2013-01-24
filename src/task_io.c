#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "task_io.h"

static int kIoStartLen = 100;

char *get_user_input(int max_len) {

	char c = EOF;

	bool is_unlimited_length = false;
	if (max_len < 0) {
		is_unlimited_length = true;
		max_len = kIoStartLen;
	}

	char * user_input_str = malloc(max_len);
	int idx = 0;

	while ((c = getchar()) != EOF && c != '\n') {
		user_input_str[idx++] = c;

		//have we reached the end of the memory?
		if (idx == max_len) {

			if (is_unlimited_length) {
				max_len *= kIoStartLen;
				user_input_str = realloc(user_input_str, max_len);
			} else {
				//return our string
				return user_input_str;
			}
		} 
	}

	return user_input_str;
}
