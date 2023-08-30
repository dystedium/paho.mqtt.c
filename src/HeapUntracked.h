

#if !defined(HEAPUNTRACKED_H)
#define HEAPUNTRACKED_H


#include <stdlib.h>


#if !defined(paho_malloc_u)
/**
 * call malloc without internal heap tracking
 * @param x the size of the item to be allocated
 * @return the pointer to the item allocated, or NULL
 */
#define paho_malloc_u(x) malloc(x)
#endif

#if !defined(paho_realloc_u)
/**
 * call realloc without internal heap tracking
 * @param a the heap item to be reallocated
 * @param b the new size of the item
 * @return the new pointer to the heap item
 */
#define paho_realloc_u(a, b) realloc(a, b)
#endif

#if !defined(paho_free_u)
/**
 * call free without internal heap tracking
 * @param x the pointer to the item to be freed
 */
#define paho_free_u(x) free(x)
#endif


#endif
