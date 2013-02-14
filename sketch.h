
#ifndef TK_SKECTH
#define TK_SKETCH

#include <stdio.h>
#include <stdlib.h>

typedef struct ExampleT {
    char * name;
    void (^print_name)();
} ExampleT;

#define before_arrow(obj) patsubst(#obj, '-\>.*', '')
#define __(method_call) before_arrow(method_call)

#endif
