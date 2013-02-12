#ifndef TK_TESTER
#define TK_TESTER 

//includes
#include <signal.h>
#include "suite.h"
#include "../src/common.h"

#define assertStrEqual(exp, act) assert(strcmp(exp, act) == 0)

//suite getters
SuiteT* Suite_tk_string();
SuiteT* Suite_list();
SuiteT* Suite_dict();
SuiteT* Suite_command();

#endif
