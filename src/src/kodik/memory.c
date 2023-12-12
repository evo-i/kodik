#include <evo/threads/threads.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <kodik/memory.h>

#ifdef HAS_CONFIG
# include <config.h>
#endif

#ifdef HAS_MIMALLOC_H
# include <mimalloc.h>
# define KODIK_MEMORY_SELECT(FIRST, SECOND) FIRST
#else
# include <stdlib.h>
# define KODIK_MEMORY_SELECT(FIRST, SECOND) SECOND
#endif

#define KODIK_MEMORY_ERROR_MUTEX(error) #error

mtx_t memory_mutex = { 0 };
once_flag mem_init = { 0 };

struct mem__ {
  kodik_malloc_t  cb_malloc;
  kodik_calloc_t  cb_calloc;
  kodik_realloc_t cb_realloc;
  kodik_free_t    cb_free;
} static kodik_memory__ = {
  .cb_malloc  = KODIK_MEMORY_SELECT(mi_malloc,  malloc),
  .cb_calloc  = KODIK_MEMORY_SELECT(mi_calloc,  calloc),
  .cb_realloc = KODIK_MEMORY_SELECT(mi_realloc, realloc),
  .cb_free    = KODIK_MEMORY_SELECT(mi_free,    free)
};

void
static_mutex_init(void) {
  int status = 0;
  status = mtx_init(&memory_mutex, mtx_plain);
  if (0 != status) {
    (void) fprintf(stderr, KODIK_MEMORY_ERROR_MUTEX(status));
    abort();
  }
}

int
kodik_memory_get(kodik_malloc_t *p_out_malloc, kodik_calloc_t *p_out_calloc,
                 kodik_realloc_t *p_out_realloc, kodik_free_t *p_out_free) {
  call_once(&mem_init, static_mutex_init);

  int status;

  status = mtx_lock(&memory_mutex);
  if (status != 0) {
    return status;
  }

  *p_out_malloc   = kodik_memory__.cb_malloc;
  *p_out_calloc   = kodik_memory__.cb_calloc;
  *p_out_realloc  = kodik_memory__.cb_realloc;
  *p_out_free     = kodik_memory__.cb_free;

  status = mtx_unlock(&memory_mutex);

  return status;
}

int
kodik_memory_set(kodik_malloc_t p_malloc, kodik_calloc_t p_calloc,
                 kodik_realloc_t p_realloc, kodik_free_t p_free) {
  call_once(&mem_init, static_mutex_init);

  int status;

  status = mtx_lock(&memory_mutex);

  if (status != 0) {
    return status;
  }

  kodik_memory__.cb_malloc = p_malloc;
  kodik_memory__.cb_calloc = p_calloc;
  kodik_memory__.cb_realloc = p_realloc;
  kodik_memory__.cb_free = p_free;
  status = mtx_unlock(&memory_mutex);

  return status;
}
void *
kodik_malloc(size_t size) {
  call_once(&mem_init, static_mutex_init);
  void *mem;

  if (thrd_success != mtx_lock(&memory_mutex)) {
    return NULL;
  }

  mem = kodik_memory__.cb_malloc(size);

  mtx_unlock(&memory_mutex);
  return mem;
}

void *
kodik_calloc(size_t count, size_t size) {
  call_once(&mem_init, static_mutex_init);

  void *mem;
  if (thrd_success != mtx_lock(&memory_mutex)) {
    return NULL;
  }

  mem = kodik_memory__.cb_calloc(count, size);
  mtx_unlock(&memory_mutex);
  return mem;
}

void *
kodik_realloc(void *old_mem, size_t new_size) {
  call_once(&mem_init, static_mutex_init);

  void *mem;

  if (thrd_success != mtx_lock(&memory_mutex)) {
    return NULL;
  }

  mem = kodik_memory__.cb_realloc(old_mem, new_size);
  mtx_unlock(&memory_mutex);
  return mem;
}

void
kodik_free(void *block) {
  call_once(&mem_init, static_mutex_init);

  mtx_lock(&memory_mutex);
  kodik_memory__.cb_free(block);
  mtx_unlock(&memory_mutex);
}
