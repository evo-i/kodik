#ifndef KODIK_DATA_QUALITY_H
#define KODIK_DATA_QUALITY_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "../exports.h"

typedef struct kodik_quality_t kodik_quality_t;

KODIK_API
char const *
kodik_quality_get_title(kodik_quality_t const *quality);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KODIK_DATA_QUALITY_H */
