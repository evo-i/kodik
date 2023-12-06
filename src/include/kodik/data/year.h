#ifndef KODIK_DATA_YEAR_H
#define KODIK_DATA_YEAR_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include "../exports.h"

typedef struct kodik_year_t kodik_year_t;

KODIK_API
int64_t
kodik_year_get_year(kodik_year_t const *self);

KODIK_API
int64_t
kodik_year_get_count(kodik_year_t const *self);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KODIK_DATA_YEAR_H */
