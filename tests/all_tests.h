#ifndef ALL_TESTS_H
#define ALL_TESTS_H

#include "CuTest.h"
#include <stdio.h>
#include <stdlib.h>

CuSuite * helper_get_suite();
CuSuite * task_io_suite();
CuSuite * command_suite();

#endif
