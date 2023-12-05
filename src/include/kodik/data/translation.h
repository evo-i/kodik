#ifndef KODIK_DATA_TRANSLATION_H
#define KODIK_DATA_TRANSLATION_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stddef.h>
#include "../exports.h"

typedef struct kodik_translation_t kodik_translation_t;

KODIK_API
char const *
kodik_translation_get_title(kodik_translation_t const *translation);

KODIK_API
char const *
kodik_translation_get_type(kodik_translation_t const *translation);

KODIK_API
int64_t
kodik_translation_get_id(kodik_translation_t const *translation);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KODIK_DATA_TRANSLATION_H */
