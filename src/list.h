#ifndef TK_LIST
#define TK_LIST 

#include "common.h"

typedef struct ListT {
    void **values;
    void ** last_value;
    int size;
    /*
     * The total number of bytes allocated to values;
     */
    int capacity;
    /*
     * Frees the values and the list
     */
    void (*destroy)(struct ListT*);
    /*
     * returns the object at the specified index. If @param idx is out
     * of range an ABORT signal is raised.
     */
    void* (*object_at_index)(struct ListT*, int idx);
    /*
     * This method will add an object at the end of the list. If more
     * memory is needed more is allocated
     * 
     * @param obj The object to append
     */
    void (*append)(struct ListT*, void*);

} ListT;

static size_t kListSize = sizeof(ListT);

/*
 * This is the creator for ListT structs. Callers of this must free the
 * returned pointer.
 * 
 * @param begin_size The estimated size of values. This will be realloced if
 *  needed to fit the values in the variadic args
 * @params ... The values. This must a NULL termianted list.
 *     
 */
ListT* List(int begin_size, ...);

#endif
