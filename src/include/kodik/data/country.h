#ifndef KODIK_DATA_COUNTRY_H
#define KODIK_DATA_COUNTRY_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include "../exports.h"

struct kodik_country;

KODIK_API
char const *
kodik_country_get_title(struct kodik_country const *self);

KODIK_API
int64_t
kodik_country_get_count(struct kodik_country const *self);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KODIK_DATA_COUNTRY_H */
