#include <evo/threads/threads.h>
#include <stdint.h>
#include <stddef.h>

#include <stdatomic.h>

struct kodik_ref_count {
  atomic_ullong ref;
  mtx_t mtx;
};
