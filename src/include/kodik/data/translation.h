#ifndef KODIK_DATA_TRANSLATION_H
#define KODIK_DATA_TRANSLATION_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stddef.h>
#include "../exports.h"

struct kodik_translation;

KODIK_API
char const *
kodik_translation_get_title(struct kodik_translation const *self);

KODIK_API
char const *
kodik_translation_get_type(struct kodik_translation const *self);

KODIK_API
int64_t
kodik_translation_get_id(struct kodik_translation const *self);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KODIK_DATA_TRANSLATION_H */
