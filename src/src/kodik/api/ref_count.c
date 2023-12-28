#include <evo/threads/threads.h>
#include <stdint.h>
#include <stddef.h>

struct kodik_ref_count {
  uint64_t refs;
  mtx_t mtx;
};
