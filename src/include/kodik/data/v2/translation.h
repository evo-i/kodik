#ifndef KODIK_DATA_V2_TRANSLATION_H
#define KODIK_DATA_V2_TRANSLATION_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stddef.h>

#include "../../exports.h"

struct kodik_v2_translation;

KODIK_API
int64_t
kodik_v2_translation_get_id(struct kodik_v2_translation const *self);

KODIK_API
char const *
kodik_v2_translation_get_title(struct kodik_v2_translation const *self);

KODIK_API
int64_t
kodik_v2_translation_get_count(struct kodik_v2_translation const *self);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KODIK_DATA_V2_TRANSLATION_H */
