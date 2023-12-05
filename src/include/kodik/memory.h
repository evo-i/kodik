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

KODIK_API
int
kodik_memory_get(kodik_malloc_t *p_out_malloc, kodik_calloc_t *p_out_calloc,
                 kodik_realloc_t *p_out_realloc, kodik_free_t *p_out_free);

KODIK_API
int
kodik_memory_set(kodik_malloc_t p_malloc, kodik_calloc_t p_calloc,
                 kodik_realloc_t p_realloc, kodik_free_t p_free);

KODIK_API
void *
kodik_malloc(size_t size);

KODIK_API
void *
kodik_calloc(size_t count, size_t size);

KODIK_API
void *
kodik_realloc(void *old_mem, size_t new_size);

KODIK_API
void
kodik_free(void *block);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KODIK_MEMORY_H */
