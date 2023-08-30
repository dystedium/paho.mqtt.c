/*******************************************************************************
 * Copyright (c) 2009, 2020 IBM Corp. and others
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * and Eclipse Distribution License v1.0 which accompany this distribution. 
 *
 * The Eclipse Public License is available at 
 *    https://www.eclipse.org/legal/epl-2.0/
 * and the Eclipse Distribution License is available at 
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial API and implementation and/or initial documentation
 *    Ian Craggs - use tree data structure instead of list
 *******************************************************************************/


#if !defined(HEAP_H)
#define HEAP_H

#if defined(HIGH_PERFORMANCE)
#define NO_HEAP_TRACKING 1
#endif

#define PAHO_MEMORY_ERROR -99

#include "HeapUntracked.h"
#include "MQTTExportDeclarations.h"

#include <stdio.h>

#if !defined(NO_HEAP_TRACKING)

#if !defined(paho_malloc_t)
/**
 * call malloc with internal heap tracking; when NO_HEAP_TRACKING is defined,
 * this is equivalent to paho_malloc_u
 * @param x the size of the item to be allocated
 * @return the pointer to the item allocated, or NULL
 */
#define paho_malloc_t(x) malloc_tracked(__FILE__, __LINE__, x)
#endif

#if !defined(paho_realloc_t)
/**
 * call realloc with internal heap tracking; when NO_HEAP_TRACKING is defined,
 * this is equivalent to paho_realloc_u
 * @param a the heap item to be reallocated
 * @param b the new size of the item
 * @return the new pointer to the heap item
 */
#define paho_realloc_t(a, b) realloc_tracked(__FILE__, __LINE__, a, b)
#endif

#if !defined(paho_free_t)
/**
 * call free with internal heap tracking; when NO_HEAP_TRACKING is defined,
 * this is equivalent to paho_free_u
 * @param x the pointer to the item to be freed
 */
#define paho_free_t(x) free_tracked(__FILE__, __LINE__, x)
#endif

/**
 * conditionally call malloc with or without internal heap tracking; when
 * NO_HEAP_TRACKING is defined, this is equivalent to paho_malloc_u
 * @param c enable internal heap tracking when nonzero
 * @param x the size of the item to be allocated
 * @return the pointer to the item allocated, or NULL
 */
#define paho_malloc_c(c, x) ((c) ? paho_malloc_t(x) : paho_malloc_u(x))

/**
 * conditionally call realloc with or without internal heap tracking; when
 * NO_HEAP_TRACKING is defined, this is equivalent to paho_realloc_u
 * @param c enable internal heap tracking when nonzero
 * @param a the heap item to be reallocated
 * @param b the new size of the item
 * @return the new pointer to the heap item
 */
#define paho_realloc_c(c, a, b) ((c) ? paho_realloc_t(a, b) : paho_realloc_u(a, b))

/**
 * conditionally call free with or without internal heap tracking; when
 * NO_HEAP_TRACKING is defined, this is equivalent to paho_free_u
 * @param c enable internal heap tracking when nonzero
 * @param x the pointer to the item to be freed
 */
#define paho_free_c(c, x) ((c) ? paho_free_t(x) : paho_free_u(x))

#else

#if !defined(paho_malloc_t)
/**
 * call malloc with internal heap tracking; when NO_HEAP_TRACKING is defined,
 * this is equivalent to paho_malloc_u
 * @param x the size of the item to be allocated
 * @return the pointer to the item allocated, or NULL
 */
#define paho_malloc_t(x) paho_malloc_u(x)
#endif

#if !defined(paho_realloc_t)
/**
 * call realloc with internal heap tracking; when NO_HEAP_TRACKING is defined,
 * this is equivalent to paho_realloc_u
 * @param a the heap item to be reallocated
 * @param b the new size of the item
 * @return the new pointer to the heap item
 */
#define paho_realloc_t(a, b) paho_realloc_u(a, b)
#endif

#if !defined(paho_free_t)
/**
 * call free with internal heap tracking; when NO_HEAP_TRACKING is defined,
 * this is equivalent to paho_free_u
 * @param x the pointer to the item to be freed
 */
#define paho_free_t(x) paho_free_u(x)
#endif

/**
 * conditionally call malloc with or without internal heap tracking; when
 * NO_HEAP_TRACKING is defined, this is equivalent to paho_malloc_u
 * @param c enable internal heap tracking when nonzero
 * @param x the size of the item to be allocated
 * @return the pointer to the item allocated, or NULL
 */
#define paho_malloc_c(c, x) paho_malloc_u(x)

/**
 * conditionally call realloc with or without internal heap tracking; when
 * NO_HEAP_TRACKING is defined, this is equivalent to paho_realloc_u
 * @param c enable internal heap tracking when nonzero
 * @param a the heap item to be reallocated
 * @param b the new size of the item
 * @return the new pointer to the heap item
 */
#define paho_realloc_c(c, a, b) paho_realloc_u(a, b)

/**
 * conditionally call free with or without internal heap tracking; when
 * NO_HEAP_TRACKING is defined, this is equivalent to paho_free_u
 * @param c enable internal heap tracking when nonzero
 * @param x the pointer to the item to be freed
 */
#define paho_free_c(c, x) paho_free_u(x)

#endif

#if !defined(NO_HEAP_TRACKING)

/**
 * Information about the state of the heap.
 */
typedef struct
{
	size_t current_size;	/**< current size of the heap in bytes */
	size_t max_size;		/**< max size the heap has reached in bytes */
} heap_info;

#if defined(__cplusplus)
 extern "C" {
#endif

void* malloc_tracked(char*, int, size_t size);
void* realloc_tracked(char*, int, void* p, size_t size);
void free_tracked(char*, int, void* p);

void Heap_scan(FILE* file);
int Heap_initialize(void);
void Heap_terminate(void);
LIBMQTT_API heap_info* Heap_get_info(void);
int HeapDump(FILE* file);
int HeapDumpString(FILE* file, char* str);
void* Heap_findItem(void* p);
void Heap_unlink(char* file, int line, void* p);
#ifdef __cplusplus
     }
#endif

#endif

#endif
