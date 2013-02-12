#include "tk_string.h"

void substr(char * dest, char * str, int start, int len) {
    strncpy(dest, &str[start], len);
}

void strsplit(char **parts, char * str, char * delim) {

    int parts_idx = 0;
    char * str_copy = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(str_copy, str);

    char * token = strtok(str_copy, delim);
    free(str_copy);

    do {
        parts[parts_idx++] = token;
        token = strtok(NULL, delim);
    } while(token != NULL);

    parts[parts_idx] = NULL;
}

int stroccur(char * str, char * substr) {
    int count = 0;
    int offset = 0;
    char * occurance = strstr(str, substr);

    while (occurance) {
        count++;
        occurance = strstr(occurance + 1, substr);
    }

    return count;
}

size_t split_arr_size(char * str, char * delim) {
    return sizeof(char *) * (stroccur(str, delim) + 2);
}


static int kAsciiDiff = 'a' - 'A';

void strlower(char * to_lower) {
    int i;

    for (i= 0; to_lower[i] != '\0'; i++) {
        char c = to_lower[i];
        if (c >= 'A' && c <= 'Z') {
            c += kAsciiDiff;
            to_lower[i] = c;
        }
    }
}

