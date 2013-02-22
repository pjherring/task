#ifndef TK_LIST
#define TK_LIST 

#include "common.h"

typedef struct ListT {
    void** values;
    void** last_value;
    int size;
    /*
     * The total number of bytes allocated to values;
     */
    int capacity;

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

/*
 * returns the object at the specified index. If @param idx is out
 * of range an ABORT signal is raised.
 */
void * list_obj_at_idx(ListT*, int);


/*
 * Frees the values then the list
 */
void list_destroy(ListT*);


/*
 * This method will add an object at the end of the list. If more
 * memory is needed more is allocated
 * 
 * @param obj The object to append
 */
void list_append(ListT*, void*);

/*
 * Find the index of a certain object
 */
int list_index_of(ListT*, void*);

#endif
