#ifndef KODIK_DATA_V2_QUALITY_H
#define KODIK_DATA_V2_QUALITY_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stddef.h>

#include "../../exports.h"

struct kodik_v2_quality;

KODIK_API
char const *
kodik_v2_quality_get_title(struct kodik_v2_quality const *self);

KODIK_API
int64_t
kodik_v2_quality_get_count(struct kodik_v2_quality const *self);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KODIK_DATA_V2_QUALITY_H */
