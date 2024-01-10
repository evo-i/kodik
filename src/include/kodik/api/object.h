#ifndef KODIK_API_OBJECT_H
#define KODIK_API_OBJECT_H 1

#ifdef __cplusplus
extern "C" {
#endif /* !__cplusplus */

#include <stdint.h>
#include <stdbool.h>
#include <evo/threads/threads.h>
#include <stdatomic.h>

struct kodik_object {
  atomic_ullong refs;
  mtx_t         mtx;
  once_flag     of;
};

bool
kodik_object_init(struct kodik_object *obj);

int
kodik_object_sync_begin(struct kodik_object *obj);

int
kodik_object_sync_end(struct kodik_object *obj);

uint64_t
kodik_object_retain(struct kodik_object *obj);

uint64_t
kodik_object_release(struct kodik_object *obj);

#ifdef __cplusplus
}
#endif /* !__cplusplus */

#endif /* KODIK_API_OBJECT_H */
