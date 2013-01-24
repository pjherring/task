#include <assert.h>

#ifndef T_ASSERT
#define T_ASSERT

#define AssertNotNull(obj, message) if (obj == NULL) { \
    if (message != NULL) { \
        printf("Error: %s", message); \
    } \
    assert(obj != NULL); \
}
#endif


