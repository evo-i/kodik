#ifndef KODIK_DATA_GENRE_H
#define KODIK_DATA_GENRE_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stddef.h>
#include "../exports.h"

typedef struct kodik_genre_t kodik_genre_t;

KODIK_API
char const *
kodik_genre_get_title(kodik_genre_t const *self);

KODIK_API
int64_t
kodik_genre_get_count(kodik_genre_t const *self);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KODIK_DATA_GENRE_H */
