#include "tk_string.h"

char* substr(char * str, int start, int substr_len) {
    char* dest;

    dest = malloc(sizeof(char) * (10));
    assert_that((substr_len + start) < strlen(str),
        "the length of the substring plus its start index must be less "
        "than the length of the total string");
    memcpy(dest, &str[start], substr_len);
    dest[substr_len] = '\0';
    return dest;
}

char** strsplit(char * str, char * delim) {

    int parts_idx;
    char* copied;
    char* token;
    char** parts;

    copied = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(copied, str);

    parts = malloc(split_arr_size(str, delim));

    for(token = strtok(copied, delim), parts_idx = 0; 
        token != NULL; 
        token = strtok(NULL, delim), parts_idx++) {

        parts[parts_idx] = token;
    }

    parts[parts_idx] = NULL;
    return parts;
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


int strtodigit(char* str) {
    int str_idx;
    int digit;
    int found_digit;

    digit = 0;
    found_digit = NO;

    for (str_idx = 0; str[str_idx] != '\0'; str_idx++) {
        char c;
        c = str[str_idx];

        if (c >= '0' && c <= '9') {
            found_digit = YES;
            digit *= 10;
            digit += (c - '0');
        }
    }

    return found_digit ? digit : -1;
}
