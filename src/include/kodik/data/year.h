#ifndef KODIK_DATA_YEAR_H
#define KODIK_DATA_YEAR_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include "../exports.h"

struct kodik_year;

KODIK_API
int64_t
kodik_year_get_year(struct kodik_year const *self);

KODIK_API
int64_t
kodik_year_get_count(struct kodik_year const *self);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KODIK_DATA_YEAR_H */
