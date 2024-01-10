#ifndef KODIK_DATA_QUALITY_H
#define KODIK_DATA_QUALITY_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "../exports.h"

struct kodik_quality;

KODIK_API
char const *
kodik_quality_get_title(struct kodik_quality const *self);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KODIK_DATA_QUALITY_H */
