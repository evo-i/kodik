#ifndef KODIK_DATA_COUNTRY_H
#define KODIK_DATA_COUNTRY_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include "../exports.h"

typedef struct kodik_country_t kodik_country_t;

KODIK_API
char const *
kodik_country_get_title(kodik_country_t const *self);

KODIK_API
int64_t
kodik_country_get_count(kodik_country_t const *self);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KODIK_DATA_COUNTRY_H */
