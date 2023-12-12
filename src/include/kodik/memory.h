/**
 * \file memory.h
 * \author evo (kok.in@yahoo.com) https://github.com/evo-i
 * \brief Kodik memory management.
 * \version 0.1
 * \date 2023-12-12
 *
 * Copyright © 2023 evo-i (evo) https://github.com/evo-i
 *
 */

#ifndef KODIK_MEMORY_H
#define KODIK_MEMORY_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "exports.h"
#include <stddef.h>
#include <stdint.h>

typedef void *(*kodik_malloc_t )(size_t count);
typedef void *(*kodik_calloc_t )(size_t count, size_t size);
typedef void *(*kodik_realloc_t)(void *old_mem, size_t new_size);
typedef void  (*kodik_free_t   )(void *block);

/**
 * \brief Return pointers to funtions that can be used for memory allocation.
 *
 * \param p_out_malloc pointer to `malloc` function.
 * \param p_out_calloc pointer to `calloc` function.
 * \param p_out_realloc pointer to `realloc` function.
 * \param p_out_free pointer to free function.
 * \return int returns 0 on success non-zero value on error.
 */
KODIK_API
int
kodik_memory_get(kodik_malloc_t *p_out_malloc, kodik_calloc_t *p_out_calloc,
                 kodik_realloc_t *p_out_realloc, kodik_free_t *p_out_free);


/**
 * \brief Set pointers to funtions that can be used for memory allocation.
 *
 * \param p_out_malloc pointer to `malloc` function.
 * \param p_out_calloc pointer to `calloc` function.
 * \param p_out_realloc pointer to `realloc` function.
 * \param p_out_free pointer to free function.
 * \return int returns 0 on success non-zero value on error.
 *
 * \warning this function need to be called before first allocation.
 */
KODIK_API
int
kodik_memory_set(kodik_malloc_t p_malloc, kodik_calloc_t p_calloc,
                 kodik_realloc_t p_realloc, kodik_free_t p_free);

/**
 * \brief Allocate block of memory.
 *
 * \param size size of requested memory block.
 * \return void* NULL on error or pointer to block of memory.
 */
KODIK_API
void *
kodik_malloc(size_t size);

/**
 * \brief Allocate block of memory then set all of allocated block to 0.
 *
 * \param count blocks count.
 * \param size block size.
 * \return void* NULL on error or pointer to block of memory.
 */
KODIK_API
void *
kodik_calloc(size_t count, size_t size);

/**
 * \brief Reallocate block of memory.
 *
 * \param old_mem old pointer to block of memory.
 * \param new_size new size of requested block.
 * \return void* `NULL` on error or pointer to block of memory.
 *
 * \warning Do not replace old block of memory like:
 * \code{.c}
 * void *some_memory = kodik_malloc(10);
 * some_memory = kodik_realloc(some_memory, 11);
 * \endcode
 */
KODIK_API
void *
kodik_realloc(void *old_mem, size_t new_size);

/**
 * \brief Freed block of memory allocated with one of: \ref kodik_malloc,
 * \ref kodik_calloc, \ref kodik_realloc
 *
 *
 *
 * \param block pointer to block of memory.
 */
KODIK_API
void
kodik_free(void *block);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KODIK_MEMORY_H */
