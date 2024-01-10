#include <kodik/api/object.h>
#include <evo/threads/threads.h>
#include <stdatomic.h>

static
void *user_data = NULL;

static
mtx_t sync = _MTX_INITIALIZER_NP;

static
void
kodik_object_init_real() {
  struct kodik_object *obj = user_data;
  obj->mtx = (mtx_t) _MTX_INITIALIZER_NP;
  obj->refs = 0;
  atomic_fetch_add(&obj->refs, 1);
}

int
kodik_object_sync_begin(struct kodik_object *obj) {
  return mtx_lock(&obj->mtx);
}

int
kodik_object_sync_end(struct kodik_object *obj) {
  return mtx_unlock(&obj->mtx);
}

bool kodik_object_init(struct kodik_object *obj) {
  mtx_lock(&sync);
  user_data = obj;
  call_once(&obj->of, kodik_object_init_real);
  user_data = NULL;
  mtx_unlock(&sync);
}
