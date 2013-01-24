#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "helper.h"

char * const lowercase_str(char * const to_lower) {

    char * to_lower_copy = strdup(to_lower);
    int i = 0;
    char c;

    while ((c = to_lower[i]) != '\0') {
        to_lower_copy[i++] = tolower(c);
    }

    return to_lower_copy;
}


