#ifndef KODIK_DATA_V2_QUALITY_H
#define KODIK_DATA_V2_QUALITY_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stddef.h>
#include "../../exports.h"

typedef struct kodik_v2_quality_t kodik_v2_quality_t;

KODIK_API
char const *
kodik_v2_quality_get_title(kodik_v2_quality_t const *self);

KODIK_API
int64_t
kodik_v2_quality_get_count(kodik_v2_quality_t const *self);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KODIK_DATA_V2_QUALITY_H */
