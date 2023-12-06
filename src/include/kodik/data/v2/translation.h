#ifndef KODIK_DATA_V2_TRANSLATION_H
#define KODIK_DATA_V2_TRANSLATION_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stddef.h>

#include "../../exports.h"

typedef struct kodik_v2_translation_t kodik_v2_translation_t;

KODIK_API
int64_t
kodik_v2_translation_get_id(kodik_v2_translation_t const *self);

KODIK_API
char const *
kodik_v2_translation_get_title(kodik_v2_translation_t const *self);

KODIK_API
int64_t
kodik_v2_translation_get_count(kodik_v2_translation_t const *self);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KODIK_DATA_V2_TRANSLATION_H */
