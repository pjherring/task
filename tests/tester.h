#ifndef TK_TESTER
#define TK_TESTER 

//includes
#include <signal.h>
#include "suite.h"

#define assertStrEqual(exp, act) assert(strcmp(exp, act) == 0)

//suite getters
SuiteT* Suite_tk_string();

#endif
