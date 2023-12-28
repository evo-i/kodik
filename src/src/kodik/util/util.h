#ifndef KODIK_PRIVATE_UTIL_H
#define KODIK_PRIVATE_UTIL_H 1


#ifdef __cplusplus
extern "C" {
#endif /* !__cplusplus */

#include <evo/threads/threads.h>
#include <stdint.h>

struct kodik_ref_count {
  uint64_t  count;
  mtx_t     mtx;
};



#ifdef __cplusplus
}
#endif /* !__cplusplus */
#endif /* KODIK_PRIVATE_UTIL_H */
