#include <uv.h>
#include <stdbool.h>
#include <stddef.h>
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

#define KODIK_MEMORY_ERROR_MUTEX(error) \
"uv_mutex_init failed with error: %s and message: %s\n",  \
uv_err_name(error), uv_strerror(error)

static uv_mutex_t *memory_mutex = NULL;

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

int
static_mutex_init(void) {
  int status = 0;
  if (NULL == memory_mutex) {
    status = uv_mutex_init(memory_mutex);
    if (0 != status) {
      (void) fprintf(stderr, KODIK_MEMORY_ERROR_MUTEX(status));
    }
  }
  return status;
}

int
kodik_memory_get(kodik_malloc_t *p_out_malloc, kodik_calloc_t *p_out_calloc,
                 kodik_realloc_t *p_out_realloc, kodik_free_t *p_out_free) {
  int status;

  status = static_mutex_init();

  if (0 != status) {
    return status;
  }

  uv_mutex_lock(memory_mutex);
  *p_out_malloc   = kodik_memory__.cb_malloc;
  *p_out_calloc   = kodik_memory__.cb_calloc;
  *p_out_realloc  = kodik_memory__.cb_realloc;
  *p_out_free     = kodik_memory__.cb_free;
  uv_mutex_unlock(memory_mutex);

  return status;
}

int
kodik_memory_set(kodik_malloc_t p_malloc, kodik_calloc_t p_calloc,
                 kodik_realloc_t p_realloc, kodik_free_t p_free) {
  int status = static_mutex_init();

  if (0 != status) {
    return status;
  }

  uv_mutex_lock(memory_mutex);
  kodik_memory__.cb_malloc = p_malloc;
  kodik_memory__.cb_calloc = p_calloc;
  kodik_memory__.cb_realloc = p_realloc;
  kodik_memory__.cb_free = p_free;
  uv_mutex_unlock(memory_mutex);

  return status;
}
void *
kodik_malloc(size_t size) {
  void *mem;
  if (0 != static_mutex_init()) {
    return NULL;
  }

  uv_mutex_lock(memory_mutex);
  mem = kodik_memory__.cb_malloc(size);
  uv_mutex_unlock(memory_mutex);
  return mem;
}

void *
kodik_calloc(size_t count, size_t size) {
  void *mem;

  if (0 != static_mutex_init()) {
    return NULL;
  }

  uv_mutex_lock(memory_mutex);
  mem = kodik_memory__.cb_calloc(count, size);
  uv_mutex_unlock(memory_mutex);
  return mem;
}

void *
kodik_realloc(void *old_mem, size_t new_size) {
  void *mem;

  if (0 != static_mutex_init()) {
    return NULL;
  }

  uv_mutex_lock(memory_mutex);
  mem = kodik_memory__.cb_realloc(old_mem, new_size);
  uv_mutex_unlock(memory_mutex);
  return mem;
}

void
kodik_free(void *block) {
  if (0 != static_mutex_init()) {
    return;
  }

  uv_mutex_lock(memory_mutex);
  kodik_memory__.cb_free(block);
  uv_mutex_unlock(memory_mutex);
}
