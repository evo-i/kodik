#ifndef KODIK_DATA_GENRE_H
#define KODIK_DATA_GENRE_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stddef.h>
#include "../exports.h"

struct kodik_genre;

KODIK_API
char const *
kodik_genre_get_title(struct kodik_genre const *self);

KODIK_API
int64_t
kodik_genre_get_count(struct kodik_genre const *self);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KODIK_DATA_GENRE_H */
